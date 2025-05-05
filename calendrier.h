#ifndef CALENDRIER_H
#define CALENDRIER_H

#include <QWidget>
#include <QCalendarWidget>
#include <QPushButton>
#include <QListView>
#include <QStandardItemModel>
#include "tache.h"

class Calendrier : public QWidget
{
    Q_OBJECT

public:
    explicit Calendrier(QWidget *parent = nullptr);
    void loadTasksForDate(const QDate &date);
    void setupUI();
    void loadTasks();
    void checkForOverdueTasks();

private slots:
    void onDateSelected(const QDate &date);
    void showAddTaskDialog();
    void showTaskDetails(const QModelIndex &index);
    void sendReminders(); // Déclaration ajoutée

private:
    QCalendarWidget *calendar;
    QListView *taskListView;
    QStandardItemModel *taskModel;
    QPushButton *addTaskButton;
    QPushButton *viewDailyButton;
    QPushButton *viewWeeklyButton;
    QPushButton *viewMonthlyButton;
<<<<<<< HEAD
=======
    QDate lastSelectedDate;
>>>>>>> 7b691f662826127da815b7d7434c9c56665f8748
};

#endif // CALENDRIER_H
