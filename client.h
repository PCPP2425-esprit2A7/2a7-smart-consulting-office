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
    Client(int id, QString nomComplet, QString adresse, QString telephone, QString email, QString nomEntreprise, int nbrConsultations, QDate joinDate, QString cinClient);

    bool ajouter();
    bool modifier();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
    QChartView* stat();

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
};

#endif // CLIENT_H
