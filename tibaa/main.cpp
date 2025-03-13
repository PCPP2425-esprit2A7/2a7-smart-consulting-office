#include "mainwindow.h"
#include <QApplication>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialize the database connection
    Connection conn;
    if (!conn.createconnect()) {
        qDebug() << "Failed to connect to the database.";
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
