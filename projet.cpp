#include "projet.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QVariant>
#include <QTextStream>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;



projets::projets(int id, const QString &nom, const QString &desc, const QString &debut, const QString &fin, double bud, const QString &stat)
    : id_projet(id), nom_projet(nom), description(desc), date_debut(debut), date_fin(fin), budget(bud), status(stat) {}


projets::projets(){}


QSqlQueryModel* projets::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PROJETS");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL (afficher) :" << model->lastError().text();
    }
    return model;
}


bool projets::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO PROJETS (ID_PROJET, NOM, DESCRIPTION, DATEDEBUT, DATEFIN, BUDGET, STATUS) "
                  "VALUES (:id_projet, :nom, :desc, :debut, :fin, :bud, :stat)");

    query.bindValue(":id_projet", id_projet);
    query.bindValue(":nom", nom_projet);
    query.bindValue(":desc", description);
    query.bindValue(":debut", date_debut);
    query.bindValue(":fin", date_fin);
    query.bindValue(":bud", budget);
    query.bindValue(":stat", status);

    if (!query.exec()) {
        qDebug() << "Erreur SQL (ajouter) :" << query.lastError().text();
        return false;
    }
    return true;
}




bool projets::supprimer(int id_projet) {
    QSqlQuery query;
    query.prepare("DELETE FROM PROJETS WHERE ID_PROJET = :id");
    query.bindValue(":id", id_projet);

    qDebug() << "Tentative de suppression: ID =" << id_projet;

    if (!query.exec()) {
        qDebug() << "Erreur SQL (supprimer):" << query.lastError().text();  // Print SQL error
        return false;
    }

    qDebug() << "Suppression réussie pour ID:" << id_projet;
    return true;
}



bool projets::modifier(int id_projet) {
    QSqlQuery query;
    query.prepare("UPDATE PROJETS SET nom_projet = :nom, description = :desc, date_debut = :dateDebut, "
                  "date_fin = :dateFin, budget = :budget, status = :status WHERE id_projet = :id");

    query.bindValue(":id", id_projet);
    query.bindValue(":nom", nom_projet);
    query.bindValue(":desc", description);
    query.bindValue(":dateDebut", date_debut);
    query.bindValue(":dateFin", date_fin);
    query.bindValue(":budget", budget);
    query.bindValue(":status", status);

    qDebug() << "Query prepared: " << query.lastQuery();  // Check the query

    if (!query.exec()) {
        qDebug() << "Erreur SQL (modifier) :" << query.lastError().text();
        return false;
    }

    return true;
}

int projets::getProjectCountByStatus(const QString &status)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM projets WHERE STATUS = :status");
    query.bindValue(":status", status);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            qDebug() << "Statut:" << status << "| Count:" << count;
            return count;
        } else {
            qDebug() << "La requête a été exécutée mais aucun résultat.";
        }
    } else {
        qDebug() << "Erreur SQL:" << query.lastError().text();
    }

    return 0;
}







QSqlQueryModel* projets::trier() {
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM projets ORDER BY ID_PROJET ASC");


    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL (trier) :" << model->lastError().text();
        return nullptr;
    }


    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID Projet"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom Projet"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Début"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Fin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Budget"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Status"));

    return model;
}



QSqlQueryModel* projets::chercher(QString id) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM projets WHERE ID_PROJET = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        model->setQuery(std::move(query));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID Projet"));
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom Projet"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Début"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Fin"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Budget"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Status"));
    }

    return model;
}

bool projets::PDF() {

    QString filePath = QFileDialog::getSaveFileName(nullptr, QObject::tr("Save PDF"), "", QObject::tr("PDF Files (*.pdf)"));

    if (filePath.isEmpty()) {

        qDebug() << "User canceled the file save dialog.";
        return false;
    }


    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&writer);


    if (!painter.isActive()) {
        qDebug() << "Failed to initialize QPainter";
        return false;
    }


    painter.setFont(QFont("Arial", 16));
    painter.drawText(200, 50, "Liste des Projets");

    int y = 500;


    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(50, y, "ID");
    painter.drawText(300, y, "Nom");
    painter.drawText(900, y, "Description");
    painter.drawText(1800, y, "Début");
    painter.drawText(2400, y, "Fin");
    painter.drawText(3000, y, "Status");

    y += 200;
    painter.setFont(QFont("Arial", 7));


    QSqlQuery query("SELECT * FROM projets");
    while (query.next()) {
        painter.drawText(50, y, query.value(0).toString());
        painter.drawText(300, y, query.value(1).toString());
        painter.drawText(900, y, query.value(2).toString());
        painter.drawText(1800, y, query.value(3).toString());
        painter.drawText(2400, y, query.value(4).toString());
        painter.drawText(3000, y, query.value(5).toString());

        y += 200;
        if (y > writer.height() - 100) {
            writer.newPage();
            y = 100;
        }
    }

    painter.end();
    qDebug() << "PDF saved at:" << filePath;
    return true;
}

void projets::afficherProgressionASCII() {
    QSqlQuery query;
    query.prepare("SELECT STATUS, COUNT(*) FROM PROJETS GROUP BY STATUS");

    if (!query.exec()) {
        qDebug() << "Erreur SQL (ASCII):" << query.lastError().text();
        return;
    }

    cout << "\033[1m\033[4m\nTableau de Bord - Progression des Projets (ASCII)\n\033[0m\n";

    while (query.next()) {
        QString status = query.value(0).toString();
        int count = query.value(1).toInt();

        // Couleurs ASCII différentes par status
        QString colorCode;
        if (status == "Terminé")
            colorCode = "\033[1;32m";  // Vert
        else if (status == "En cours")
            colorCode = "\033[1;33m";  // Jaune
        else if (status == "Planifié")
            colorCode = "\033[1;34m";  // Bleu
        else
            colorCode = "\033[1;37m";  // Blanc

        cout << status.toStdString() << ": " << colorCode.toStdString();
        for (int i = 0; i < count; ++i) {
            cout << "|█";
        }
        cout << "\033[0m" << " (" << count << ")\n";
    }

    cout << endl;
}


