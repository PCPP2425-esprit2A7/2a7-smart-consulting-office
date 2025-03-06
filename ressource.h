#ifndef RESSOURCE_H
#define RESSOURCE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class Ressource
{
    QString nom , fournisseur , etat ;
    int id_res , cout , quantite , tel_fournisseur ;
public:
    //cons
    Ressource(){};
    Ressource(int , QString , QString , int ,int , QString , int);

    //getters
    QString getNom() {return nom;}
    QString getFournisseur() {return fournisseur;}
    QString getEtat() {return etat;}
    int getIdRes() {return id_res;}
    int getCout() {return cout;}
    int getQuantite() {return quantite;}
    int getTelFournisseur() {return tel_fournisseur;}

    //setters
    void setNom(QString n) {nom=n;}
    void setFournisseur(QString f) {fournisseur=f;}
    void setEtat(QString e) {etat=e;}
    void setIdRes(int id_res) {this->id_res=id_res;}
    void setCout(int c) { cout=c;}
    void setQuantite(int q) { quantite=q;}
    void setTelFournisseur(int tel) { tel_fournisseur=tel;}

    //methodes
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer();


};


#endif // RESSOURCE_H
