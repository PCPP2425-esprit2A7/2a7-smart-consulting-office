#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void ajouterClient();  // Add a client
    void afficherClients(); // Display clients
    void supprimerClient(); // Delete a client
    void modifierClient();
    void nextPage();
    void prevPage();
    void onCalendarDateSelected(const QDate &date);
    void confirmerModification();
    void exportClientsToPDF();
    void sortClientsByJoinDate();
    void searchClientByCIN();
    void setupStatistics();




private:
    Ui::MainWindow *ui;
    Client *client;  // Client instance
    // A function to display the chart
    QDate selectedDate;


};

#endif // MAINWINDOW_H
