#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QMessageBox>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QtCharts/QChartView>  // Main chart view
#include <QtCharts/QBarSeries>  // For bar charts
#include <QtCharts/QBarSet>     // Individual bar sets
#include <QtCharts/QBarCategoryAxis>  // For category axis
#include <QtCharts/QValueAxis>  // For value axis
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QtCharts>
class client;



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouterConst_clicked();
    void on_tableView_activated(const QModelIndex &index);
    void on_modifier_clicked();
    void on_supprimerbtn_clicked();
    void navigateToPage(int pageIndex);
    void on_searchTextChanged(const QString &searchText);
    void on_sortheureChanged(int index);
    void setupStatisticsChart();
    void navigateToEmployees();
    void navigateToHome();
    void navigateToStock();
    void navigateBack();
    void navigateToClients();
    void navigateToAppointments();
    void navigateToTreatments();
    void navigateToResources();
    void stop1();
    void navigateToclient();
    void navigateToformation();
    void stop2();
private:
    Ui::MainWindow *ui;

     QWidget *chartContainer = nullptr;  // Pointer to hold our chart container
};

#endif // MAINWINDOW_H
