#ifndef CLIENT_H
#define CLIENT_H

#include "qchartview.h"
#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Client
{
public:
    Client();
    Client(int id, QString nomComplet, QString adresse, QString telephone, QString email, QString nomEntreprise, int nbrConsultations, QDate joinDate, QString cinClient, QString RFID);

    bool ajouter();
    bool modifier();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
    QChartView* stat();

    void setNomComplet(const QString &nom);
    void setAdresse(const QString &adresse);
    void setEmail(const QString &email);
    void setCinClient(const QString &cin);
    void fetchClientByRFID(const QString &rfidTag);


private:
    int id;
    QString nomComplet;
    QString adresse;
    QString telephone;
    QString email;
    QString nomEntreprise;
    int nbrConsultations;
    QDate joinDate;
    QString cinClient;
    QString RFID;

};

#endif // CLIENT_H
