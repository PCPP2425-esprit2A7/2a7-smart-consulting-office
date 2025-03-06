#include "ressource.h"

Ressource::Ressource(int id_res , QString nom , QString fournisseur , int cout , int quantite , QString etat , int tel_fournisseur) {
    this->id_res=id_res;
    this->nom=nom;
    this->fournisseur=fournisseur;
    this->cout=cout;
    this->quantite=quantite;
    this->etat=etat;
    this->tel_fournisseur=tel_fournisseur;

}

bool Ressource::ajouter()
{}

QSqlQueryModel * Ressource::afficher()
{


}
bool Ressource::supprimer()
{

}
