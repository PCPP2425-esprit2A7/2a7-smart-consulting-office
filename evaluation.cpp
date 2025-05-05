#include "evaluation.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// Constructeur par défaut
Evaluation::Evaluation()
    : id(0), idFormation(0), participantId(0), pourcentage(0.0), commentaire("") {}

// Constructeur paramétré
Evaluation::Evaluation(int id, int idFormation, int participantId, double pourcentage, const QString &commentaire)
    : id(id), idFormation(idFormation), participantId(participantId), pourcentage(pourcentage), commentaire(commentaire) {}

// Getter pour l'ID de l'évaluation
int Evaluation::getId() const {
    return id;
}

// Getter pour l'ID de la formation
int Evaluation::getIdFormation() const {
    return idFormation;
}

// Getter pour l'ID du participant
int Evaluation::getParticipantId() const {
    return participantId;
}

// Getter pour le pourcentage
double Evaluation::getPourcentage() const {
    return pourcentage;
}

// Getter pour le commentaire
QString Evaluation::getCommentaire() const {
    return commentaire;
}

// Setter pour l'ID de l'évaluation
void Evaluation::setId(int newId) {
    id = newId;
}

// Setter pour l'ID de la formation
void Evaluation::setIdFormation(int newIdFormation) {
    idFormation = newIdFormation;
}

// Setter pour l'ID du participant
void Evaluation::setParticipantId(int newParticipantId) {
    participantId = newParticipantId;
}

// Setter pour le pourcentage
void Evaluation::setPourcentage(double newPourcentage) {
    pourcentage = newPourcentage;
}

// Setter pour le commentaire
void Evaluation::setCommentaire(const QString &newCommentaire) {
    commentaire = newCommentaire;
}

// Méthode pour ajouter une évaluation dans la base de données
bool Evaluation::ajouterEvaluation() {
    QSqlQuery query;
    query.prepare("INSERT INTO evaluations (id_formation, participant_id, pourcentage, commentaire) "
                  "VALUES (:id_formation, :participant_id, :pourcentage, :commentaire)");
    query.bindValue(":id_formation", idFormation);
    query.bindValue(":participant_id", participantId);
    query.bindValue(":pourcentage", pourcentage);
    query.bindValue(":commentaire", commentaire);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout de l'évaluation:" << query.lastError().text();
        return false;
    }
}




QVector<Evaluation> Evaluation::afficherEvaluations(int idFormation, int participantId) {
    QVector<Evaluation> evaluations;

    QSqlQuery query;
    if (participantId == -1) {
        query.prepare("SELECT id, id_formation, participant_id, pourcentage, commentaire FROM evaluations WHERE id_formation = :id_formation");
        query.bindValue(":id_formation", idFormation);
    } else {
        query.prepare("SELECT id, id_formation, participant_id, pourcentage, commentaire FROM evaluations WHERE id_formation = :id_formation AND participant_id = :participant_id");
        query.bindValue(":id_formation", idFormation);
        query.bindValue(":participant_id", participantId);
    }

    if (query.exec()) {
        while (query.next()) {
            Evaluation evaluation;
            evaluation.setId(query.value(0).toInt());
            evaluation.setIdFormation(query.value(1).toInt());
            evaluation.setParticipantId(query.value(2).toInt());
            evaluation.setPourcentage(query.value(3).toDouble());
            evaluation.setCommentaire(query.value(4).toString());
            evaluations.append(evaluation);
        }
    } else {
        qDebug() << "Erreur lors de la récupération des évaluations:" << query.lastError().text();
    }

    return evaluations;
}


bool Evaluation::modifierEvaluation() {
    QSqlQuery query;
    query.prepare("UPDATE evaluations SET pourcentage = :pourcentage, commentaire = :commentaire WHERE id_evaluation = :id");
    query.bindValue(":pourcentage", pourcentage);
    query.bindValue(":commentaire", commentaire);
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Évaluation modifiée avec succès!";
        return true;
    } else {
        qDebug() << "Erreur lors de la modification de l'évaluation:" << query.lastError().text();
        return false;
    }
}


bool Evaluation::supprimerEvaluation() {
    QSqlQuery query;
    query.prepare("DELETE FROM evaluations WHERE id_evaluation = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Évaluation supprimée avec succès!";
        return true;
    } else {
        qDebug() << "Erreur lors de la suppression de l'évaluation:" << query.lastError().text();
        return false;
    }
}
