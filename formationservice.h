#ifndef FORMATIONSERVICE_H
#define FORMATIONSERVICE_H

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QList>
#include "formations.h"

class FormationService
{
public:
    bool ajouterParticipation(int formationId, const QString& participant, const QString& presence);
    static bool ajouterEvaluation(int formationId, int participantId, double pourcentage, const QString &commentaire);
    static QSqlQueryModel* triParDate();
    static QSqlQueryModel* triParDuree();
    static QSqlQueryModel* rechercheAvancee(const QString &participant, const QDate &date, int duree);
    static bool exporterPDF(const QList<Formation> &formations); // ✅ Corrigé
    static int compterFormations();
    static double tauxParticipation();
    static QSqlQueryModel* afficherPresence();
    static double evaluerParticipant(int idFormation);
    static QSqlQueryModel* afficherEvaluations(int formationId);
    static QSqlQueryModel* afficherStatistiques();
    static QList<Formation> obtenirFormations(); // ✅ Corrigé

};

/*bool FormationService::ajouterParticipation(int formationId, const QString& participant, const QString& presence)
{
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
}*/

#endif // FORMATIONSERVICE_H
