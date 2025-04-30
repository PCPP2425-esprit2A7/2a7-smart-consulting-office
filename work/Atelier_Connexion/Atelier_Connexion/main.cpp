#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "login.h"
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Available database drivers:" << QSqlDatabase::drivers();

    Login l;
    l.show();


    return a.exec();
}
