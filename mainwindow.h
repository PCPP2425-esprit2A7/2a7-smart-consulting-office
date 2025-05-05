#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "githubclient.h"
#include "arduino.h"
#include "qlabel.h"
#include "qstandarditemmodel.h"
#include "projet.h"
<<<<<<< HEAD
#include "tache.h"
#include "calendrier.h"
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
#include <QChartView> // Inclure pour QChartView
#include <QSqlQuery>
=======
#include "tache.h"
#include "calendrier.h"
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af
>>>>>>> 1ef526ce3d4a5b5ac7518f95db20ca4d5e511ce8
#include <QChartView> // Inclure pour QChartView
#include <QSqlQuery>
#include <QItemSelection>
#include <QTableView>
#include <QValueAxis>
#include <QBarCategoryAxis>
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> 00ca2d6ddb272cb69d6813b4c25604876d18434f
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af
>>>>>>> 1ef526ce3d4a5b5ac7518f95db20ca4d5e511ce8

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
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD



=======
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af
>>>>>>> 1ef526ce3d4a5b5ac7518f95db20ca4d5e511ce8
    //FORMATION ***************************************
    void on_ajouter_clicked();

    void on_modifier_clicked();
    void on_supprimer_clicked();
    //void onFormationSelectionChanged(const QItemSelection &selected, const QItemSelection &);
    void on_afficher_clicked();
    void on_statistiques_clicked();
    void on_pdf_clicked();
    void on_presence_clicked();
    void on_evaluations_clicked();
    void on_tripardate_clicked();
    void on_triparduree_clicked();
    void on_ajouterEvaluationBtn_clicked();
    //void update_labelF();    // Bouton pour ajouter une évaluation

    //CONSULTANTS ***********************************************************************************************

    void on_ajouterConst_clicked();
    void on_tableView_activated(const QModelIndex &index);
    void onmodifier_clicked();
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
<<<<<<< HEAD
//TACHE ********************************************************************************************************

    void on_ajoute_2_clicked();
    void on_modifier_3_clicked2();
    void on_sup_2_clicked();
    void on_recuperer_clicked();
    void on_viewhistory_clicked();
    void on_tri_2_clicked();
    void on_pdf_3_clicked();
    void on_stat_2_clicked();
    void on_chercher_2_clicked();
    void on_calendarButton_clicked();
=======
<<<<<<< HEAD


=======
//TACHE ********************************************************************************************************

    void on_ajoute_clicked();
    void onmodifier_clicked2();
    void on_sup_clicked();
    void on_recuperer_clicked();
    void on_viewhistory_clicked();
    void on_tri_clicked();
    void onpdf_clicked();
    void on_stat_clicked();
    void on_chercher_clicked();
    void on_calendarButton_clicked();
>>>>>>> 00ca2d6ddb272cb69d6813b4c25604876d18434f
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af
>>>>>>> 1ef526ce3d4a5b5ac7518f95db20ca4d5e511ce8




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
<<<<<<< HEAD
=======
<<<<<<< HEAD
    int selectedFormationId = 3;

    QWidget *chartContainer = nullptr;
=======
<<<<<<< HEAD

=======
>>>>>>> 1ef526ce3d4a5b5ac7518f95db20ca4d5e511ce8
    int selectedFormationId = 3;

    QWidget *chartContainer = nullptr;
    //TAHCE ***************************************
    tache t;
    Calendrier *calendar;
<<<<<<< HEAD
=======
>>>>>>> 00ca2d6ddb272cb69d6813b4c25604876d18434f
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af
>>>>>>> 1ef526ce3d4a5b5ac7518f95db20ca4d5e511ce8

};
#endif // MAINWINDOW_H
