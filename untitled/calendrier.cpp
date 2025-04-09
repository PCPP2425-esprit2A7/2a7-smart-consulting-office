#include "calendrier.h"
#include "connection.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTextCharFormat>
#include <QMenu>
#include <QTimer>
#include <QDebug>

Calendrier::Calendrier(QWidget *parent) : QWidget(parent)
{
    setupUI();
    loadTasks();

    // Check for overdue tasks every hour
    QTimer *reminderTimer = new QTimer(this);
    connect(reminderTimer, &QTimer::timeout, this, &Calendrier::checkForOverdueTasks);
    reminderTimer->start(3600000); // 1 hour

    // Initial check
    checkForOverdueTasks();
}

void Calendrier::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Calendar widget
    calendar = new QCalendarWidget(this);
    calendar->setGridVisible(true);
    connect(calendar, &QCalendarWidget::clicked, this, &Calendrier::onDateSelected);

    // Task list view
    taskListView = new QListView(this);
    taskModel = new QStandardItemModel(this);
    taskListView->setModel(taskModel);
    connect(taskListView, &QListView::doubleClicked, this, &Calendrier::showTaskDetails);

    // View buttons
    QHBoxLayout *viewLayout = new QHBoxLayout();
    viewDailyButton = new QPushButton("Daily", this);
    viewWeeklyButton = new QPushButton("Weekly", this);
    viewMonthlyButton = new QPushButton("Monthly", this);

    connect(viewDailyButton, &QPushButton::clicked, [this]() {
        calendar->setCurrentPage(calendar->yearShown(), calendar->monthShown());
    });

    connect(viewWeeklyButton, &QPushButton::clicked, [this]() {
        // Implement weekly view logic
    });

    connect(viewMonthlyButton, &QPushButton::clicked, [this]() {
        // Implement monthly view logic
    });

    viewLayout->addWidget(viewDailyButton);
    viewLayout->addWidget(viewWeeklyButton);
    viewLayout->addWidget(viewMonthlyButton);

    // Add task button
    addTaskButton = new QPushButton("Add Task", this);
    connect(addTaskButton, &QPushButton::clicked, this, &Calendrier::showAddTaskDialog);

    // Assemble layout
    mainLayout->addWidget(calendar);
    mainLayout->addLayout(viewLayout);
    mainLayout->addWidget(taskListView);
    mainLayout->addWidget(addTaskButton);

    setLayout(mainLayout);
}

void Calendrier::loadTasks()
{
    QSqlDatabase db = Connection::get_database();
    QSqlQuery query(db);
    query.prepare("SELECT id, nom, datee, priorite FROM TACHES");
    while (query.next()) {
        QDate taskDate = query.value(2).toDate();
        QString taskName = query.value(1).toString();
        QString priority = query.value(3).toString();

        // Format text for the calendar
        QTextCharFormat format;
        if (priority == "High") {
            format.setBackground(Qt::red);
            format.setForeground(Qt::white);
        } else if (priority == "Medium") {
            format.setBackground(Qt::yellow);
        } else {
            format.setBackground(Qt::green);
        }

        calendar->setDateTextFormat(taskDate, format);
    }
}

void Calendrier::loadTasksForDate(const QDate &date)
{
    taskModel->clear();
    QSqlDatabase db = Connection::get_database();
    QSqlQuery query(db);;
    query.prepare("SELECT id, nom, description, priorite, statut FROM TACHES WHERE datee = :date");
    query.bindValue(":date", date);

    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString description = query.value(2).toString();
            QString priority = query.value(3).toString();
            QString status = query.value(4).toString();

            QStandardItem *item = new QStandardItem(
                QString("%1 - %2 (%3, %4)").arg(name).arg(description).arg(priority).arg(status));
            item->setData(id, Qt::UserRole);
            taskModel->appendRow(item);
        }
    }
}

void Calendrier::onDateSelected(const QDate &date)
{
    loadTasksForDate(date);
}

void Calendrier::showAddTaskDialog()
{
    // You can reuse your existing task creation dialog here
    // Or implement a simplified version for the calendar
    QMessageBox::information(this, "Add Task", "This would open the task creation dialog");
}

void Calendrier::showTaskDetails(const QModelIndex &index)
{
    int taskId = index.data(Qt::UserRole).toInt();
    tache task = tache::read(taskId);

    QString details = QString(
                          "Task ID: %1\n"
                          "Name: %2\n"
                          "Description: %3\n"
                          "Date: %4\n"
                          "Priority: %5\n"
                          "Status: %6")
                          .arg(task.getId())
                          .arg(task.getNom())
                          .arg(task.getDescription())
                          .arg(task.getDatee().toString("dd/MM/yyyy"))
                          .arg(task.getPriorite())
                          .arg(task.getStatut());

    QMessageBox::information(this, "Task Details", details);
}

void Calendrier::checkForOverdueTasks()
{
    QDate today = QDate::currentDate();
    QSqlDatabase db = Connection::get_database();
    QSqlQuery query(db);
    query.prepare("SELECT nom FROM TACHES WHERE datee < :today AND statut != 'Completed'");
    query.bindValue(":today", today);

    if (query.exec()) {
        QStringList overdueTasks;
        while (query.next()) {
            overdueTasks << query.value(0).toString();
        }

        if (!overdueTasks.isEmpty()) {
            QMessageBox::warning(this, "Overdue Tasks",
                                 QString("You have %1 overdue tasks:\n- %2")
                                     .arg(overdueTasks.count())
                                     .arg(overdueTasks.join("\n- ")));
        }
    }
}
void Calendrier::sendReminders()
{
    QDate today = QDate::currentDate();
    QSqlDatabase db = Connection::get_database();
    QSqlQuery query(db);
    query.prepare("SELECT nom FROM TACHES WHERE datee = :today AND statut != 'Completed'");
    query.bindValue(":today", today);

    if (query.exec()) {
        QStringList tasksDue;
        while (query.next()) {
            tasksDue << query.value(0).toString();
        }

        if (!tasksDue.isEmpty()) {
            QMessageBox::information(this, "Rappels",
                                     "Tâches pour aujourd'hui:\n- " + tasksDue.join("\n- "));
        }
    }
}
