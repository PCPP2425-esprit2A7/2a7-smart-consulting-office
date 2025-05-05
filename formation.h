// Source file (formation.cpp)

#include "formation.h"
#include "formationservice.h"
#include <QSqlError>
#include <QSqlRecord>
#include <QPdfWriter>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QPagedPaintDevice>
#include <QFileInfo>
#include <QPageSize>
#include <QFileDialog>
#include <QDebug>
#include "formation.h"

Formation::Formation() {}

Formation::Formation(int id,  QString dates, int duree, QString participant, QString intitule, QString statut)
    : id(id), dates(dates), duree(duree), participant(participant), intitule(intitule), statut(statut) {}

int Formation::getId() const {  // Make sure it's const here too
    return id;
}
QString Formation::getDate() const { return dates; }
int Formation::getDuree() const { return duree; }
QString Formation::getParticipant() const { return participant; }
QString Formation::getIntitule() const { return intitule; }
QString Formation::getStatut() const { return statut; }

bool Formation::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO FORMATIONS (ID, DATES, DUREE, PARTICIPANT, INTITULE, STATUT) "
                  "VALUES (:id, TO_DATE(:dates, 'YYYY-MM-DD'), :duree, :participant, :intitule, :statut)");

    query.bindValue(":id", id);
    query.bindValue(":dates", dates);  // Ensure the dates are in the correct format for your database
    query.bindValue(":duree", duree);
    query.bindValue(":participant", participant);
    query.bindValue(":intitule", intitule);
    query.bindValue(":statut", statut);

    if (!query.exec()) {
        qDebug() << "Erreur SQL (ajouter) :" << query.lastError().text();
        return false;
    }

    return true;
}

bool Formation::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FORMATIONS WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur SQL (supprimer) :" << query.lastError().text();
        return false;
    }

    return true;
}

bool Formation::modifier(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE FORMATIONS SET DATES = TO_DATE(:dates, 'YYYY-MM-DD'), DUREE = :duree, "
                  "PARTICIPANT = :participant, INTITULE = :intitule, STATUT = :statut WHERE ID = :id");

    query.bindValue(":id", id);
    query.bindValue(":dates", dates);
    query.bindValue(":duree", duree);
    query.bindValue(":participant", participant);
    query.bindValue(":intitule", intitule);
    query.bindValue(":statut", statut);

    if (!query.exec()) {
        qDebug() << "Erreur SQL (modifier) :" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel* Formation::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATIONS");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL afficher() :" << model->lastError().text();
    } else {
        qDebug() << "afficher() OK, lignes retournées :" << model->rowCount();
    }

    return model;
}
