#ifndef PROJET_H
#define PROJET_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QApplication>
#include <QMap>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

// Classe principale : projets
class projets
{
private:
    int id_projet;
    QString nom_projet;
    QString description;
    QString date_debut;
    QString date_fin;
    double budget;
    QString status;

public:
    projets();
    projets(int id, const QString &nom, const QString &desc, const QString &debut, const QString &fin, double bud, const QString &stat);

    int getId_projet() const;
    QString getNom_projet() const;
    QString getDescription() const;
    QString getDate_debut() const;
    QString getDate_fin() const;
    double getBudget() const;
    QString getStatus() const;

    void setId_projet(int id);
    void setNom_projet(const QString &nom);
    void setDescription(const QString &desc);
    void setDate_debut(const QString &date);
    void setDate_fin(const QString &date);
    void setBudget(double value);
    void setStatus(const QString &stat);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id_projet);
    bool modifier(int id_projet);

    QSqlQueryModel* trier();
    QSqlQueryModel* chercher(QString id);
    bool PDF();

    // New Methods
    int getProjectCountByStatus(const QString &status);
    void afficherProgressionASCII();

};

#endif // PROJET_H
