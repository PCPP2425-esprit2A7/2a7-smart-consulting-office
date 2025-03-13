#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialize the database connection
    Connection conn;
    if (!conn.createconnect()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to connect to the database!");
        return -1; // Exit the application if the database connection fails
    }

    MainWindow w;
    w.show();
    return a.exec();
}
