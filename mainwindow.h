#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cstdlib>
#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QApplication>
#include <iostream>
#include <tache.h>

#include "connection.h"

#include <cstdlib>


QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE
using namespace std ;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:





    void on_add_val_s_clicked();

    void on_update_val_s_clicked();

    void on_refresh_s_clicked();

    void on_addButton_s_clicked();

    void on_updateButton_s_clicked();

    void on_deleteButton_s_clicked();

    void on_pushbutton3_clicked();

    void on_backtolist_clicked();

    void on_backtolist_2_clicked();

    void on_backtolist_3_clicked();




private:
    Ui::MainWindow *ui;
    /*void setupTableView();*/
    Tache montache;
    Connection c;





};
#endif // MAINWINDOW_H
