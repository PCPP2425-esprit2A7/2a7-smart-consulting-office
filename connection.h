#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


class Connection
{
private :
    QSqlDatabase db;
public:
    Connection();
    bool createconnect();
    void closeConnection();
    static QSqlDatabase get_database();
};

#endif // CONNECTION_H
