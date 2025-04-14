#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "tache.h"
#include <QDebug>
#include <QVBoxLayout>
#include "calendrier.h"
#include "PieChartWidget.h"
#include <QDialog>
#include <QTableView>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialisation du modèle de tâches
    QSqlQueryModel *model = t.afficher();
    qDebug() << "Nombre de taches :" << model->rowCount();
    ui->aff->setModel(model);

    // Initialisation du calendrier
    calendar = new Calendrier();
    calendar->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    calendar->setWindowTitle("Task Calendar");

    // Connexion explicite du bouton calendrier
    connect(ui->calendarButton, &QPushButton::clicked, this, &MainWindow::on_calendarButton_clicked);
}

MainWindow::~MainWindow()
{
    delete calendar; // Nettoyage du calendrier
    delete ui;
}

void MainWindow::on_calendarButton_clicked()
{

        calendar->show();
        calendar->raise();  // Bring to front
        calendar->activateWindow();  // Give focus
        calendar->loadTasks();

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
        // Réinitialiser les champs après ajout
        ui->nom->clear();
        ui->description->clear();
        ui->priorite->clear();
        ui->statut->clear();
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
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide (nombre positif).");
        return;
    }

    if (!tache::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Aucune tâche trouvée avec cet ID.");
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
        QMessageBox::warning(this, "Erreur", "ID invalide.");
        return;
    }

    if (!tache::exists(id)) {
        QMessageBox::warning(this, "Erreur", "Tâche introuvable.");
        return;
    }

    QString nom = ui->nom->text().trimmed();
    QString description = ui->description->text().trimmed();
    QDate datee = ui->datee->date();
    QString priorite = ui->priorite->text().trimmed();
    QString statut = ui->statut->text().trimmed();

    if (t.update(id, nom, description, datee, priorite, statut)) {
        QMessageBox::information(this, "Succès", "Tâche mise à jour.");
        ui->aff->setModel(t.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la mise à jour.");
    }
}

void MainWindow::on_sup_clicked()
{
    QString idText = ui->idedit->text();
    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide.");
        return;
    }

    if (QMessageBox::question(this, "Confirmation",
                              "Voulez-vous vraiment supprimer cette tâche?",
                              QMessageBox::Yes|QMessageBox::No) == QMessageBox::No) {
        return;
    }

    if (t.remove(id)) {
        QMessageBox::information(this, "Succès", "Tâche supprimée.");
        ui->aff->setModel(t.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression.");
    }
}

void MainWindow::on_viewhistory_clicked()
{
    QString idText = ui->idedit->text();
    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || id <= 0) {
        QScopedPointer<QSqlQueryModel> historyModel(tache::gettHistory());
        if (historyModel && historyModel->rowCount() > 0) {
            QDialog historyDialog(this);
            historyDialog.setWindowTitle("Historique des modifications");
            historyDialog.resize(800, 400);

            QTableView* historyView = new QTableView(&historyDialog);
            historyView->setModel(historyModel.data());
            historyView->resizeColumnsToContents();

            QVBoxLayout layout(&historyDialog);
            layout.addWidget(historyView);

            historyDialog.exec();
        }
        return ;
    }

    QScopedPointer<QSqlQueryModel> historyModel(tache::getHistory(id));
    if (historyModel && historyModel->rowCount() > 0) {
        QDialog historyDialog(this);
        historyDialog.setWindowTitle("Historique des modifications");
        historyDialog.resize(800, 400);

        QTableView* historyView = new QTableView(&historyDialog);
        historyView->setModel(historyModel.data());
        historyView->resizeColumnsToContents();

        QVBoxLayout layout(&historyDialog);
        layout.addWidget(historyView);

        historyDialog.exec();
    } else {
        QMessageBox::information(this, "Information", "Aucun historique disponible.");
    }
}

void MainWindow::on_tri_clicked()
{
    tache t;
    QString critere = ui->Trie->currentText().toLower();

    QString ass = ui->ass->currentText().toLower();



    QSqlQueryModel* model = t.trier(critere,ass);
    if (model) {
        ui->aff->setModel(model);
        ui->aff->resizeColumnsToContents();
    } else {
        QMessageBox::warning(this, "Erreur", "Échec du tri.");
    }
}

void MainWindow::on_pdf_clicked()
{
    QString defaultName = QString("taches_%1.pdf").arg(QDate::currentDate().toString("yyyyMMdd"));
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

    tache t;
    if (t.genererPDF(fichierPDF)) {
        QMessageBox::information(this, "Succès", "PDF généré avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la génération du PDF.");
    }
}

void MainWindow::on_stat_clicked()
{
    tache t;
    QMap<QString, int> stats = t.obtenirStatistiques();

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
        ui->aff->setModel(t.afficher());
        return;
    }

    tache t;
    QSqlQueryModel* model = t.rechercher(valeur);
    if (model) {
        ui->aff->setModel(model);
        ui->aff->resizeColumnsToContents();
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la recherche.");
    }
}
