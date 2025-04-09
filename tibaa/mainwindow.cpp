#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "piechartwidget.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "ressource.h"
#include <QDebug>
#include <QVBoxLayout>

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
    QString etat = ui->etat->currentText().toLower();
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
    ui->etat->setCurrentText(r.getEtat());
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
    QString etat = ui->etat->currentText().toLower();
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



void MainWindow::on_tri_clicked()
    {
        ressource r;
        QString critere = ui->Trie->currentText().toLower();
        bool ascendant = true; // Tri ascendant par défaut

        QSqlQueryModel* model = r.trier(critere, ascendant);
        if (model) {
            ui->aff->setModel(model);
            ui->aff->resizeColumnsToContents();
        } else {
            QMessageBox::warning(this, "Erreur", "Échec du tri.");
        }
    }

    void MainWindow::on_pdf_clicked()
    {
        QString defaultName = QString("ressource_%1.pdf").arg(QDate::currentDate().toString("yyyyMMdd"));
        QString fichierPDF = QFileDialog::getSaveFileName(
            this,
            "Enregistrer le PDF",
            defaultName,
            "Fichiers PDF (*.pdf)");

        if (fichierPDF.isEmpty()) {
            return;
        }

        if (!fichierPDF.endsWith(".pdf", Qt::CaseInsensitive)) {
            fichierPDF += ".pdf";
        }

        ressource r;
        if (r.genererPDF(fichierPDF)) {
            QMessageBox::information(this, "Succès", "PDF généré avec succès.");
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de la génération du PDF.");
        }
    }

    void MainWindow::on_stat_clicked()
    {
     ressource r;
        QMap<QString, int> stats = r.obtenirStatistiques();

        if (stats.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Aucune donnée statistique disponible.");
            return;
        }

        QDialog statDialog(this);
        statDialog.setWindowTitle("Statistiques des tâches");
        statDialog.resize(600, 600);

        PieChartWidget* chartWidget = new PieChartWidget(stats, &statDialog);

        QVBoxLayout layout(&statDialog);
        layout.addWidget(chartWidget);

        statDialog.exec();
    }

    void MainWindow::on_chercher_clicked()
    {
        QString valeur = ui->cherche->text().trimmed();

        if (valeur.isEmpty()) {
            ui->aff->setModel(r.afficher());
            return;
        }

         ressource r;
        QSqlQueryModel* model = r.rechercher(valeur);
        if (model) {
            ui->aff->setModel(model);
            ui->aff->resizeColumnsToContents();
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de la recherche.");
        }
    }





