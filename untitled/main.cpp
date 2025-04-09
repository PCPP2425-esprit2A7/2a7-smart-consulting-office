#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

// Fonction pour envoyer les rappels du calendrier
void sendCalendarReminders()
{
    // Implémentation de l'envoi des rappels
    QMessageBox::information(nullptr, "Rappels", "Vérification des rappels du calendrier...");
    // Ajoutez ici la logique d'envoi des rappels
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialisation de la connexion à la base de données
    Connection conn;
    if (!conn.createconnect()) {
        QMessageBox::critical(nullptr, "Database Error", "Échec de la connexion à la base de données !");
        return -1;
    }

    // Envoi des rappels au démarrage de l'application
    sendCalendarReminders();

    // Affichage de la fenêtre principale
    MainWindow w;
    w.show();

    return a.exec();
}
