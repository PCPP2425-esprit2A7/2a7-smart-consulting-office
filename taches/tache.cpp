#include "tache.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QFile>
#include <QTextDocument>
#include <QDate>

// Constructeur par défaut
tache::tache() : id(-1) {}

// Constructeur paramétré
tache::tache(const QString &nom, const QString &description, const QDate &datee, const QString &priorite, const QString &statut)
    : id(-1), nom(nom), description(description), datee(datee), priorite(priorite), statut(statut) {}

// Getters
int tache::getId() const { return id; }
QString tache::getNom() const { return nom; }
QString tache::getDescription() const { return description; }
QDate tache::getDatee() const { return datee; }
QString tache::getPriorite() const { return priorite; }
QString tache::getStatut() const { return statut; }

// Setters
void tache::setNom(const QString &nom) { this->nom = nom; }
void tache::setDescription(const QString &description) { this->description = description; }
void tache::setDatee(const QDate &datee) { this->datee = datee; }
void tache::setPriorite(const QString &priorite) { this->priorite = priorite; }
void tache::setStatut(const QString &statut) { this->statut = statut; }

// Méthode pour vérifier si une tâche existe
bool tache::exists(int id) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM TACHES WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            return query.value(0).toInt() > 0; // Retourne true si la tâche existe
        }
    }
    return false; // Retourne false en cas d'erreur ou si la tâche n'existe pas
}

// Méthode Create
bool tache::create() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO TACHES (nom, description, datee, priorite, statut) "
                  "VALUES (:nom, :description, TO_DATE(:datee, 'DD-MM-YYYY'), :priorite, :statut)");

    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":datee", datee.toString("dd-MM-yyyy"));  // Format the date as DD-MM-YYYY
    query.bindValue(":priorite", priorite);
    query.bindValue(":statut", statut);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion :" << query.lastError();
        return false;
    }

    // Récupérer l'ID généré
    id = query.lastInsertId().toInt();
    return true;
}
// Méthode afficher
QSqlQueryModel* tache::afficher() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TACHES", db);

    // Configuration des en-têtes de colonnes
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Priorité"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));

    return model;
}

// Méthode Remove
bool tache::remove(int id) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM TACHES WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression :" << query.lastError();
        return false;
    }

    return true;
}

// Méthode Read
tache tache::read(int id) {
    tache t;  // Créer un objet tache vide
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return t;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM TACHES WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {  // Si un résultat est trouvé
            t.setId(query.value("id").toInt());
            t.setNom(query.value("nom").toString());
            t.setDescription(query.value("description").toString());
            t.setDatee(query.value("datee").toDate());
            t.setPriorite(query.value("priorite").toString());
            t.setStatut(query.value("statut").toString());
        } else {
            qDebug() << "Aucune tâche trouvée avec l'ID:" << id;
        }
    } else {
        qDebug() << "Erreur lors de la récupération de la tâche :" << query.lastError().text();
    }

    return t;  // Retourner l'objet tache
}

// Méthode Update
bool tache::update(int id, const QString &nom, const QString &description, const QDate &datee, const QString &priorite, const QString &statut) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    // Vérifier si la tâche avec l'ID donné existe
    query.prepare("SELECT COUNT(*) FROM TACHES WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();

    if (query.value(0).toInt() == 0) {
        qDebug() << "La tâche avec l'ID " << id << " n'existe pas.";
        return false;  // La tâche n'existe pas
    }

    // Préparer la requête de mise à jour
    query.prepare("UPDATE TACHES SET nom = :nom, description = :description, datee = TO_DATE(:datee, 'DD-MM-YYYY'), "
                  "priorite = :priorite, statut = :statut "
                  "WHERE id = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":datee", datee.toString("dd-MM-yyyy"));  // Format the date as DD-MM-YYYY
    query.bindValue(":priorite", priorite);
    query.bindValue(":statut", statut);
    query.bindValue(":id", id);

    // Exécuter la requête et vérifier si elle a réussi
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de la tâche : " << query.lastError().text();
        return false;  // Si l'exécution échoue
    }

    qDebug() << "Tâche avec ID " << id << " modifiée avec succès.";
    return true;
}

// Méthode pour trier les tâches
QSqlQueryModel* tache::trier(const QString& critere, bool ascendant) {
    QSqlQuery query;
    QString queryString = "SELECT * FROM TACHES";

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

// Méthode pour rechercher des tâches
QSqlQueryModel* tache::rechercher(const QString& valeur) {
    QSqlQuery query;
    QString queryString;

    if (valeur.toInt() > 0) {
        // Recherche par ID (si la valeur est un entier positif)
        queryString = "SELECT * FROM TACHES WHERE id = :valeur";
    } else {
        // Recherche par nom, description, priorite ou statut
        queryString = "SELECT * FROM TACHES "
                      "WHERE nom LIKE :valeurLike "
                      "OR description LIKE :valeurLike "
                      "OR priorite LIKE :valeurLike "
                      "OR statut LIKE :valeurLike";
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
QString tache::genererContenuPDF() {
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
        <h1>Rapport des Tâches</h1>
        <table>
            <tr>
                <th>ID</th>
                <th>Nom</th>
                <th>Description</th>
                <th>Date</th>
                <th>Priorité</th>
                <th>Statut</th>
            </tr>
    )";

    // Ajouter les tâches à la table dans la boucle
    QSqlQuery query("SELECT * FROM TACHES");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString description = query.value(2).toString();
        QDate datee = query.value(3).toDate();
        QString priorite = query.value(4).toString();
        QString statut = query.value(5).toString();

        html += QString(
                    "<tr>"
                    "<td>%1</td>"
                    "<td>%2</td>"
                    "<td>%3</td>"
                    "<td>%4</td>"
                    "<td>%5</td>"
                    "<td>%6</td>"
                    "</tr>"
                    ).arg(id)
                    .arg(nom)
                    .arg(description)
                    .arg(datee.toString("dd/MM/yyyy"))
                    .arg(priorite)
                    .arg(statut);
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
void tache::genererPDF(const QString& fichierPDF) {
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
}
