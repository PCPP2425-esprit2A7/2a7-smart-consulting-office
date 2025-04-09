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

// Constructeur par défaut
ressource::ressource() : id_res(-1), cout(0), quantite(0), tel_fournisseur(0) {}

// Constructeur paramétré
ressource::ressource(const QString &nom, const QString &fournisseur, int cout, int quantite, const QString &etat, int tel_fournisseur)
    : id_res(-1), nom(nom), fournisseur(fournisseur), cout(cout), quantite(quantite), etat(etat), tel_fournisseur(tel_fournisseur) {}

// Getters
int ressource::getIdRes() const { return id_res; }
QString ressource::getNom() const { return nom; }
QString ressource::getFournisseur() const { return fournisseur; }
int ressource::getCout() const { return cout; }
int ressource::getQuantite() const { return quantite; }
QString ressource::getEtat() const { return etat; }
int ressource::getTelFournisseur() const { return tel_fournisseur; }

// Setters
void ressource::setIdRes(int id_res) { this->id_res = id_res; }
void ressource::setNom(const QString &nom) { this->nom = nom; }
void ressource::setFournisseur(const QString &fournisseur) { this->fournisseur = fournisseur; }
void ressource::setCout(int cout) { this->cout = cout; }
void ressource::setQuantite(int quantite) { this->quantite = quantite; }
void ressource::setEtat(const QString &etat) { this->etat = etat; }
void ressource::setTelFournisseur(int tel_fournisseur) { this->tel_fournisseur = tel_fournisseur; }

// Méthode pour vérifier si une ressource existe
bool ressource::exists(int id_res) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM RESSOURCES WHERE id_res = :id_res");
    query.bindValue(":id_res", id_res);

    if (query.exec()) {
        if (query.next()) {
            return query.value(0).toInt() > 0; // Retourne true si la ressource existe
        }
    }
    return false; // Retourne false en cas d'erreur ou si la ressource n'existe pas
}

// Méthode Create
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

    // Récupérer l'ID généré
    id_res = query.lastInsertId().toInt();
    return true;
}

// Méthode afficher
QSqlQueryModel* ressource::afficher() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RESSOURCES", db);

    // Configuration des en-têtes de colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Fournisseur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Coût"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("État"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Téléphone Fournisseur"));

    return model;
}

// Méthode Remove
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

// Méthode Read
ressource ressource::read(int id_res) {
    ressource r;  // Créer un objet ressource vide
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return r;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM RESSOURCES WHERE id_res = :id_res");
    query.bindValue(":id_res", id_res);

    if (query.exec()) {
        if (query.next()) {  // Si un résultat est trouvé
            r.setIdRes(query.value("id_res").toInt());
            r.setNom(query.value("nom").toString());
            r.setFournisseur(query.value("fournisseur").toString());
            r.setCout(query.value("cout").toInt());
            r.setQuantite(query.value("quantite").toInt());
            r.setEtat(query.value("etat").toString());
            r.setTelFournisseur(query.value("tel_fournisseur").toInt());
        } else {
            qDebug() << "Aucune ressource trouvée avec l'ID:" << id_res;
        }
    } else {
        qDebug() << "Erreur lors de la récupération de la ressource :" << query.lastError().text();
    }

    return r;  // Retourner l'objet ressource
}

// Méthode Update
bool ressource::update(int id_res, const QString &nom, const QString &fournisseur, int cout, int quantite, const QString &etat, int tel_fournisseur) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    // Vérifier si la ressource avec l'ID donné existe
    query.prepare("SELECT COUNT(*) FROM RESSOURCES WHERE id_res = :id_res");
    query.bindValue(":id_res", id_res);
    query.exec();
    query.next();

    if (query.value(0).toInt() == 0) {
        qDebug() << "La ressource avec l'ID " << id_res << " n'existe pas.";
        return false;  // La ressource n'existe pas
    }

    // Préparer la requête de mise à jour
    query.prepare("UPDATE RESSOURCES SET nom = :nom, fournisseur = :fournisseur, cout = :cout, quantite = :quantite, etat = :etat, tel_fournisseur = :tel_fournisseur "
                  "WHERE id_res = :id_res");

    query.bindValue(":nom", nom);
    query.bindValue(":fournisseur", fournisseur);
    query.bindValue(":cout", cout);
    query.bindValue(":quantite", quantite);
    query.bindValue(":etat", etat);
    query.bindValue(":tel_fournisseur", tel_fournisseur);
    query.bindValue(":id_res", id_res);

    // Exécuter la requête et vérifier si elle a réussi
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de la ressource : " << query.lastError().text();
        return false;  // Si l'exécution échoue
    }

    qDebug() << "Ressource avec ID " << id_res << " modifiée avec succès.";
    return true;
}

