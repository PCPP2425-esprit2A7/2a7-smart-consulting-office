#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <QString>
#include <QSqlQueryModel>
#include <QMap>


class ressource
{
public:
    ressource();
    ressource(const QString &nom, const QString &fournisseur, int cout, int quantite, const QString &etat, int tel_fournisseur);

    int getIdRes() const;
    QString getNom() const;
    QString getFournisseur() const;
    int getCout() const;
    int getQuantite() const;
    QString getEtat() const;
    int getTelFournisseur() const;

    void setIdRes(int id_res);
    void setNom(const QString &nom);
    void setFournisseur(const QString &fournisseur);
    void setCout(int cout);
    void setQuantite(int quantite);
    void setEtat(const QString &etat);
    void setTelFournisseur(int tel_fournisseur);

    bool create();
    static bool remove(int id_res);
    static ressource read(int id_res);
    bool update(int id_res, const QString &nom, const QString &fournisseur, int cout, int quantite, const QString &etat, int tel_fournisseur);

    QSqlQueryModel* afficher();
    static bool exists(int id_res);
    QSqlQueryModel* trier(const QString& critere, bool ascendant = true);
    QSqlQueryModel* rechercher(const QString& keyword);
    QString genererContenuPDF();
    bool genererPDF(const QString& fichierPDF);
    QMap<QString, int> obtenirStatistiques();

private:
    int id_res;
    QString nom;
    QString fournisseur;
    int cout;
    int quantite;
    QString etat;
    int tel_fournisseur;
};
#endif // RESSOURCE_H
