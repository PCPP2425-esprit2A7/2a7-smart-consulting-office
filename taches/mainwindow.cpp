#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "tache.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlQueryModel *model = t.afficher();
    qDebug() << "Nombre de taches :" << model->rowCount();
    ui->aff->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajoute_clicked()
{
    QString nom = ui->nom->text().trimmed();
    QString description = ui->description->text().trimmed();
    QDate datee = ui->datee->date();
    QString priorite = ui->priorite->text().trimmed();
    QString statut = ui->statut->text().trimmed();

    if (nom.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    tache newTache(nom, description, datee, priorite, statut);

    if (newTache.create()) {
        QMessageBox::information(this, "Succès", "La tâche a été ajoutée avec succès !");
        ui->aff->setModel(newTache.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la tâche.");
    }
}

void MainWindow::on_recuperer_clicked()
{
    QString idText = ui->idedit->text();

    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    if (!tache::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Tâche non trouvée.");
        return;
    }
    tache t = tache::read(id);
    ui->nom->setText(t.getNom());
    ui->description->setText(t.getDescription());
    ui->datee->setDate(t.getDatee());
    ui->priorite->setText(t.getPriorite());
    ui->statut->setText(t.getStatut());
}

void MainWindow::on_modifier_clicked()
{
    QString idText = ui->idedit->text();
    bool ok;
    int id = idText.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }
    if (!tache::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Tâche non trouvée.");
        return;
    }
    QString nom = ui->nom->text().trimmed();
    QString description = ui->description->text().trimmed();
    QDate datee = ui->datee->date();
    QString priorite = ui->priorite->text().trimmed();
    QString statut = ui->statut->text().trimmed();

    tache t;
    if (t.update(id, nom, description, datee, priorite, statut)) {
        QMessageBox::information(this, "Succès", "La tâche a été modifiée avec succès.");
        ui->aff->setModel(t.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier la tâche.");
    }
}

void MainWindow::on_sup_clicked()
{
    QString idText = ui->idedit->text();

    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    tache t;
    if (t.remove(id)) {
        QMessageBox::information(this, "Succès", "Tâche supprimée avec succès.");
        ui->aff->setModel(t.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression de la tâche.");
    }
}