//Méthode pour trier les ressources
QSqlQueryModel* ressource::trier(const QString& critere, bool ascendant) {
    QSqlQuery query;
    QString queryString = "SELECT * FROM RESSOURCES";

    if (!critere.isEmpty()) {
        queryString += " ORDER BY " + critere;
        if (!ascendant) {
            queryString += " DESC";
        }
    }

    query.prepare(queryString);
    query.exec();

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(query));

    return model;
}

// Méthode pour rechercher des ressources
QSqlQueryModel* ressource::rechercher(const QString& valeur) {
    QSqlQuery query;
    QString queryString;

    if (valeur.toInt() > 0) {
        // Recherche par ID (si la valeur est un entier positif)
        queryString = "SELECT * FROM RESSOURCES WHERE id_res = :valeur";
    } else {
        // Recherche par nom, fournisseur, etat
        queryString = "SELECT * FROM RESSOURCES "
                      "WHERE nom LIKE :valeurLike "
                      "OR fournisseur LIKE :valeurLike "
                      "OR etat LIKE :valeurLike";
    }

    query.prepare(queryString);

    if (valeur.toInt() > 0) {
        query.bindValue(":valeur", valeur);
    } else {
        query.bindValue(":valeurLike", "%" + valeur + "%");
    }

    qDebug() << "Executing query:" << queryString;
    qDebug() << "Binding values - " << (valeur.toInt() > 0 ? "exact:" : "LIKE pattern:") << valeur;

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(query));

    return model;
}

// Méthode pour générer le contenu HTML du PDF
QString ressource::genererContenuPDF() {
    QString html = R"(
    <html>
    <head>
        <style>
            body {
                font-family: Arial, sans-serif;
                margin: 0;
                padding: 0;
            }
            h1 {
                text-align: center;
                color: #333;
                margin-bottom: 10px;
                font-size: 18px;
            }
            table {
                width: 100%;
                border-collapse: collapse;
            }
            th, td {
                border: 1px solid #dddddd;
                padding: 8px;
                text-align: left;
                font-size: 9px;
                white-space: nowrap;
            }
            th {
                background-color: #f2f2f2;
                font-weight: bold;
            }
            .footer {
                text-align: center;
                font-size: 10px;
                color: #666;
                margin-top: 15px;
            }
        </style>
    </head>
    <body>
        <h1>Rapport des Ressources</h1>
        <table>
            <tr>
                <th>ID</th>
                <th>Nom</th>
                <th>Fournisseur</th>
                <th>Coût</th>
                <th>Quantité</th>
                <th>État</th>
                <th>Téléphone Fournisseur</th>
            </tr>
    )";

    // Ajouter les ressources à la table dans la boucle
    QSqlQuery query("SELECT * FROM RESSOURCES");
    while (query.next()) {
        int id_res = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString fournisseur = query.value(2).toString();
        int cout = query.value(3).toInt();
        int quantite = query.value(4).toInt();
        QString etat = query.value(5).toString();
        int tel_fournisseur = query.value(6).toInt();

        html += QString(
                    "<tr>"
                    "<td>%1</td>"
                    "<td>%2</td>"
                    "<td>%3</td>"
                    "<td>%4</td>"
                    "<td>%5</td>"
                    "<td>%6</td>"
                    "<td>%7</td>"
                    "</tr>"
                    ).arg(id_res)
                    .arg(nom)
                    .arg(fournisseur)
                    .arg(cout)
                    .arg(quantite)
                    .arg(etat)
                    .arg(tel_fournisseur);
    }

    html += QString(R"(
        </table>
        <div class='footer'>
            <p>Ce rapport a été généré automatiquement le %1.</p>
        </div>
    </body>
    </html>
    )").arg(QDate::currentDate().toString("dd/MM/yyyy"));

    return html;
}

// Méthode pour générer le PDF
bool ressource::genererPDF(const QString& fichierPDF) {
    QString contenuHTML = genererContenuPDF();  // Récupérer le contenu HTML généré

    QTextDocument document;
    document.setHtml(contenuHTML);

    // Configurer le QPrinter pour créer un PDF
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageOrientation(QPageLayout::Landscape); // Utilisez setPageOrientation
    printer.setOutputFileName(fichierPDF);

    // Réduire les marges de la page pour maximiser l'espace
    printer.setPageMargins(QMarginsF(5, 5, 5, 5));

    // Imprimer le document dans le fichier PDF
    document.print(&printer);
    if (!printer.isValid()) {
        qDebug() << "Erreur: Imprimante invalide";
        return false;
    }

    document.print(&printer);

    if (!QFile::exists(fichierPDF)) {
        qDebug() << "Erreur: Fichier PDF non créé";
        return false;
    }

    return true;

}
QMap<QString, int> ressource::obtenirStatistiques() {
    QMap<QString, int> stats;
    QSqlQuery query;
    query.prepare("SELECT etat, COUNT(*) FROM RESSOURCES GROUP BY etat");

    if (query.exec()) {
        while (query.next()) {
            stats.insert(query.value(0).toString(), query.value(1).toInt());
        }
    }
    return stats;
}
