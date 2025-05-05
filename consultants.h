#ifndef CONSULTANTS_H
#define CONSULTANTS_H

#include "connection.h"
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class consultants
{
private:
    int ID_CONS;
    QString NOM_CONS;
    QString PRENOM_CONS;
    QString EMAIL;
    int TEL;
    QString CATEGORIE;
    QString MDP;
    int HEURES;
    QString QUESTION;
    QString REPONSE;

public:
    consultants();
    consultants(int ID_CONS, QString NOM_CONS, QString PRENOM_CONS, QString EMAIL, int TEL, QString CATEGORIE, QString MDP, int HEURES, QString QUESTION, QString REPONSE)
    {// initialise un consultant avec toutes ses informations passées en paramètres
        this->ID_CONS = ID_CONS;
        this->NOM_CONS = NOM_CONS;
        this->PRENOM_CONS = PRENOM_CONS;
        this->EMAIL = EMAIL;
        this->TEL = TEL;
        this->CATEGORIE = CATEGORIE;
        this->MDP = MDP;
        this->HEURES = HEURES;
        this->QUESTION = QUESTION;
        this->REPONSE = REPONSE;
    }

    // Setters //permettent de modifier les valeurs des attributs
    void setID_CONS(int id) { ID_CONS = id; }
    void setNom(QString nom) { NOM_CONS = nom; }
    void setPrenom(QString prenom) { PRENOM_CONS = prenom; }
    void setEmail(QString email) { EMAIL = email; }
    void setTel(int tel) { TEL = tel; }
    void setCategorie(QString categorie) { CATEGORIE = categorie; }
    void setMdp(QString mdp) { MDP = mdp; }
    void setHeures(int heures) { HEURES = heures; }
    void setQuestion(QString question) { QUESTION = question; }
    void setReponse(QString reponse) { REPONSE = reponse; }

    // Getters //permettent de récupérer les valeurs des attributs d’un consultant
    int getID_CONS() { return ID_CONS; }
    QString getNom() { return NOM_CONS; }
    QString getPrenom() { return PRENOM_CONS; }
    QString getEmail() { return EMAIL; }
    int getTel() { return TEL; }
    QString getCategorie() { return CATEGORIE; }
    QString getMdp() { return MDP; }
    int getHeures() { return HEURES; }
    QString getQuestion() { return QUESTION; }
    QString getReponse() { return REPONSE; }

    bool Ajouterconsultants();
    QSqlQueryModel* Afficherconsultants();//indiquent que cette classe interagit avec une base de données via Qt SQL
    bool Modifierconsultants();
    bool Supprimerconsultants(const QString &ID_CONS);
};

#endif // CONSULTANTS_H
