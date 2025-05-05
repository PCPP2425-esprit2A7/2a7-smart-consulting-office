#include "formationservice.h"
#include "evaluation.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "evaluation.h"
#include <QVector>
#include <QDebug>

QSqlQueryModel* FormationService::afficherEvaluations(int formationId) {
    //Crée un modèle Qt pour afficher des résultats SQL dans une vue (ex. QTableView).
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM EVALUATION WHERE formation_id = :formationId");
    query.bindValue(":formationId", formationId);

    if (!query.exec()) {
        qDebug() << "Erreur SQL : " << query.lastError().text();
        return nullptr;
    }

    model->setQuery(std::move(query));
    return model;
}

bool FormationService::ajouterParticipation(int formationId, const QString& participant, const QString& presence) {
    QSqlQuery query;
    query.prepare("INSERT INTO PARTICIPATIONS (FORMATION_ID, PARTICIPANT, PRESENCE) VALUES (:formationId, :participant, :presence)");
    query.bindValue(":formationId", formationId);
    query.bindValue(":participant", participant);
    query.bindValue(":presence", presence);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de la participation : " << query.lastError().text();
        return false;
    }
    return true;
}

