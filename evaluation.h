// Dans evaluation.h

#ifndef EVALUATION_H
#define EVALUATION_H

#include <QString>
#include <QVector>

class Evaluation
{
public:
    // Attributs de la classe
    int id;
    int idFormation;
    int participantId;
    double pourcentage;
    QString commentaire;

    // Constructeurs
    Evaluation(); // Constructeur par défaut
    Evaluation(int id, int idFormation, int participantId, double pourcentage, const QString &commentaire);

    // Getters
    int getId() const;
    int getIdFormation() const;
    int getParticipantId() const;
    double getPourcentage() const;
    QString getCommentaire() const;

    // Setters
    void setId(int newId);
    void setIdFormation(int newIdFormation);
    void setParticipantId(int newParticipantId);
    void setPourcentage(double newPourcentage);
    void setCommentaire(const QString &newCommentaire);

    // Méthodes pour gérer les évaluations dans la base de données
    bool ajouterEvaluation();
    bool modifierEvaluation();
    bool supprimerEvaluation();

    // Méthode statique pour récupérer toutes les évaluations d'une formation
    // Déclaration avec argument par défaut
    static QVector<Evaluation> afficherEvaluations(int idFormation, int participantId = -1);
};

#endif // EVALUATION_H

