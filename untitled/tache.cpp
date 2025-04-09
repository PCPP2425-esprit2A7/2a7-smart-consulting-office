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
#include <QJsonObject>
#include <QJsonDocument>

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

bool tache::exists(int id) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM TACHES WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

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
    query.bindValue(":datee", datee.toString("dd-MM-yyyy"));
    query.bindValue(":priorite", priorite);
    query.bindValue(":statut", statut);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion :" << query.lastError();
        return false;
    }

    id = query.lastInsertId().toInt();
    logHistory(id, "CREATE", serializeTacheData(*this));
    return true;
}

QSqlQueryModel* tache::afficher() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TACHES", db);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Priorité"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));

    return model;
}

bool tache::remove(int id) {
    tache t = read(id);
    if (t.getId() == -1) return false;

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

    logHistory(id, "DELETE", serializeTacheData(t));
    return true;
}

tache tache::read(int id) {
    tache t;
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return t;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM TACHES WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        t.setId(query.value("id").toInt());
        t.setNom(query.value("nom").toString());
        t.setDescription(query.value("description").toString());
        t.setDatee(query.value("datee").toDate());
        t.setPriorite(query.value("priorite").toString());
        t.setStatut(query.value("statut").toString());
    }
    return t;
}

bool tache::update(int id, const QString &nom, const QString &description, const QDate &datee,
                   const QString &priorite, const QString &statut) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    tache oldTache = read(id);
    if (oldTache.getId() == -1) return false;

    QSqlQuery query(db);
    query.prepare("UPDATE TACHES SET nom = :nom, description = :description, "
                  "datee = TO_DATE(:datee, 'DD-MM-YYYY'), priorite = :priorite, statut = :statut "
                  "WHERE id = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":datee", datee.toString("dd-MM-yyyy"));
    query.bindValue(":priorite", priorite);
    query.bindValue(":statut", statut);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour :" << query.lastError();
        return false;
    }

    tache newTache = read(id);
    QJsonObject changes;
    if (oldTache.getNom() != newTache.getNom()) changes["nom"] = newTache.getNom();
    if (oldTache.getDescription() != newTache.getDescription()) changes["description"] = newTache.getDescription();
    if (oldTache.getDatee() != newTache.getDatee()) changes["datee"] = newTache.getDatee().toString("dd-MM-yyyy");
    if (oldTache.getPriorite() != newTache.getPriorite()) changes["priorite"] = newTache.getPriorite();
    if (oldTache.getStatut() != newTache.getStatut()) changes["statut"] = newTache.getStatut();

    logHistory(id, "UPDATE", QJsonDocument(changes).toJson(QJsonDocument::Compact));
    return true;
}

void tache::logHistory(int tacheId, const QString &action, const QString &changes) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open for history logging!";
        return;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO TACHES_HISTORY (tache_id, action_type, changed_data) "
                  "VALUES (:tache_id, :action_type, :changed_data)");
    query.bindValue(":tache_id", tacheId);
    query.bindValue(":action_type", action);
    query.bindValue(":changed_data", changes);

    if (!query.exec()) {
        qDebug() << "History logging failed:" << query.lastError();
    }
}

QString tache::serializeTacheData(const tache &t) {
    QJsonObject obj;
    obj["id"] = t.getId();
    obj["nom"] = t.getNom();
    obj["description"] = t.getDescription();
    obj["datee"] = t.getDatee().toString("dd-MM-yyyy");
    obj["priorite"] = t.getPriorite();
    obj["statut"] = t.getStatut();
    return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}
QSqlQueryModel* tache::gettHistory() {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM TACHES_HISTORY ORDER BY change_timestamp DESC");

    if (!query.exec()) {
        qDebug() << "Error getting history:" << query.lastError();
        delete model;
        return nullptr;
    }

    model->setQuery(std::move(query));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Tâche ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Action"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Changes"));

    return model;
}

QSqlQueryModel* tache::getHistory(int tacheId) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM TACHES_HISTORY WHERE tache_id = :tache_id ORDER BY change_timestamp DESC");
    query.bindValue(":tache_id", tacheId);

    if (!query.exec()) {
        qDebug() << "Error getting history:" << query.lastError();
        delete model;
        return nullptr;
    }

    model->setQuery(std::move(query));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Tâche ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Action"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Changes"));

    return model;
}

QSqlQueryModel* tache::trier(const QString& critere, bool ascendant) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QSqlQuery query(db);
    QString queryString = "SELECT * FROM TACHES";

    if (!critere.isEmpty()) {
        queryString += " ORDER BY " + critere;
        if (!ascendant) {
            queryString += " DESC";
        }
    }

    if (!query.exec(queryString)) {
        qDebug() << "Error executing query:" << query.lastError();
        return nullptr;
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(query));
    return model;
}

