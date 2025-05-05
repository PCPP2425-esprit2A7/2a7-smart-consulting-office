#include "connection.h"

Connection::Connection() {
    db = QSqlDatabase::addDatabase("QODBC");
}

bool Connection::createconnect() {
    db.setDatabaseName("consulting");
    db.setUserName("mariem");
    db.setPassword("2004");

    if (!db.open()) {
        qDebug() << "Erreur de connexion:" << db.lastError().text();
        return false;
    }

    qDebug() << "Connexion réussie !";
    return true;
}

void Connection::closeConnection() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Connexion fermée.";
   }
}
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> 1ef526ce3d4a5b5ac7518f95db20ca4d5e511ce8
QSqlDatabase Connection::get_database()
{
    return QSqlDatabase::database(); // Return the default database connection
}
<<<<<<< HEAD
=======
>>>>>>> 00ca2d6ddb272cb69d6813b4c25604876d18434f
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af
>>>>>>> 1ef526ce3d4a5b5ac7518f95db20ca4d5e511ce8
