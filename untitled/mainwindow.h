#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tache.h"
#include "calendrier.h"
#include <QMainWindow>
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajoute_clicked();
    void on_modifier_clicked();
    void on_sup_clicked();
    void on_recuperer_clicked();
    void on_viewhistory_clicked();
    void on_tri_clicked();
    void on_pdf_clicked();
    void on_stat_clicked();
    void on_chercher_clicked();
    void on_calendarButton_clicked();
void update_label();    // Déclaration ajoutée

private:
    Ui::MainWindow *ui;
    tache t;
    Arduino A;
    QString data;
    Calendrier *calendar;
};

#endif // MAINWINDOW_H
