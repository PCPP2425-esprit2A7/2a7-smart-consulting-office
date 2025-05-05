#include "consultants.h"
#include <QDebug>

consultants::consultants()
{
}

bool consultants::Ajouterconsultants()
{
    QSqlQuery query;
    query.prepare("INSERT INTO consultants (NOM_CONS, PRENOM_CONS, EMAIL, TEL, CATEGORIE, MDP, HEURES, QUESTION, REPONSE) "
                  "VALUES (:NOM_CONS, :PRENOM_CONS, :EMAIL, :TEL, :CATEGORIE, :MDP, :HEURES, :QUESTION, :REPONSE)");

     //pour associer les valeurs des attributs de la classe aux colonnes de la base ,eviter l'injection
    query.bindValue(":NOM_CONS", NOM_CONS);
    query.bindValue(":PRENOM_CONS", PRENOM_CONS);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":TEL", QVariant(TEL).toInt());  // Ensure TEL is passed as an integer //Pour éviter des erreurs de type TEL est converti explicitement en int, et HEURES en double
    query.bindValue(":CATEGORIE", CATEGORIE);
    query.bindValue(":MDP", MDP);
    query.bindValue(":HEURES", QVariant(HEURES).toInt());  // Ensure HEURES is passed as a double
    query.bindValue(":QUESTION", QUESTION);
    query.bindValue(":REPONSE", REPONSE);

    // Debugging output
    qDebug() << "Query:" << query.lastQuery(); // utilisé pour afficher la requête et ses valeurs liées
    qDebug() << "Bound values:" << query.boundValues();

    if (!query.exec()) {//exécute la requête et retourne true en cas de succès, false en cas d’échec
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel *consultants::Afficherconsultants()
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    modal->setQuery("SELECT ID_CONS, NOM_CONS, PRENOM_CONS, EMAIL, TEL, CATEGORIE, MDP, HEURES, QUESTION, REPONSE FROM consultants");
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CONS"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_CONS"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_CONS"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    modal->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL"));
    modal->setHeaderData(5, Qt::Horizontal, QObject::tr("CATEGORIE"));
    modal->setHeaderData(6, Qt::Horizontal, QObject::tr("MDP"));
    modal->setHeaderData(7, Qt::Horizontal, QObject::tr("HEURES"));
    modal->setHeaderData(8, Qt::Horizontal, QObject::tr("QUESTION"));
    modal->setHeaderData(9, Qt::Horizontal, QObject::tr("REPONSE"));
    return modal;
}

bool consultants::Modifierconsultants()
{
    QSqlQuery query;
    query.prepare("UPDATE consultants SET NOM_CONS = :NOM_CONS, PRENOM_CONS = :PRENOM_CONS, EMAIL = :EMAIL, TEL = :TEL, CATEGORIE = :CATEGORIE, MDP = :MDP, HEURES = :HEURES, QUESTION = :QUESTION, REPONSE = :REPONSE WHERE ID_CONS = :ID_CONS");

    // Bind values with explicit casting
    query.bindValue(":NOM_CONS", NOM_CONS);
    query.bindValue(":PRENOM_CONS", PRENOM_CONS);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":TEL", QVariant(TEL).toInt());  // Explicitly cast TEL to int
    query.bindValue(":CATEGORIE", CATEGORIE);
    query.bindValue(":MDP", MDP);
    query.bindValue(":HEURES", QVariant(HEURES).toInt());  // Explicitly cast HEURES to double
    query.bindValue(":QUESTION", QUESTION);
    query.bindValue(":REPONSE", REPONSE);
    query.bindValue(":ID_CONS", ID_CONS);

    // Debugging output
    qDebug() << "Query:" << query.lastQuery();
    qDebug() << "Bound values:" << query.boundValues();

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error:" << query.lastError().text();
        return false;
    }

    return true;
}

bool consultants::Supprimerconsultants(const QString &ID_CONS)
{
    QSqlQuery query;
    query.prepare("DELETE FROM consultants WHERE ID_CONS = :ID_CONS");
    query.bindValue(":ID_CONS", ID_CONS);
    return query.exec();
}
