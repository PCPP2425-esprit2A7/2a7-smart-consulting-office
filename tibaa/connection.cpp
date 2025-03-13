#include "connection.h"

Connection::connection()
{
}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("consulting"); // Insert the data source name
    db.setUserName("mariem"); // Insert the username
    db.setPassword("2004"); // Insert the password

    if (db.open())
        test = true;

    return test;
}

QSqlDatabase Connection::get_database()
{
    return QSqlDatabase::database();
}
