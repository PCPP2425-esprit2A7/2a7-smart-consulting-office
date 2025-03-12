#include "Client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Client::Client(int id, const QString &name, const QString &address,
               const QString &phone, const QString &email,
               const QString &nom_entreprise, int nbr_consultation)
    : id(id), name(name), address(address), phone(phone), email(email),
    nom_entreprise(nom_entreprise), nbr_consultation(nbr_consultation)
{
}

bool Client::ajouter() {
    QSqlQuery query;

    query.prepare("INSERT INTO CLIENTS (NOMCOMPLET, ADRESSE, TELEPHONE, EMAIL, NOMENTREPRISE, NBR_CONSULTATIONS) "
                  "VALUES (:name, :address, :phone, :email, :nom_entreprise, :nbr_consultation)");

    query.bindValue(":name", name);
    query.bindValue(":address", address);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":nom_entreprise", nom_entreprise);
    query.bindValue(":nbr_consultation", nbr_consultation);

    if (!query.exec()) {
        qDebug() << "Erreur SQL (ajouter) :" << query.lastError().text();
        qDebug() << "Requête échouée :" << query.lastQuery();
        return false;
    }

    return true;
}

QSqlQueryModel* Client::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENTS");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL (afficher) :" << model->lastError().text();
    }
    return model;
}

bool Client::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENTS WHERE ID_CLIENT = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur SQL (supprimer) :" << query.lastError().text();
        return false;
    }
    return true;
}


bool Client::modifier(int id) {
    QSqlQuery query;

    query.prepare("UPDATE CLIENTS SET NOMCOMPLET = :name, ADRESSE = :address, TELEPHONE = :phone, "
                  "EMAIL = :email, NOMENTREPRISE = :nom_entreprise, NBR_CONSULTATIONS = :nbr_consultation "
                  "WHERE ID_CLIENT = :id");

    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":address", address);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":nom_entreprise", nom_entreprise);
    query.bindValue(":nbr_consultation", nbr_consultation);

    if (!query.exec()) {
        qDebug() << "Erreur SQL (modifier) :" << query.lastError().text();
        return false;
    }

    return true;
}
