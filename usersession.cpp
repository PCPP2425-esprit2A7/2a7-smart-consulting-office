#include "usersession.h"

// Initialize the static member variable
UserSession* UserSession::m_instance = nullptr;

// Constructor implementation
UserSession::UserSession()
    : m_idCons(0), m_tel(0), m_heures(0.0f)
{
    // Initialize member variables
}

// Static method to access the instance
UserSession& UserSession::instance() {
    if (!m_instance) {
        m_instance = new UserSession();
    }
    return *m_instance;
}

void UserSession::setConsultant(int idCons, const QString& nomCons, const QString& prenomCons,
                               const QString& email, int tel, const QString& categorie,
                               const QString& mdp, int heures, const QString& question,
                               const QString& reponse)
{
    m_idCons = idCons;
    m_nomCons = nomCons;
    m_prenomCons = prenomCons;
    m_email = email;
    m_tel = tel;
    m_categorie = categorie;
    m_mdp = mdp;
    m_heures = heures;
    m_question = question;
    m_reponse = reponse;
}

// Getters implementation
int UserSession::getIdCons() const { return m_idCons; }
QString UserSession::getNomCons() const { return m_nomCons; }
QString UserSession::getPrenomCons() const { return m_prenomCons; }
QString UserSession::getEmail() const { return m_email; }
int UserSession::getTel() const { return m_tel; }
QString UserSession::getCategorie() const { return m_categorie; }
QString UserSession::getMdp() const { return m_mdp; }
int UserSession::getHeures() const { return m_heures; }
QString UserSession::getQuestion() const { return m_question; }
QString UserSession::getReponse() const { return m_reponse; }

void UserSession::clearSession()
{
    m_idCons = 0;
    m_nomCons.clear();
    m_prenomCons.clear();
    m_email.clear();
    m_tel = 0;
    m_categorie.clear();
    m_mdp.clear();
    m_heures = 0.0f;
    m_question.clear();
    m_reponse.clear();
}
