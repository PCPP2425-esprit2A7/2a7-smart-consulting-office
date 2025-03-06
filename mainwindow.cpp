#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QIntValidator>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    if (c.check_data_base()) {
        ui->stock_table->setModel(montache.afficher_tous_les_taches());
    } else {
        qDebug() << "La base de données n'est pas ouverte.";
    }


    void MainWindow::on_add_val_clicked()
    {
        montache.setNom(ui->ref_s->text());
        montache.setDescription(ui->description_r_t->text());
        montache.setDatee(ui->dob_in_2->text());
        montache.setPriorite(ui->ref_s_2->text().toInt());
        montache.setStatut(ui->ref_s_3->text());
        ui->up_del_cin_in->setText(montache.getNom());

        if(montache.getNom().length() > 0 && montache.getStatut().length() > 0){
            ui->idcl_erreur->setText("");
            ui->telephone_erreur->setText("");
            if(montache.ajouter_tache()){
                ui->operations_clients->setCurrentWidget(ui->list);
                sendMail();
                ui->table_client->setModel(montache.afficher_tous_les_taches());
                ui->operations_clients->setCurrentWidget(ui->list);
                QMessageBox::information(nullptr, "Tache ajouté", QString(montache.getNom() + " a été ajouté à la table des clients"));
                ui->ref_s->clear();
                ui->description_r_t->clear();
                ui->dob_in_2->clear();
                ui->ref_s_2->clear();
                ui->ref_s_3->clear();
                on_refresh_clicked();
            }
            else{
                QMessageBox::information(nullptr, "Tache non ajouté", "Erreur 404");
            }
        }
        else {
            if(montache.getNom().length() == 0){
                ui->idcl_erreur->setText("Le nom ne peut pas être vide");
            }
            if(montache.getStatut().length() == 0){
                ui->telephone_erreur->setText("Le statut ne peut pas être vide");
            }
        }
    }

    void MainWindow::on_update_val_clicked()
    {
        QString up_idcl_in = ui->up_idcl_in->text();
        QString up_nom_in = ui->up_nom_in->text();
        QString up_prenom_in = ui->up_prenom_in->text();
        int up_age_in = ui->up_age_in->text().toInt();
        QString up_telephone_in = ui->up_telephone_in->text();
        QString up_email_in = ui->up_email_in->text();
        QString up_adresse_in = ui->up_adresse_in->text();
        int up_nbrprojets_in = ui->up_nbrprojets_in->text().toInt();

        if (monclient.modifier_client(up_idcl_in, up_nom_in, up_prenom_in, up_age_in, up_telephone_in, up_email_in, up_adresse_in, up_nbrprojets_in)){
            /*ui->table_client->setModel(monclient.afficher_tous_les_clients());
        ui->operations_clients->setCurrentWidget(ui->list);*/
            QMessageBox::information(nullptr, "Client mis à jour", QString("Les informations du client : " + up_idcl_in + " ont été mises à jour"));
        }
        else {
            QMessageBox::information(nullptr, "Erreur", QString("Les informations du client : " + up_idcl_in + " n'ont pas été mises à jour"));
        }
    }


    void MainWindow::on_refresh_clicked()
    {
        ui->table_client->setModel(monclient.afficher_tous_les_clients());
    }

    void MainWindow::on_addButton_clicked()
    {
        ui->operations_clients->setCurrentWidget(ui->add_stock);
    }

    void MainWindow::on_update_val_clicked()
    {
        QString up_nom_in = ui->ref_s_6->text();
        QString up_description_in = ui->description_r_t_2->text();
        QString up_datee_in = ui->dob_in_3->text();
        int up_priorite_in = ui->ref_s_4->text().toInt();
        QString up_statut_in = ui->ref_s_5->text();

        if (montache.modifier_client(up_nom_in, up_description_in, up_datee_in, up_priorite_in, up_statut_in)){
            /*ui->table_client->setModel(montache.afficher_tous_les_clients());
        ui->operations_clients->setCurrentWidget(ui->list);*/
            QMessageBox::information(nullptr, "Tâche mise à jour", QString("Les informations de la tâche : " + up_nom_in + " ont été mises à jour"));
        }
        else {
            QMessageBox::information(nullptr, "Erreur", QString("Les informations de la tâche : " + up_nom_in + " n'ont pas été mises à jour"));
        }
    }



    void MainWindow::on_updateButton_clicked()
    {
        QString nom = ui->ref_s_6->text();
        QSqlQuery query;
        query.prepare("SELECT * FROM TACHE WHERE NOM = :nom");
        query.bindValue(":nom", nom);

        if(query.exec()){
            while(query.next()){
                ui->ref_s_6->setText(query.value(0).toString());
                ui->description_r_t_2->setText(query.value(1).toString());
                ui->dob_in_3->setText(query.value(2).toString());
                ui->ref_s_4->setText(query.value(3).toString());
                ui->ref_s_5->setText(query.value(4).toString());
            }
        }
        ui->operations_clients->setCurrentWidget(ui->update_stock);
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    void MainWindow::on_pushbutton3_clicked()
    {
        QString nom = ui->up_idcl_in_2->text();
        /*ui->lineEdit->setReadOnly(false);
    ui->lineEdit->setEnabled(true);*/

        if (nom == "") {
            QMessageBox::warning(this, tr("Nom non valide"),
                                 tr("Veuillez entrer un nom de tâche valide."));
            return;
        }

        Tache t;
        bool supprimer_tache = t.supprimer_tache(nom);

        // Afficher un message en fonction du résultat
        if (supprimer_tache) {
            QMessageBox::information(this, tr("Suppression réussie"),
                                     tr("La tâche a été supprimée avec succès."));
        } else {
            QMessageBox::critical(this, tr("Erreur de suppression"),
                                  tr("La tâche n'a pas pu être supprimée. Vérifiez le nom de la tâche ou la connexion à la base de données."));
        }
    }

    void MainWindow::on_backtolist_clicked()
    {
        ui->operations_clients->setCurrentWidget(ui->list_stock));
    }
    void MainWindow::on_backtolist_2_clicked()
    {
        ui->operations_clients->setCurrentWidget(ui->list_stock);
    }
    void MainWindow::on_backtolist_3_clicked()
    {
        ui->operations_clients->setCurrentWidget(ui->list_stock);
    }
