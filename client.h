#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client
{
private:
    int id;
    QString name;
    QString address;
    QString phone;
    QString email;
    QString nom_entreprise;
    int nbr_consultation;

public:

    Client(int id, const QString &name, const QString &address,
           const QString &phone, const QString &email,
           const QString &nom_entreprise, int nbr_consultation);

    int getId() const;
    void setId(int id);

    QString getName() const;
    void setName(const QString &name);

    QString getAddress() const;
    void setAddress(const QString &address);

    QString getPhone() const;
    void setPhone(const QString &phone);

    QString getEmail() const;
    void setEmail(const QString &email);

    QString getNomEntreprise() const;
    void setNomEntreprise(const QString &nom_entreprise);

    int getNbrConsultation() const;
    void setNbrConsultation(int nbr_consultation);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier(int id);  // Added the modifier function
};

#endif // CLIENT_H
