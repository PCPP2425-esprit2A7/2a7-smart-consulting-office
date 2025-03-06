#include "Client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


Client::Client(int id, const std::string &name, const std::string &address,
               const std::string &phone, const std::string &email,
               const std::string &nom_entreprise, int nbr_consultation)
    : id(id), name(name), address(address), phone(phone), email(email),
    nom_entreprise(nom_entreprise), nbr_consultation(nbr_consultation)
{
}


bool Client::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO clients (id, name, address, phone, email, nom_entreprise, nbr_consultation) "
                  "VALUES (:id, :name, :address, :phone, :email, :nom_entreprise, :nbr_consultation)");

    query.bindValue(":id", id);
    query.bindValue(":name", QString::fromStdString(name));
    query.bindValue(":address", QString::fromStdString(address));
    query.bindValue(":phone", QString::fromStdString(phone));
    query.bindValue(":email", QString::fromStdString(email));
    query.bindValue(":nom_entreprise", QString::fromStdString(nom_entreprise));
    query.bindValue(":nbr_consultation", nbr_consultation);

    if (!query.exec()) {
        qDebug() << "Erreur SQL (ajouter) :" << query.lastError().text();
        return false;
    }
    return true;
}


QSqlQueryModel* Client::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM clients");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL (afficher) :" << model->lastError().text();
    }
    return model;
}


bool Client::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM clients WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur SQL (supprimer) :" << query.lastError().text();
        return false;
    }
    return true;
}
