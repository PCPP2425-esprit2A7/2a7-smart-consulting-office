#include "tache.h"

// parameterized constructor
Tache::Tache(QString nom, QString description, QString datee, int priorite, QString statut)
{
    this->nom = nom;
    this->description = description;
    this->datee = datee;
    this->priorite = priorite;
    this->statut = statut;
}

// default constructor
Tache::Tache()
{
    nom = "";
    description = "";
    datee = "";
    priorite = 0;
    statut = "";
}

/* definition of getters */
QString Tache::getNom(){
    return nom;
}
QString Tache::getDescription(){
    return description;
}
QString Tache::getDatee(){
    return datee;
}
int Tache::getPriorite(){
    return priorite;
}
QString Tache::getStatut(){
    return statut;
}

/* definition of setters */
void Tache::setNom(QString nom){
    this->nom = nom;
}
void Tache::setDescription(QString description){
    this->description = description;
}
void Tache::setDatee(QString datee){
    this->datee = datee;
}
void Tache::setPriorite(int priorite){
    this->priorite = priorite;
}
void Tache::setStatut(QString statut){
    this->statut = statut;
}

/* AFFICHAGE */
QSqlQueryModel* Tache::afficher_tous_les_clients(){
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT NOM, DESCRIPTION, DATEE, PRIORITE, STATUT FROM TACHE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATEE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIORITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));

    return model;
}

/* ADD */
bool Tache::ajouter_client() {
    QSqlQuery query;
    query.prepare("INSERT INTO TACHE (NOM, DESCRIPTION, DATEE, PRIORITE, STATUT)"
                  "VALUES (:NOM, :DESCRIPTION, :DATEE, :PRIORITE, :STATUT)");
    query.bindValue(":NOM", nom);
    query.bindValue(":DESCRIPTION", description);
    query.bindValue(":DATEE", datee);
    query.bindValue(":PRIORITE", priorite);
    query.bindValue(":STATUT", statut);
    return query.exec();
}

/* DELETE */
bool Tache::supprimer_client(QString nom) {
    QSqlQuery query;
    query.prepare("DELETE FROM TACHE WHERE NOM = :nom");
    query.bindValue(0, nom);
    if (query.exec()) {
        int numRowsAffected = query.numRowsAffected();

        if (numRowsAffected > 0) {
            qDebug() << "Tâche avec NOM" << nom << "supprimée";
            return true;
        } else {
            qDebug() << "Il n'y a pas de tâche avec ce NOM" << nom;
            return false;
        }
    } else {
        qDebug() << "Erreur lors de la suppression de la tâche avec NOM" << nom << "Error:" << query.lastError().text();
        return false;
    }
}

/* UPDATE */
bool Tache::modifier_client(QString nom, QString description, QString datee, int priorite, QString statut) {
    QSqlQuery query;
    query.prepare("UPDATE TACHE SET DESCRIPTION = :description, DATEE = :datee, PRIORITE = :priorite, STATUT = :statut WHERE NOM = :nom");
    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":datee", datee);
    query.bindValue(":priorite", priorite);
    query.bindValue(":statut", statut);
    if (!query.exec()) {
        // qDebug() << "Query execution error:" << query.lastError().text();
    }
    return query.exec();
}
