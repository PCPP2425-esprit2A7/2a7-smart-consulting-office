#ifndef USERSESSION_H
#define USERSESSION_H

#include <QString>

class UserSession
{
private:
    static UserSession* m_instance;

    // Consultant attributes
    int m_idCons;
    QString m_nomCons;
    QString m_prenomCons;
    QString m_email;
    int m_tel;
    QString m_categorie;  // Note the French spelling
    QString m_mdp;
    int m_heures;
    QString m_question;
    QString m_reponse;

    // Private constructor for singleton pattern
    UserSession();

public:
    // Singleton access
    static UserSession& instance();

    // Prevent copying
    UserSession(const UserSession&) = delete;
    UserSession& operator=(const UserSession&) = delete;

    // Setters
    void setConsultant(int idCons, const QString& nomCons, const QString& prenomCons,
                      const QString& email, int tel, const QString& categorie,
                      const QString& mdp, int heures, const QString& question,
                      const QString& reponse);

    // Getters
    int getIdCons() const;
    QString getNomCons() const;
    QString getPrenomCons() const;
    QString getEmail() const;
    int getTel() const;
    QString getCategorie() const;  // Note the French spelling
    QString getMdp() const;
    int getHeures() const;
    QString getQuestion() const;
    QString getReponse() const;

    // Clear session
    void clearSession();

    // Additional methods - use same spelling as existing variable
    void setCategory(const QString &category) { m_categorie = category; }
    QString getCategory() const { return m_categorie; }
};

#endif // USERSESSION_H
