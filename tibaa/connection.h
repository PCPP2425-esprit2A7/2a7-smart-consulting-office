#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
public:
    connection();
    bool createconnect();
    static QSqlDatabase get_database();
};

#endif // CONNECTION_H
