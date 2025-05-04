#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "githubclient.h"
#include "arduino.h"
#include "qlabel.h"
#include "qstandarditemmodel.h"
#include "projet.h"
#include <QChartView> // Inclure pour QChartView
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void addClients(const QString &name, const QString &address, const QString &email, const QString &cin);

private slots:
    //CLIENT**************************************
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
    void afficherClientStats();
    void onSendClicked();
    void handleResponse(const QString &response);
    void addClient(const QString &name, const QString &address, const QString &email, const QString &cin);
    void update_label_from_arduino();
    void update_label();
    void fetchClientByRFID(const QString &rfidTag);
    //PROJETS *****************************************
    void ajouterProjet();
    void supprimerProjet();
    void afficherProjet();
    void modifierprojet();


    void ontrier_clicked();
    void onchercher_clicked();
    void onexporter_clicked();

    void onshowStatsButton_clicked();
    void afficherStat();
    void afficherDashboardASCII();
    void onbtnAfficherDashboard_clicked();
    void showAsciiDashboardPage();







private:
    Ui::MainWindow *ui;
    //CLIENTS*****************************
    Client *client;  // Client instance
    // A function to display the chart
    QDate selectedDate;
    OpenAIChatBot *githubClient;
    QByteArray data; // variable contenant les données reçues

    Arduino A; // ton objet Arduino
    QTimer *timer; // objet temporaire
       QStandardItemModel *model;
    QLabel *clientInfoLabel;
    //PROJETS ******************************
    projets pr;  // Objet projet

    // Nouvelle méthode pour afficher le graphique des statistiques
    QChartView* stat(); // Fonction pour générer le graphique des statistiques


};
#endif // MAINWINDOW_H
