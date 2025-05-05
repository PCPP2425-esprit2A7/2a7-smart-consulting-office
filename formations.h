#ifndef FORMATIONS_H
#define FORMATIONS_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QObject>

class Formation {
private:
    int id;
    QString dates;
    int duree;
    QString participant;
    QString intitule;
    QString statut;
    int nbr_participants;  // ✅ Nouveau champ ajouté

public:
    Formation();
    Formation(int id, QString dates, int duree, QString participant, QString intitule, QString statut, int nbr_participants);

    int getId() const;
    QString getDate() const;
    int getDuree() const;
    QString getParticipant() const;
    QString getIntitule() const;
    QString getStatut() const;
    int getNbrParticipants() const;  // ✅ Getter ajouté

    bool ajouter();
    bool modifier(int id);
    bool supprimer(int id);
    QSqlQueryModel* afficher();
};

#endif // FORMATIONS_H
