#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ajouterClient();  // Add a client
    void afficherClients(); // Display clients
    void supprimerClient(); // Delete a client

private:
    Ui::MainWindow *ui;
    Client *client;  // Client instance
};

#endif // MAINWINDOW_H