QSqlQueryModel* tache::rechercher(const QString& valeur) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return nullptr;
    }

    QSqlQuery query(db);
    bool isNumeric = false;
    int id = valeur.toInt(&isNumeric);

    if (isNumeric && id > 0) {
        query.prepare("SELECT * FROM TACHES WHERE id = :id");
        query.bindValue(":id", id);
    } else {
        query.prepare("SELECT * FROM TACHES WHERE priorite LIKE :search ");
        query.bindValue(":search", "%" + valeur + "%");
    }

    if (!query.exec()) {
        qDebug() << "Error executing search:" << query.lastError();
        return nullptr;
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(query));
    return model;
}

QString tache::genererContenuPDF() {
    QString html = R"(
    <html><head><style>
        body { font-family: Arial, sans-serif; margin: 0; padding: 0; }
        h1 { text-align: center; color: #333; margin-bottom: 10px; font-size: 18px; }
        table { width: 100%; border-collapse: collapse; }
        th, td { border: 1px solid #ddd; padding: 8px; text-align: left; font-size: 9px; }
        th { background-color: #f2f2f2; font-weight: bold; }
        .footer { text-align: center; font-size: 10px; color: #666; margin-top: 15px; }
    </style></head>
    <body>
        <h1>Rapport des Tâches</h1>
        <table>
            <tr><th>ID</th><th>Nom</th><th>Description</th><th>Date</th><th>Priorité</th><th>Statut</th></tr>
    )";

    QSqlQuery query("SELECT * FROM TACHES");
    while (query.next()) {
        html += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td><td>%6</td></tr>")
        .arg(query.value(0).toInt())
            .arg(query.value(1).toString())
            .arg(query.value(2).toString())
            .arg(query.value(3).toDate().toString("dd/MM/yyyy"))
            .arg(query.value(4).toString())
            .arg(query.value(5).toString());
    }

    html += QString(R"(
        </table>
        <div class='footer'>
            <p>Généré le %1</p>
        </div>
    </body></html>
    )").arg(QDate::currentDate().toString("dd/MM/yyyy"));

    return html;
}

bool tache::genererPDF(const QString& fichierPDF) {
    QString contenuHTML = genererContenuPDF();
    if (contenuHTML.isEmpty()) {
        qDebug() << "Erreur: Contenu HTML vide";
        return false;
    }

    QTextDocument document;
    document.setHtml(contenuHTML);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fichierPDF);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setPageMargins(QMarginsF(5, 5, 5, 5));

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

QMap<QString, int> tache::obtenirStatistiques() {
    QMap<QString, int> stats;
    QSqlQuery query;
    query.prepare("SELECT statut, COUNT(*) FROM TACHES GROUP BY statut");

    if (query.exec()) {
        while (query.next()) {
            stats.insert(query.value(0).toString(), query.value(1).toInt());
        }
    }
    return stats;
}

QList<tache> tache::getTasksForDate(const QDate &date) {
    QList<tache> tasks;
    QSqlQuery query;
    query.prepare("SELECT id FROM TACHES WHERE datee = :date");
    query.bindValue(":date", date);

    if (query.exec()) {
        while (query.next()) {
            tasks.append(read(query.value(0).toInt()));
        }
    }
    return tasks;
}

QList<tache> tache::getUpcomingTasks(int daysAhead) {
    QList<tache> tasks;
    QDate endDate = QDate::currentDate().addDays(daysAhead);

    QSqlQuery query;
    query.prepare("SELECT id FROM TACHES WHERE datee BETWEEN :start AND :end");
    query.bindValue(":start", QDate::currentDate());
    query.bindValue(":end", endDate);

    if (query.exec()) {
        while (query.next()) {
            tasks.append(read(query.value(0).toInt()));
        }
    }
    return tasks;
}

bool tache::setTaskDependency(int taskId, int dependsOnId) {
    QSqlDatabase db = Connection::get_database();
    if (!db.isOpen()) return false;

    QSqlQuery query(db);
    query.prepare("INSERT INTO TASK_DEPENDENCIES (task_id, depends_on) VALUES (:task_id, :depends_on)");
    query.bindValue(":task_id", taskId);
    query.bindValue(":depends_on", dependsOnId);

    return query.exec();
}

QList<int> tache::getTaskDependencies(int taskId) {
    QList<int> dependencies;
    QSqlQuery query;
    query.prepare("SELECT depends_on FROM TASK_DEPENDENCIES WHERE task_id = :task_id");
    query.bindValue(":task_id", taskId);

    if (query.exec()) {
        while (query.next()) {
            dependencies.append(query.value(0).toInt());
        }
    }
    return dependencies;
}
