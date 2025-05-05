#include "client.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QChart>
#include <QStringList>

Client::Client()
{
    id = 0;
    nomComplet = "";
    adresse = "";
    telephone = "";
    email = "";
    nomEntreprise = "";
    nbrConsultations = 0;
    joinDate = QDate::currentDate();
    cinClient = "";
    RFID = "";
}

Client::Client(int id, QString nomComplet, QString adresse, QString telephone, QString email, QString nomEntreprise, int nbrConsultations, QDate joinDate, QString cinClient, QString RFID)
{
    this->id = id;
    this->nomComplet = nomComplet;
    this->adresse = adresse;
    this->telephone = telephone;
    this->email = email;
    this->nomEntreprise = nomEntreprise;
    this->nbrConsultations = nbrConsultations;
    this->joinDate = joinDate;
    this->cinClient = cinClient;
    this->RFID = RFID;
}

bool Client::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENTS (NOMCOMPLET, ADRESSE, TELEPHONE, EMAIL, NOMENTREPRISE, NBR_CONSULTATIONS, JOIN_DATE, CIN_CLIENT, RFID) "
                  "VALUES (:nomComplet, :adresse, :telephone, :email, :nomEntreprise, :nbrConsultations, :joinDate, :cinClient, :RFID)");

    query.bindValue(":nomComplet", nomComplet);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":nomEntreprise", nomEntreprise);
    query.bindValue(":nbrConsultations", 0);
    query.bindValue(":joinDate", joinDate);
    query.bindValue(":cinClient", cinClient);
    query.bindValue(":RFID", RFID);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du client: " << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();


    model->setQuery(
        "SELECT ID_CLIENT, NOMCOMPLET, NOMENTREPRISE, ADRESSE, EMAIL, TELEPHONE, "
        "NBR_CONSULTATIONS, JOIN_DATE, CIN_CLIENT,RFID "
        "FROM CLIENTS"
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Entreprise"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Consultations"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'adhésion"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("RFID"));

    return model;
}


bool Client::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENTS WHERE ID_CLIENT = :id");
    query.bindValue(":id", id);

    return query.exec();
}

bool Client::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENTS SET NOMCOMPLET = :nomComplet, ADRESSE = :adresse, TELEPHONE = :telephone, EMAIL = :email, "
                  "NOMENTREPRISE = :nomEntreprise, NBR_CONSULTATIONS = :nbrConsultations, "
                  "JOIN_DATE = :joinDate, CIN_CLIENT = :cinClient WHERE ID_CLIENT = :id");

    query.bindValue(":nomComplet", nomComplet);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":nomEntreprise", nomEntreprise);
    query.bindValue(":nbrConsultations", nbrConsultations);
    query.bindValue(":joinDate", joinDate);
    query.bindValue(":cinClient", cinClient);
    query.bindValue(":id", id);

    return query.exec();
}
QChartView* Client::stat()
{
    // Création des ensembles de données (par entreprise)
    QMap<QString, int> companyCounts;

    // Requête SQL pour récupérer les entreprises des clients
    QSqlQuery query;
    query.exec("SELECT NOMENTREPRISE FROM CLIENTS");

    // Vérifier si la requête a échoué
    if (query.lastError().isValid()) {
        qDebug() << "Erreur de la requête: " << query.lastError().text();
        return nullptr; // Retourner nullptr en cas d'erreur
    }

    // Comptage des clients par entreprise
    while (query.next()) {
        QString company = query.value(0).toString(); // Récupérer le nom de l'entreprise
        companyCounts[company]++; // Incrémenter le nombre de clients pour l'entreprise
    }

    // Création des ensembles de données pour chaque entreprise
    QBarSeries* series = new QBarSeries();
    QStringList categories; // Pour stocker les noms des entreprises

    // Ajout des données aux ensembles
    for (auto it = companyCounts.begin(); it != companyCounts.end(); ++it) {
        QBarSet* set = new QBarSet(it.key()); // Créer un ensemble pour chaque entreprise
        *set << it.value(); // Ajouter le nombre de clients
        series->append(set); // Ajouter à la série
        categories << it.key(); // Ajouter le nom de l'entreprise aux catégories
    }

    // Création du graphique
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des clients par entreprise");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Ajout des axes
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories); // Ajouter les catégories des entreprises
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, qMax(1, *std::max_element(companyCounts.begin(), companyCounts.end()))); // Plage minimale garantie
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Suppression de la légende si nécessaire
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Création de la vue du graphique
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Retourner la vue pour affichage
    return chartView;
}
void Client::setNomComplet(const QString &nom)
{
    nomComplet = nom;
}

void Client::setAdresse(const QString &adresse)
{
    this->adresse = adresse;
}

void Client::setEmail(const QString &email)
{
    this->email = email;
}

void Client::setCinClient(const QString &cin)
{
    cinClient = cin;
}
void fetchClientByRFID(const QString &rfidTag) {
    QSqlQuery query;
    query.prepare("SELECT * FROM clients WHERE RFID = :rfid");
    query.bindValue(":rfid", rfidTag);

    if (query.exec()) {
        if (query.next()) {
            int clientId = query.value("id").toInt();
            QString clientName = query.value("name").toString();
            QString clientRFID = query.value("RFID").toString();

            qDebug() << "Client ID: " << clientId;
            qDebug() << "Client Name: " << clientName;
            qDebug() << "Client RFID: " << clientRFID;
        } else {
            qDebug() << "No client found with RFID: " << rfidTag;
        }
    } else {
        qDebug() << "Error executing query: " << query.lastError();
    }
}

