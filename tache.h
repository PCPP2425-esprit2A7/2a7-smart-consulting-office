#ifndef TACHE_H
#define TACHE_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDebug>
#include <QObject>
#include <QSqlTableModel>
#include <QPixmap>
#include <QByteArray>
#include "connection.h"
#include <QTableView>
#include<QSqlError>



#include<QLineSeries>
#include <QPdfWriter>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QSizeF>
#include <QPrinter>
#include <QPageSize>

class Tache
{
private:
    QString nom;
    QString description;
    QString datee;
    int priorite;
    QString statut;

public:
    /*constructor*/
    Tache();
    Tache(QString, QString, QString, int, QString);
    /*destructor*/
    /* getters */
    QString getNom();
    QString getDescription();
    QString getDatee();
    int getPriorite();
    QString getStatut();
    /* setters */
    void setNom(QString nom);
    void setDescription(QString description);
    void setDatee(QString datee);
    void setPriorite(int priorite);
    void setStatut(QString statut);

    /* CRUD */
    QSqlQueryModel* afficher_tous_les_clients();
    bool ajouter_client();
    bool supprimer_client(QString nom);
    bool modifier_client(QString nom, QString description, QString datee, int priorite, QString statut);

};

#endif // TACHE_H
