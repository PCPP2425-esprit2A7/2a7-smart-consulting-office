#include "formations.h"
#include "formationservice.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>
#include <QPdfWriter>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QPageSize>
#include <QSqlQueryModel>

// ------------------ Formation ---------------------

Formation::Formation() {}

Formation::Formation(int id, QString dates, int duree, QString participant, QString intitule, QString statut, int nbr_participants)
    : id(id), dates(dates), duree(duree), participant(participant), intitule(intitule), statut(statut), nbr_participants(nbr_participants) {}

int Formation::getId() const { return id; }
QString Formation::getDate() const { return dates; }
int Formation::getDuree() const { return duree; }
QString Formation::getParticipant() const { return participant; }
QString Formation::getIntitule() const { return intitule; }
QString Formation::getStatut() const { return statut; }
int Formation::getNbrParticipants() const { return nbr_participants; }

bool Formation::ajouter()
{
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM FORMATIONS WHERE ID = :id");
    checkQuery.bindValue(":id", id);
    if (!checkQuery.exec()) return false;
    checkQuery.next();
    if (checkQuery.value(0).toInt() > 0) return false;

    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO FORMATIONS (ID, DATES, DUREE, PARTICIPANT, INTITULE, STATUT, NBR_PARTICIPANTS) "
                  "VALUES (:id, TO_DATE(:dates, 'YYYY-MM-DD'), :duree, :participant, :intitule, :statut, :nbr_participants)");

    query.bindValue(":id", id);
    query.bindValue(":dates", dates);
    query.bindValue(":duree", duree);
    query.bindValue(":participant", participant);
    query.bindValue(":intitule", intitule);
    query.bindValue(":statut", statut);
    query.bindValue(":nbr_participants", nbr_participants);

    if (!query.exec()) {
        db.rollback();
        return false;
    }

    FormationService formationService;
    bool participationAjoutee = formationService.ajouterParticipation(id, participant, statut);
    if (!participationAjoutee) {
        db.rollback();
        return false;
    }

    db.commit();
    return true;
}

bool Formation::modifier(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE FORMATIONS SET DATES = TO_DATE(:dates, 'YYYY-MM-DD'), DUREE = :duree, "
                  "PARTICIPANT = :participant, INTITULE = :intitule, STATUT = :statut, NBR_PARTICIPANTS = :nbr_participants "
                  "WHERE ID = :id");

    query.bindValue(":id", id);
    query.bindValue(":dates", dates);
    query.bindValue(":duree", duree);
    query.bindValue(":participant", participant);
    query.bindValue(":intitule", intitule);
    query.bindValue(":statut", statut);
    query.bindValue(":nbr_participants", nbr_participants);

    return query.exec();
}

bool Formation::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FORMATIONS WHERE ID = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* Formation::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATIONS");
    return model;
}

// ------------------ FormationService ---------------------

bool FormationService::ajouterEvaluation(int formationId, int participantId, double pourcentage, const QString &commentaire)
{
    QSqlQuery query;

    query.prepare("INSERT INTO EVALUATION (ID_FORMATION, PARTICIPANT_ID, POURCENTAGE, COMMENTAIRE) "
                  "VALUES (:ID_FORMATION, :PARTICIPANT_ID, :POURCENTAGE, :COMMENTAIRE)");

    query.bindValue(":ID_FORMATION", formationId);
    query.bindValue(":PARTICIPANT_ID", participantId);
    query.bindValue(":POURCENTAGE", pourcentage);
    query.bindValue(":COMMENTAIRE", commentaire);

    if (!query.exec()) {
        qDebug() << "Erreur SQL (ajouterEvaluation):" << query.lastError().text();
        return false;
    }

    return true;
}




QSqlQueryModel* FormationService::triParDate()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATIONS ORDER BY DATES ASC");
    return model;
}

QSqlQueryModel* FormationService::triParDuree()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATIONS ORDER BY DUREE DESC");
    return model;
}

QSqlQueryModel* FormationService::rechercheAvancee(const QString &participant, const QDate &date, int duree)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM FORMATIONS WHERE PARTICIPANT LIKE :participant AND DATES = TO_DATE(:date, 'YYYY-MM-DD') AND DUREE = :duree");
    query.bindValue(":participant", "%" + participant + "%");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":duree", duree);
    query.exec();
    model->setQuery(std::move(query));
    return model;
}

bool FormationService::exporterPDF(const QList<Formation> &formations)
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, QObject::tr("Enregistrer le PDF"), "", QObject::tr("Fichiers PDF (*.pdf)"));
    if (filePath.isEmpty()) return false;

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);
    QPainter painter(&writer);
    if (!painter.isActive()) return false;

    int y = 100;
    for (const Formation &f : formations) {
        painter.drawText(50, y, QString("ID: %1 | Date: %2 | Intitulé: %3 | Participants: %4")
                                    .arg(f.getId())
                                    .arg(f.getDate())
                                    .arg(f.getIntitule())
                                    .arg(f.getNbrParticipants()));
        y += 30;
    }

    painter.end();
    return true;
}

int FormationService::compterFormations()
{
    QSqlQuery query("SELECT COUNT(*) FROM FORMATIONS");
    return query.next() ? query.value(0).toInt() : 0;
}

double FormationService::tauxParticipation()
{
    QSqlQuery total("SELECT COUNT(*) FROM PRESENCE");
    QSqlQuery presentes("SELECT COUNT(*) FROM PRESENCE WHERE PRESENT = 1");

    if (total.next() && presentes.next()) {
        double t = total.value(0).toDouble();
        double p = presentes.value(0).toDouble();
        return t > 0 ? (p / t) * 100.0 : 0;
    }
    return 0;
}

QSqlQueryModel* FormationService::afficherPresence()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PRESENCE");
    return model;
}

double FormationService::evaluerParticipant(int idFormation)
{
    QSqlQuery query;
    query.prepare("SELECT AVG(POURCENTAGE) FROM EVALUATION WHERE FORMATION_ID = :id");
    query.bindValue(":id", idFormation);
    query.exec();
    return query.next() ? query.value(0).toDouble() : 0.0;
}

QSqlQueryModel* FormationService::afficherStatistiques()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT F.INTITULE, P.PRESENCE, COUNT(*) AS Nombre "
                    "FROM PARTICIPATIONS P "
                    "JOIN FORMATIONS F ON P.FORMATION_ID = F.ID "
                    "GROUP BY F.INTITULE, P.PRESENCE");
    return model;
}

QList<Formation> FormationService::obtenirFormations()
{
    QList<Formation> liste;
    QSqlQuery query("SELECT * FROM FORMATIONS");

    while (query.next()) {
        Formation f(
            query.value("ID").toInt(),
            query.value("DATES").toString(),
            query.value("DUREE").toInt(),
            query.value("PARTICIPANT").toString(),
            query.value("INTITULE").toString(),
            query.value("STATUT").toString(),
            query.value("NBR_PARTICIPANTS").toInt()
            );
        liste.append(f);
    }

    return liste;
}
