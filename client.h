#ifndef CLIENT_H
#define CLIENT_H

#include <Qstring>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client
{
private:
    int id;
    std::string name;
    std::string address;
    std::string phone;
    std::string email;
    std::string nom_entreprise;
    int nbr_consultation;

public:

    Client(int id, const std::string &name, const std::string &address,
           const std::string &phone, const std::string &email,
           const std::string &nom_entreprise, int nbr_consultation);


    int getId() const;
    void setId(int id);

    std::string getName() const;
    void setName(const std::string &name);

    std::string getAddress() const;
    void setAddress(const std::string &address);

    std::string getPhone() const;
    void setPhone(const std::string &phone);

    std::string getEmail() const;
    void setEmail(const std::string &email);

    std::string getNomEntreprise() const;
    void setNomEntreprise(const std::string &nom_entreprise);

    int getNbrConsultation() const;
    void setNbrConsultation(int nbr_consultation);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);

};

#endif // CLIENT_H
