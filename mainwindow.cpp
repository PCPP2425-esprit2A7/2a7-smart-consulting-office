#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connecting buttons to their respective functions
    connect(ui->btnAjouter, &QPushButton::clicked, this, &MainWindow::ajouterClient);
    connect(ui->btnAfficher, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
        afficherClients();
    });
    connect(ui->btnAfficher_1, &QPushButton::clicked, this, &MainWindow::afficherClients);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &MainWindow::supprimerClient);
    connect(ui->btnModifier, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
    }); // Added update button
    connect(ui->btnConfirmer, &QPushButton::clicked, this, &MainWindow::modifierClient);
    connect(ui->btnNext, &QPushButton::clicked, this, &MainWindow::nextPage);
    connect(ui->btnPrev, &QPushButton::clicked, this, &MainWindow::prevPage);

    afficherClients(); // Load initial client list
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ajouterClient()
{
    QString name = ui->lineEdit_name->text();
    QString address = ui->lineEdit_address->text();
    QString phone = ui->lineEdit_phone->text();
    QString email = ui->lineEdit_email->text();
    QString nomEntreprise = ui->lineEdit_nom_entreprise->text();
    int nbr_consultation = ui->lineEdit_nbr_consultation->text().toInt();

    Client client(0, name, address, phone, email, nomEntreprise, nbr_consultation);

    if (client.ajouter()) {
        QMessageBox::information(this, "Succès", "Client ajouté !");
        afficherClients();  // Refresh table view
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du client.");
    }
}

void MainWindow::afficherClients()
{
    Client client(0, "", "", "", "", "", 0);
    ui->tableView->setModel(client.afficher());  // Update the model in the table view
}

void MainWindow::supprimerClient()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Suppression", "Veuillez sélectionner un client à supprimer.");
        return;
    }

    QModelIndex index = selectedRows.first();
    int id = index.sibling(index.row(), 0).data().toInt(); // Get ID from first column

    Client client(0, "", "", "", "", "", 0);
    if (client.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Client supprimé !");
        afficherClients();  // Refresh table view
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du client.");
    }
}

// ✅ **New Update Function**
void MainWindow::modifierClient()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Veuillez sélectionner un client à modifier.");
        return;
    }

    QModelIndex index = selectedRows.first();
    int id = index.sibling(index.row(), 0).data().toInt(); // Get ID from first column

    // Get new values from input fields
    QString name = ui->lineEdit_name_2->text();
    QString address = ui->lineEdit_address_2->text();
    QString phone = ui->lineEdit_phone_2->text();
    QString email = ui->lineEdit_email_2->text();
    QString nomEntreprise = ui->lineEdit_nom_entreprise_2->text();
    int nbr_consultation = ui->lineEdit_nbr_consultation->text().toInt();

    Client client(id, name, address, phone, email, nomEntreprise, nbr_consultation);

    if (client.modifier(id)) {
        QMessageBox::information(this, "Succès", "Client modifié avec succès.");
        afficherClients();  // Refresh Table
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du client.");
    }
}

void MainWindow::nextPage() {
    int currentIndex = ui->stackedWidget->currentIndex();
    int pageCount = ui->stackedWidget->count();

    if (currentIndex < pageCount - 1) {
        ui->stackedWidget->setCurrentIndex(currentIndex + 1);
    }
}

void MainWindow::prevPage() {
    int currentIndex = ui->stackedWidget->currentIndex();

    if (currentIndex > 0) {
        ui->stackedWidget->setCurrentIndex(currentIndex - 1);
    }
}
