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
QSqlDatabase Connection::get_database()
{
    return QSqlDatabase::database(); // Return the default database connection
}
