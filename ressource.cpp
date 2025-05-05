#include "ressource.h"
#include "connection.h"
#include "piechartwidget.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include <QPdfWriter>
#include <QPrinter>

#include <QPainter>
#include <QFile>
#include <QTextDocument>
#include <QDate>

ressource::ressource() : id_res(-1), cout(0), quantite(0), tel_fournisseur(0) {}

ressource::ressource(const QString &nom, const QString &fournisseur, int cout, int quantite, const QString &etat, int tel_fournisseur)
    : id_res(-1), nom(nom), fournisseur(fournisseur), cout(cout), quantite(quantite), etat(etat), tel_fournisseur(tel_fournisseur) {}

int ressource::getIdRes() const { return id_res; }
QString ressource::getNom() const { return nom; }
QString ressource::getFournisseur() const { return fournisseur; }
int ressource::getCout() const { return cout; }
int ressource::getQuantite() const { return quantite; }
QString ressource::getEtat() const { return etat; }
int ressource::getTelFournisseur() const { return tel_fournisseur; }

void ressource::setIdRes(int id_res) { this->id_res = id_res; }
void ressource::setNom(const QString &nom) { this->nom = nom; }
void ressource::setFournisseur(const QString &fournisseur) { this->fournisseur = fournisseur; }
void ressource::setCout(int cout) { this->cout = cout; }
void ressource::setQuantite(int quantite) { this->quantite = quantite; }
void ressource::setEtat(const QString &etat) { this->etat = etat; }
void ressource::setTelFournisseur(int tel_fournisseur) { this->tel_fournisseur = tel_fournisseur; }

bool ressource::exists(int id_res) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM RESSOURCES WHERE id_res = :id_res");
    query.bindValue(":id_res", id_res);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

bool ressource::create() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO RESSOURCES (nom, fournisseur, cout, quantite, etat, tel_fournisseur) "
                  "VALUES (:nom, :fournisseur, :cout, :quantite, :etat, :tel_fournisseur)");

    query.bindValue(":nom", nom);
    query.bindValue(":fournisseur", fournisseur);
    query.bindValue(":cout", cout);
    query.bindValue(":quantite", quantite);
    query.bindValue(":etat", etat);
    query.bindValue(":tel_fournisseur", tel_fournisseur);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion :" << query.lastError();
        return false;
    }

    id_res = query.lastInsertId().toInt();
    return true;
}

QSqlQueryModel* ressource::afficher() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RESSOURCES", db);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Fournisseur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Coût"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("État"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Téléphone Fournisseur"));

    return model;
}

bool ressource::remove(int id_res) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM RESSOURCES WHERE id_res = :id_res");
    query.bindValue(":id_res", id_res);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression :" << query.lastError();
        return false;
    }

    return true;
}

ressource ressource::read(int id_res) {
    ressource r;
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return r;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM RESSOURCES WHERE id_res = :id_res");
    query.bindValue(":id_res", id_res);

    if (query.exec() && query.next()) {
        r.setIdRes(query.value("id_res").toInt());
        r.setNom(query.value("nom").toString());
        r.setFournisseur(query.value("fournisseur").toString());
        r.setCout(query.value("cout").toInt());
        r.setQuantite(query.value("quantite").toInt());
        r.setEtat(query.value("etat").toString());
        r.setTelFournisseur(query.value("tel_fournisseur").toInt());
    }

    return r;
}

bool ressource::update(int id_res, const QString &nom, const QString &fournisseur, int cout, int quantite, const QString &etat, int tel_fournisseur) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE RESSOURCES SET nom = :nom, fournisseur = :fournisseur, cout = :cout, "
                  "quantite = :quantite, etat = :etat, tel_fournisseur = :tel_fournisseur "
                  "WHERE id_res = :id_res");

    query.bindValue(":nom", nom);
    query.bindValue(":fournisseur", fournisseur);
    query.bindValue(":cout", cout);
    query.bindValue(":quantite", quantite);
    query.bindValue(":etat", etat);
    query.bindValue(":tel_fournisseur", tel_fournisseur);
    query.bindValue(":id_res", id_res);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour :" << query.lastError();
        return false;
    }

    return true;
}

QSqlQueryModel* ressource::trier(const QString& critere, bool ascendant) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QString queryString = "SELECT * FROM RESSOURCES";
    if (!critere.isEmpty()) {
        queryString += " ORDER BY " + critere;
        if (!ascendant) {
            queryString += " DESC";
        }
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(queryString, db);
    return model;
}

QSqlQueryModel* ressource::rechercher(const QString& valeur) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QString queryString;
    if (valeur.toInt() > 0) {
        queryString = "SELECT * FROM RESSOURCES WHERE id_res = :valeur";
    } else {
        queryString = "SELECT * FROM RESSOURCES WHERE nom LIKE :valeur OR fournisseur LIKE :valeur OR etat LIKE :valeur";
    }

    QSqlQuery query(db);
    query.prepare(queryString);

    if (valeur.toInt() > 0) {
        query.bindValue(":valeur", valeur);
    } else {
        query.bindValue(":valeur", "%" + valeur + "%");
    }

    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche :" << query.lastError();
        return nullptr;
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(query));
    return model;
}

QString ressource::genererContenuPDF() {
    QString html = R"(
    <html>
    <head>
        <style>
            body { font-family: Arial, sans-serif; margin: 0; padding: 0; }
            h1 { text-align: center; color: #333; margin-bottom: 10px; font-size: 18px; }
            table { width: 100%; border-collapse: collapse; }
            th, td { border: 1px solid #ddd; padding: 8px; text-align: left; font-size: 9px; }
            th { background-color: #f2f2f2; font-weight: bold; }
            .footer { text-align: center; font-size: 10px; color: #666; margin-top: 15px; }
        </style>
    </head>
    <body>
        <h1>Rapport des Ressources</h1>
        <table>
            <tr>
                <th>ID</th><th>Nom</th><th>Fournisseur</th><th>Coût</th>
                <th>Quantité</th><th>État</th><th>Téléphone Fournisseur</th>
            </tr>
    )";

    QSqlQuery query("SELECT * FROM RESSOURCES");
    while (query.next()) {
        html += QString("<tr>"
                        "<td>%1</td><td>%2</td><td>%3</td><td>%4</td>"
                        "<td>%5</td><td>%6</td><td>%7</td>"
                        "</tr>")
                    .arg(query.value(0).toInt())
                    .arg(query.value(1).toString())
                    .arg(query.value(2).toString())
                    .arg(query.value(3).toInt())
                    .arg(query.value(4).toInt())
                    .arg(query.value(5).toString())
                    .arg(query.value(6).toInt());
    }

    html += QString(R"(
        </table>
        <div class='footer'>
            <p>Généré le %1</p>
        </div>
    </body>
    </html>
    )").arg(QDate::currentDate().toString("dd/MM/yyyy"));

    return html;
}

bool ressource::genererPDF(const QString& fichierPDF) {
    QTextDocument document;
    document.setHtml(genererContenuPDF());

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setOutputFileName(fichierPDF);
    printer.setPageMargins(QMarginsF(5, 5, 5, 5));

    document.print(&printer);
    return QFile::exists(fichierPDF);
}

QMap<QString, int> ressource::obtenirStatistiques() {
    QMap<QString, int> stats;
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return stats;
    }

    QSqlQuery query(db);
    query.prepare("SELECT etat, COUNT(*) FROM RESSOURCES GROUP BY etat");

    if (query.exec()) {
        while (query.next()) {
            stats.insert(query.value(0).toString(), query.value(1).toInt());
        }
    }

    return stats;
}
