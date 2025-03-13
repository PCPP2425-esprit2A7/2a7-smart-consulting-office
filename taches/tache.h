#ifndef TACHE_H
#define TACHE_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class tache
{
public:
    tache();
    tache(const QString &nom, const QString &description, const QDate &datee, const QString &priorite, const QString &statut);

    int getId() const;
    QString getNom() const;
    QString getDescription() const;
    QDate getDatee() const;
    QString getPriorite() const;
    QString getStatut() const;

    void setId(int id) { this->id = id; }
    void setNom(const QString &nom);
    void setDescription(const QString &description);
    void setDatee(const QDate &datee);
    void setPriorite(const QString &priorite);
    void setStatut(const QString &statut);

    bool create();
    static bool remove(int id);
    static tache read(int id);
    bool update(int id, const QString &nom, const QString &description, const QDate &datee, const QString &priorite, const QString &statut);

    QSqlQueryModel* afficher();
    static bool exists(int id);

    QSqlQueryModel* trier(const QString& critere, bool ascendant = true);
    QSqlQueryModel* rechercher(const QString& keyword);
    QString genererContenuPDF();
    void genererPDF(const QString& fichierPDF);

private:
    int id;
    QString nom;
    QString description;
    QDate datee;
    QString priorite;
    QString statut;
};

#endif // TACHE_H
