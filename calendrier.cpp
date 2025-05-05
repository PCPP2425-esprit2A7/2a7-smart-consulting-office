#include "calendrier.h"
#include "connection.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTextCharFormat>
#include <QMenu>
#include <QTimer>
#include <QDebug>
#include<QLabel>
#include<QLineEdit>
#include<QTextEdit>
#include<QDateEdit>
#include<QComboBox>
#include<QFormLayout>
#include <QGraphicsDropShadowEffect>
#include<QPropertyAnimation>


Calendrier::Calendrier(QWidget *parent) : QWidget(parent)
{

    setupUI();
    loadTasks();

    // Check for overdue tasks every hour
    setMinimumSize(600, 500);
    setWindowModality(Qt::ApplicationModal);
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

    // First clear any existing formats
    calendar->setDateTextFormat(QDate(), QTextCharFormat());

    if (query.exec()) {
        while (query.next()) {
            QDate taskDate = query.value(2).toDate();
            QString taskName = query.value(1).toString();
            QString priority = query.value(3).toString();

            // Create a new format for each task
            QTextCharFormat format;

            // Set base visual properties
            format.setFontWeight(QFont::Bold);
            format.setToolTip(QString("%1 - %2").arg(taskName).arg(priority));

            // Set priority-based colors
            if (priority == "High") {
                format.setBackground(QColor(255, 200, 200));  // Light red
                format.setForeground(Qt::black);
            } else if (priority == "Medium") {
                format.setBackground(QColor(255, 255, 150));  // Light yellow
                format.setForeground(Qt::black);
            } else { // Low
                format.setBackground(QColor(200, 255, 200));  // Light green
                format.setForeground(Qt::black);
            }

            // Apply the format to the date
            calendar->setDateTextFormat(taskDate, format);
        }
    } else {
        qDebug() << "Error loading tasks:" << query.lastError().text();
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
    lastSelectedDate = date;  // Store the selected date
    loadTasksForDate(date);
}
void Calendrier::showAddTaskDialog()
{

    QDialog dialog(this);
    dialog.setWindowTitle("Add New Task");

    // Create form elements
    QLabel *nameLabel = new QLabel("Task Name:", &dialog);
    QLineEdit *nameEdit = new QLineEdit(&dialog);

    QLabel *descLabel = new QLabel("Description:", &dialog);
    QTextEdit *descEdit = new QTextEdit(&dialog);

    QLabel *dateLabel = new QLabel("Date:", &dialog);
    QDateEdit *dateEdit = new QDateEdit(lastSelectedDate.isValid() ? lastSelectedDate : QDate::currentDate(), &dialog);
    dateEdit->setCalendarPopup(true);

    QLabel *priorityLabel = new QLabel("Priority:", &dialog);
    QComboBox *priorityCombo = new QComboBox(&dialog);
    priorityCombo->addItems({"Low", "Medium", "High"});

    QLabel *statusLabel = new QLabel("Status:", &dialog);
    QComboBox *statusCombo = new QComboBox(&dialog);
    statusCombo->addItems({"Not Started", "In Progress", "Completed"});

    QPushButton *saveButton = new QPushButton("Save", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    // Layout
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(nameLabel, nameEdit);
    formLayout->addRow(descLabel, descEdit);
    formLayout->addRow(dateLabel, dateEdit);
    formLayout->addRow(priorityLabel, priorityCombo);
    formLayout->addRow(statusLabel, statusCombo);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    // Connections
    connect(saveButton, &QPushButton::clicked, [&]() {
        QString name = nameEdit->text().trimmed();
        QString description = descEdit->toPlainText().trimmed();
        QDate date = dateEdit->date();
        QString priority = priorityCombo->currentText();
        QString status = statusCombo->currentText();

        if (name.isEmpty()) {
            QMessageBox::warning(&dialog, "Error", "Task name cannot be empty!");
            return;
        }

        // Create and save the task
        tache newTask(name, description, date, priority, status);
        if (newTask.create()) {
            QMessageBox::information(&dialog, "Success", "Task added successfully!");
            loadTasks(); // Refresh the calendar
            loadTasksForDate(date); // Refresh the task list if on the same date
            dialog.accept();
        } else {
            QMessageBox::critical(&dialog, "Error", "Failed to add task!");
        }
    });

    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    // Show the dialog
    if (dialog.exec() == QDialog::Accepted) {
        // Task was added successfully
    }
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
