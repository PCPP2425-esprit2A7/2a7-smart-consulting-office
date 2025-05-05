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
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
    static QSqlDatabase get_database();
>>>>>>> 00ca2d6ddb272cb69d6813b4c25604876d18434f
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af
};

#endif // CONNECTION_H
