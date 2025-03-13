#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "ressource.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlQueryModel *model = r.afficher();
    qDebug() << "Nombre de ressources :" << model->rowCount();
    ui->aff->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajoute_clicked()
{
    QString nom = ui->nom->text().trimmed();
    QString fournisseur = ui->fournisseur->text().trimmed();
    int cout = ui->cout->text().toInt();
    int quantite = ui->quantite->text().toInt();
    QString etat = ui->etat->text().trimmed();
    int tel_fournisseur = ui->tel_fournisseur->text().toInt();

    if (nom.isEmpty() || fournisseur.isEmpty() || etat.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    ressource newRessource(nom, fournisseur, cout, quantite, etat, tel_fournisseur);

    if (newRessource.create()) {
        QMessageBox::information(this, "Succès", "La ressource a été ajoutée avec succès !");
        ui->aff->setModel(newRessource.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la ressource.");
    }
}

void MainWindow::on_recuperer_clicked()
{
    QString idText = ui->idedit->text();

    bool ok;
    int id_res = idText.toInt(&ok);

    if (!ok || id_res <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    if (!ressource::exists(id_res)) {
        QMessageBox::warning(this, "Erreur", "Ressource non trouvée.");
        return;
    }
    ressource r = ressource::read(id_res);
    ui->nom->setText(r.getNom());
    ui->fournisseur->setText(r.getFournisseur());
    ui->cout->setText(QString::number(r.getCout()));
    ui->quantite->setText(QString::number(r.getQuantite()));
    ui->etat->setText(r.getEtat());
    ui->tel_fournisseur->setText(QString::number(r.getTelFournisseur()));
}

void MainWindow::on_modifier_clicked()
{
    QString idText = ui->idedit->text();
    bool ok;
    int id_res = idText.toInt(&ok);
    if (!ok || id_res <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }
    if (!ressource::exists(id_res)) {
        QMessageBox::warning(this, "Erreur", "Ressource non trouvée.");
        return;
    }
    QString nom = ui->nom->text().trimmed();
    QString fournisseur = ui->fournisseur->text().trimmed();
    int cout = ui->cout->text().toInt();
    int quantite = ui->quantite->text().toInt();
    QString etat = ui->etat->text().trimmed();
    int tel_fournisseur = ui->tel_fournisseur->text().toInt();

    ressource r;
    if (r.update(id_res, nom, fournisseur, cout, quantite, etat, tel_fournisseur)) {
        QMessageBox::information(this, "Succès", "La ressource a été modifiée avec succès.");
        ui->aff->setModel(r.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier la ressource.");
    }
}

void MainWindow::on_sup_clicked()
{
    QString idText = ui->idedit->text();

    bool ok;
    int id_res = idText.toInt(&ok);

    if (!ok || id_res <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    ressource r;
    if (r.remove(id_res)) {
        QMessageBox::information(this, "Succès", "Ressource supprimée avec succès.");
        ui->aff->setModel(r.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression de la ressource.");
    }
}
