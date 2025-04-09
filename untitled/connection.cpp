#include "connection.h"

Connection::Connection()
{
}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("consulting"); // Inserer le nom de la source de données
    db.setUserName("mariem");        // Inserer nom de l'utilisateur
    db.setPassword("2004");          // Inserer mot de passe de cet utilisateur

    if (db.open())
        test = true;

    return test;
}

QSqlDatabase Connection::get_database()
{
    return QSqlDatabase::database(); // Return the default database connection
}
