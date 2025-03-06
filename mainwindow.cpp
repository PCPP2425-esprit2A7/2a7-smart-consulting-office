#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->btnAjouter, &QPushButton::clicked, this, &MainWindow::ajouterClient);
    connect(ui->btnAfficher_1, &QPushButton::clicked, this, &MainWindow::afficherClients);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &MainWindow::supprimerClient);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ajouterClient()
{
    int id = ui->lineEdit_id->text().toInt();
    QString name = ui->lineEdit_name->text();
    QString address = ui->lineEdit_address->text();
    QString phone = ui->lineEdit_phone->text();
    QString email = ui->lineEdit_email->text();
    QString nomEntreprise = ui->lineEdit_nom_entreprise->text();
    int nbrConsultation = ui->lineEdit_nbr_consultation->text().toInt();


    Client client(id, name.toStdString(), address.toStdString(), phone.toStdString(),
                  email.toStdString(), nomEntreprise.toStdString(), nbrConsultation);

    if (client.ajouter()) {
        QMessageBox::information(this, "Succès", "Client ajouté !");
        afficherClients();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du client.");
    }
}


void MainWindow::afficherClients()
{
    Client client(0, "", "", "", "", "", 0);
    ui->tableView->setModel(client.afficher());
}


void MainWindow::supprimerClient()
{
    int id = ui->lineEdit_id_suppression->text().toInt();

    Client client(0, "", "", "", "", "", 0);
    if (client.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Client supprimé !");
        afficherClients();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du client.");
    }
}
