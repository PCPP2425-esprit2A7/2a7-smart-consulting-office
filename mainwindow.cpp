#include "mainwindow.h"
#include "formationservice.h"
#include "qsqlerror.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "ui_login.h"
#include "usersession.h"
#include <QDebug>
#include <QMessageBox>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->CLIENTSbtn, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->PROJETSbtn, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
        ui->stackedWidget_3->setCurrentIndex(0);
    });
    connect(ui->FORMATIONSbtn, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(ui->CONSULTANTbtn, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(3);
    });
// CONNECT GESTION CLIENT *****************************
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList()
                                     << "Nom Complet"
                                     << "Adresse"
                                     << "Telephone"
                                     << "Email"
                                     << "Nom Entreprise"
                                     << "Date d'Adhesion"
                                     << "CIN"
                                     << "RFID");

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
    //le slot update_label suite à la reception du signal readyRead (reception des données
       // Initialize the GPTClient and set the API key
    /*OpenAIChatBot = new OpenAIChatBot(this);
    OpenAIChatBot->setToken("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");
    OpenAIChatBot->sendMessage("Hello");
    // Connect the responseReceived signal from GPTClient to display the response in chat
    connect(githubClient, &GitHubClient::responseReceived, this, [=](const QString &res){
        ui->chatDisplay->append("🤖: " + res);
    });*/

    // Connecter Arduino
    A.connect_arduino();

    // Timer pour lire les données toutes les 100 ms
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update_label_from_arduino);
    timer->start(100); // chaque 100 ms



    // Calendar settings
    ui->calendarWidget->setGridVisible(true);   // Show the date grid
    ui->calendarWidget->setNavigationBarVisible(true);  // Show month/year navigation
    ui->calendarWidget->setDateEditEnabled(true);  // Enable date editing
    ui->tableView->setSortingEnabled(true);


    // Connect button clicks to respective slots
    connect(ui->btnAjouter, &QPushButton::clicked, this, [=](){
        ajouterClient();
        ui->stackedWidget_2->setCurrentIndex(0);
    });
    connect(ui->btnAfficher, &QPushButton::clicked, this, &MainWindow::afficherClients);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &MainWindow::supprimerClient);
    connect(ui->btnModifier, &QPushButton::clicked, this, [=](){
        ui->stackedWidget_2->setCurrentIndex(2);
    });
    connect(ui->AjoutClient, &QPushButton::clicked, this, [=](){
        ui->stackedWidget_2->setCurrentIndex(1);
    });
    connect(ui->btnConfirmer, &QPushButton::clicked, this, &MainWindow::confirmerModification);
    //connect(ui->btnNext, &QPushButton::clicked, this, &MainWindow::nextPage);
    //connect(ui->btnPrev, &QPushButton::clicked, this, &MainWindow::prevPage);
    connect(ui->btnExportPDF, &QPushButton::clicked, this, &MainWindow::exportClientsToPDF);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::sortClientsByJoinDate);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchClientByCIN);
    connect(ui->statbutton, &QPushButton::clicked, this, &MainWindow::afficherClientStats);
    connect(ui->send, &QPushButton::clicked, this, &MainWindow::onSendClicked);
    //connect(githubClient, &GitHubClient::responseReceived, this, &MainWindow::handleResponse);
    connect(ui->Home, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_2->setCurrentIndex(0);
    });
    connect(ui->btnConfirmer, &QPushButton::clicked, this, [=](){
        ui->stackedWidget_2->setCurrentIndex(0);
        modifierClient();
    });







    // Connect the calendar date selection signal to the slot
    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &MainWindow::onCalendarDateSelected);
    //CONNECT GESTION PROJETS *******************************************
    connect(ui->ajoute, &QPushButton::clicked, this, &MainWindow::ajouterProjet);
    connect(ui->aff_2, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(0);
        afficherProjet();
    });
    connect(ui->sup, &QPushButton::clicked, this, &MainWindow::supprimerProjet);
    connect(ui->update, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(2);
        modifierprojet();
    });
    connect(ui->add, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget_3->setCurrentIndex(1);
    });



    connect(ui->tri, &QPushButton::clicked, this, &::MainWindow::ontrier_clicked);
    connect(ui->chercher, &QPushButton::clicked, this, &::MainWindow::onchercher_clicked);
    connect(ui->pdf, &QPushButton::clicked, this, &::MainWindow::onexporter_clicked);
    connect(ui->stat, &QPushButton::clicked, this, &MainWindow::afficherStat);
    connect(ui->asciibutton, &QPushButton::clicked, this, &MainWindow::afficherDashboardASCII);
    connect(ui->asciibutton, &QPushButton::clicked, this, &MainWindow::showAsciiDashboardPage);
    ui->aff->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->aff->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->aff->horizontalHeader()->setStretchLastSection(true);

    //CONNECT FORMATIONS***********************************************************************************
    connect(ui->ajouter,           &QPushButton::clicked, this, &MainWindow::on_ajouter_clicked);
    connect(ui->supprimer,         &QPushButton::clicked, this, &MainWindow::on_supprimer_clicked);
    connect(ui->modifier,          &QPushButton::clicked, this, &MainWindow::on_modifier_clicked);
    connect(ui->afficher,          &QPushButton::clicked, this, &MainWindow::on_afficher_clicked);
    connect(ui->pdf,               &QPushButton::clicked, this, &MainWindow::on_pdf_clicked);
    connect(ui->presence,          &QPushButton::clicked, this, &MainWindow::on_presence_clicked);
    connect(ui->evaluations,       &QPushButton::clicked, this, &MainWindow::on_evaluations_clicked);
    connect(ui->tripardate,        &QPushButton::clicked, this, &MainWindow::on_tripardate_clicked);
    connect(ui->triparduree,       &QPushButton::clicked, this, &MainWindow::on_triparduree_clicked);
    connect(ui->ajouterEvaluationBtn, &QPushButton::clicked, this, &MainWindow::on_ajouterEvaluationBtn_clicked);

    on_afficher_clicked();

    //CONSULTANT CONNECT *************************************************************************************




}



MainWindow::~MainWindow()
{
    delete ui;
}
// MainWindow CLIENT *********************************************
void MainWindow::ajouterClient()
{
    QString name = ui->lineEdit_name->text().trimmed();
    QString address = ui->lineEdit_address->text().trimmed();
    QString phone = ui->lineEdit_phone->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString nomEntreprise = ui->lineEdit_nom_entreprise->text().trimmed();
    QDate join_date = ui->calendarWidget->selectedDate();
    QString cin_client = ui->lineEdit_cin->text().trimmed();
    QString RFID = ui->rfid->text().trimmed();

    static const QRegularExpression phoneRegex("^\\d{7,}$");
    static const QRegularExpression emailRegex("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$");

    if (name.isEmpty() || address.isEmpty() || phone.isEmpty() || email.isEmpty() || nomEntreprise.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs.");
        return;
    }

    if (!phoneRegex.match(phone).hasMatch()) {
        QMessageBox::warning(this, "Numéro invalide", "Le numéro de téléphone doit contenir au moins 7 chiffres.");
        return;
    }

    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Email invalide", "Veuillez saisir une adresse e-mail valide.");
        return;
    }

    int nbr_consultation = 0;
    Client client(0, name, address, phone, email, nomEntreprise, nbr_consultation, join_date, cin_client, RFID);

    if (client.ajouter()) {
        QMessageBox::information(this, "Succès", "Client ajouté !");
        // Manually clear the input fields
        ui->lineEdit_name->clear();
        ui->lineEdit_address->clear();
        ui->lineEdit_phone->clear();
        ui->lineEdit_email->clear();
        ui->lineEdit_nom_entreprise->clear();
        ui->lineEdit_cin->clear();
        ui->rfid->clear();
        afficherClients();  // Refresh the list of clients
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du client.");
    }
}

void MainWindow::afficherClients()
{
    Client client(0, "", "", "", "", "", 0, QDate::currentDate(), "", "");
    ui->tableView->setModel(client.afficher());
}

void MainWindow::supprimerClient()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Suppression", "Veuillez sélectionner un client à supprimer.");
        return;
    }

    QModelIndex index = selectedRows.first();
    int id = index.sibling(index.row(), 0).data().toInt();

    Client client(0, "", "", "", "", "", 0, QDate::currentDate(), "", "");

    if (client.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Client supprimé !");
        afficherClients();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du client.");
    }
}

void MainWindow::modifierClient()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Veuillez sélectionner un client à modifier.");
        return;
    }

    QModelIndex index = selectedRows.first();
    int id = index.sibling(index.row(), 0).data().toInt();

    QString name = ui->lineEdit_name_3->text();
    QString address = ui->lineEdit_address_3->text();
    QString phone = ui->lineEdit_phone_2->text();
    QString email = ui->lineEdit_email_2->text();
    QString nomEntreprise = ui->lineEdit_nom_entreprise_2->text();
    int nbr_consultation = ui->lineEdit_nbr_consultation->text().toInt();
    QDate join_date = QDate::currentDate();
    QString cin_client = ui->lineEdit_cin2->text();
    QString RFID = ui->rfid2->text();

    Client client(id, name, address, phone, email, nomEntreprise, nbr_consultation, join_date, cin_client, RFID);
    if (client.modifier()) {
        QMessageBox::information(this, "Succès", "Client modifié avec succès.");

        // Manually clear the input fields
        ui->lineEdit_name_3->clear();
        ui->lineEdit_address_3->clear();
        ui->lineEdit_phone_2->clear();
        ui->lineEdit_email_2->clear();
        ui->lineEdit_nom_entreprise_2->clear();
        ui->lineEdit_nbr_consultation->clear();
        ui->lineEdit_cin2->clear();

        afficherClients();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du client.");
    }
}


void MainWindow::confirmerModification()
{
    modifierClient();
}



void MainWindow::nextPage()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    int pageCount = ui->stackedWidget->count();

    if (currentIndex < pageCount - 1) {
        ui->stackedWidget->setCurrentIndex(currentIndex + 1);
    }
}

void MainWindow::prevPage()
{
    int currentIndex = ui->stackedWidget->currentIndex();

    if (currentIndex > 0) {
        ui->stackedWidget->setCurrentIndex(currentIndex - 1);
    }
}

void MainWindow::onCalendarDateSelected(const QDate &date)
{
    qDebug() << "Selected date: " << date.toString();
    // You can store the selected date and use it in your other methods
    selectedDate = date;  // Store the date if you need to use it later
}



void MainWindow::exportClientsToPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "*.pdf");
    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".pdf"))
        fileName += ".pdf";

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    QFont font("Arial", 10);
    painter.setFont(font);
    QFontMetrics metrics(font);

    // Page margins and dimensions
    int margin = 50;
    int pageWidth = pdfWriter.width();
    int availableWidth = pageWidth - 2 * margin;
    int startY = 100;
    int rowHeight = 40;  // Increased row height
    int headerMargin = 10;  // Extra space between headers and data rows

    // Get data
    QSqlQueryModel model;
    model.setQuery("SELECT ID_CLIENT, NOMCOMPLET, NOMENTREPRISE, ADRESSE, EMAIL, TELEPHONE, NBR_CONSULTATIONS, JOIN_DATE, CIN_CLIENT FROM CLIENTS");

    int colCount = model.columnCount();
    int colWidth = availableWidth / colCount; // Equal column width
    QVector<int> colWidths(colCount, colWidth);

    // Title
    QFont titleFont("Arial", 14, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(margin, startY - 40, "Liste des Clients");

    // Headers
    painter.setFont(font);
    int x = margin;
    for (int col = 0; col < colCount; ++col)
    {
        QRect rect(x, startY, colWidths[col], rowHeight);
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter, model.headerData(col, Qt::Horizontal).toString());
        x += colWidths[col];
    }

    // Data rows (with margin added after the headers)
    int y = startY + rowHeight + headerMargin; // Add header margin here
    for (int row = 0; row < model.rowCount(); ++row)
    {
        x = margin;
        for (int col = 0; col < colCount; ++col)
        {
            QRect rect(x, y, colWidths[col], rowHeight);
            painter.drawRect(rect);
            painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, model.data(model.index(row, col)).toString());
            x += colWidths[col];
        }
        y += rowHeight;  // Adjust for the new row height
    }

    painter.end();
}
void MainWindow::sortClientsByJoinDate()
{

    QSqlQueryModel* model = new QSqlQueryModel(this);


    model->setQuery("SELECT ID_CLIENT, NOMCOMPLET, NOMENTREPRISE, ADRESSE, EMAIL, TELEPHONE, NBR_CONSULTATIONS, JOIN_DATE, CIN_CLIENT FROM CLIENTS ORDER BY JOIN_DATE ASC");


    ui->tableView->setModel(model);
}
void MainWindow::searchClientByCIN()
{
    // Get the CIN input as a string and convert to float (or double)
    QString cinText = ui->lineEditCIN->text().trimmed();

    // Validate input: check if it's a valid number
    bool ok;
    double cinValue = cinText.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un numéro CIN valide (nombre).");
        return;
    }

    // Prepare the query using CIN_CLIENT as float
    QSqlQueryModel* model = new QSqlQueryModel(this);
    model->setQuery(QString(
                        "SELECT DISTINCT ID_CLIENT, NOMCOMPLET, NOMENTREPRISE, ADRESSE, EMAIL, TELEPHONE, "
                        "NBR_CONSULTATIONS, JOIN_DATE, CIN_CLIENT "
                        "FROM CLIENTS WHERE CIN_CLIENT = %1")
                        .arg(cinValue, 0, 'f', 0)); // Format as float with 0 decimal digits

    // Check if the query returned results
    if (model->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur", "Échec de la recherche: " + model->lastError().text());
        return;
    }

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Résultat", "Aucun client trouvé avec ce CIN.");
        return;
    }

    // Display the result in the table
    ui->tableView->setModel(model);
}

// In the constructor, call the stat() function to create and display the chart
void MainWindow::afficherClientStats()
{
    ui->stackedWidget_2->setCurrentIndex(3);  // Replace with the correct page index if different

    QSqlQuery query;
    query.exec("SELECT NOMENTREPRISE, COUNT(*) FROM CLIENTS GROUP BY NOMENTREPRISE");

    QPieSeries *series = new QPieSeries();

    while (query.next()) {
        QString entreprise = query.value(0).toString();
        int count = query.value(1).toInt();
        if (count > 0)
            series->append(entreprise, count);
    }

    if (series->count() == 0) {
        QMessageBox::information(this, "Aucune donnée", "Aucune statistique à afficher pour les clients.");
        return;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par entreprise");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Clean previous chart
    QLayoutItem *child;
    while ((child = ui->verticalLayout_3->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }


    ui->verticalLayout_3->addWidget(chartView);
}
void MainWindow::onSendClicked() {
    QString userInput = ui->userInput->text();
    if (userInput.isEmpty())
        return;

    // Afficher le message de l'utilisateur
    ui->chatDisplay->append("<b>Moi :</b> " + userInput);
    ui->userInput->clear();

    // Envoie de la requête à l'API
    QJsonObject messageObject;
    messageObject["role"] = "user";
    messageObject["content"] = userInput;

    QJsonArray messagesArray;
    messagesArray.append(messageObject);

    QJsonObject requestBody;
    requestBody["model"] = "gpt-4o"; // ou gpt-3.5-turbo
    requestBody["messages"] = messagesArray;

    QNetworkRequest request(QUrl("https://api.openai.com/v1/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer VOTRE_CLE_API");

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request, QJsonDocument(requestBody).toJson());

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QString botReply = jsonDoc["choices"].toArray()[0].toObject()["message"].toObject()["content"].toString();
            ui->chatDisplay->append("<b>Assistant :</b> " + botReply);
        } else {
            ui->chatDisplay->append("<b>Erreur :</b> " + reply->errorString());
        }
        reply->deleteLater();
        manager->deleteLater();
    });
}


void MainWindow::handleResponse(const QString &response)
{
    ui->chatDisplay->append("AI: " + response);
}

void MainWindow::addClients(const QString &name, const QString &address, const QString &email, const QString &cin)
{
    Client client;
    client.setNomComplet(name);
    client.setAdresse(address);
    client.setEmail(email);
    client.setCinClient(cin);

    if (client.ajouter()) {
        ui->chatDisplay->append("✔️ Client ajouté !");
        afficherClients(); // Optional: refresh table
    } else {
        ui->chatDisplay->append("❌ Erreur lors de l'ajout.");
    }
}
void MainWindow::addClient(const QString &name, const QString &address, const QString &email, const QString &cin)
{
    // Example implementation
    qDebug() << "Adding client:";
    qDebug() << "Name:" << name;
    qDebug() << "Address:" << address;
    qDebug() << "Email:" << email;
    qDebug() << "CIN:" << cin;


}

void MainWindow::update_label_from_arduino()
{
    // You can remove this function if you're only working with the UID now
    QByteArray data = A.read_from_arduino();
    QString message = QString::fromUtf8(data).trimmed();

    if (!message.isEmpty())
    {
        qDebug() << "Received from Arduino:" << message;
    }
}
void MainWindow::update_label() {
    // This is where you'll update the UI based on the incoming data
    QByteArray data = A.getserial()->readAll(); // Get the data from the serial
    QString rfidTag = QString(data).trimmed();   // Clean up the data

    // Now you can perform your client lookup here
    fetchClientByRFID(rfidTag);  // Call your database function
}

/*void MainWindow::fetchClientByRFID(const QString& rfidTag) {


    QSqlQuery query;
    query.prepare("SELECT * FROM clients WHERE RFID = :rfid");  // Assuming your table is 'clients'
    query.bindValue(":rfid", rfidTag);  // Bind the RFID tag to the query

    if (!query.exec()) {
        qDebug() << "Error fetching client: " << query.lastError().text();
        return;
    }

    // If a client is found, display the details
    if (query.next()) {
        // Fetch all the fields from the database
        QString nomComplet = query.value("nomComplet").toString();
        QString adresse = query.value("adresse").toString();
        QString telephone = query.value("telephone").toString();
        QString email = query.value("email").toString();
        QString nomEntreprise = query.value("nomEntreprise").toString();
        QDate joinDate = query.value("joinDate").toDate();
        QString cinClient = query.value("cinClient").toString();
        QString rfid = query.value("RFID").toString();  // Optional, but you might want to display this too

        // Display the client info in your UI (e.g., in QLabel or other widgets)
        ui->labelNomComplet->setText(nomComplet);  // Assuming you have a QLabel named labelNomComplet
        ui->labelAdresse->setText(adresse);  // Assuming a QLabel named labelAdresse
        ui->labelTelephone->setText(telephone);  // Assuming a QLabel named labelTelephone
        ui->labelEmail->setText(email);  // Assuming a QLabel named labelEmail
        ui->labelNomEntreprise->setText(nomEntreprise);  // Assuming a QLabel named labelNomEntreprise
        ui->labelJoinDate->setText(joinDate.toString("yyyy-MM-dd"));  // Format the date as needed
        ui->labelCinClient->setText(cinClient);  // Assuming a QLabel named labelCinClient
        ui->labelRFID->setText(rfid);
    } else {
        qDebug() << "No client found for RFID tag: " << rfidTag;
    }
}*/

void MainWindow::fetchClientByRFID(const QString& rfidTag) {


    QSqlQuery query;
    query.prepare("SELECT clients.NOMCOMPLET, clients.ADRESSE, clients.TELEPHONE, clients.EMAIL, "
                  "clients.NOMENTREPRISE, clients.JOIN_DATE, clients.CIN_CLIENT, clients.RFID, "
                  "projets.nom, projets.description "
                  "FROM clients "
                  "JOIN projets ON clients.fk_projet = projets.idProjet "
                  "WHERE clients.RFID = :rfid");
    query.bindValue(":rfid", rfidTag);

    if (!query.exec()) {
        qDebug() << "Error fetching client and project: " << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString nomComplet = query.value("nomComplet").toString();
        QString adresse = query.value("adresse").toString();
        QString telephone = query.value("telephone").toString();
        QString email = query.value("email").toString();
        QString nomEntreprise = query.value("nomEntreprise").toString();
        QDate joinDate = query.value("joinDate").toDate();
        QString cinClient = query.value("cinClient").toString();
        QString rfid = query.value("RFID").toString();

        QString nomProjet = query.value("nom").toString();
        QString descriptionProjet = query.value("description").toString();

        // Display client info
        ui->labelNomComplet->setText(nomComplet);
        ui->labelAdresse->setText(adresse);
        ui->labelTelephone->setText(telephone);
        ui->labelEmail->setText(email);
        ui->labelNomEntreprise->setText(nomEntreprise);
        ui->labelJoinDate->setText(joinDate.toString("yyyy-MM-dd"));
        ui->labelCinClient->setText(cinClient);
        ui->labelRFID->setText(rfid);

        // Display project info
        ui->labelNomProjet->setText(nomProjet);
        ui->labelDescriptionProjet->setText(descriptionProjet);

        qDebug() << "Client and project fetched successfully.";
    } else {
        qDebug() << "No client or project found for RFID tag: " << rfidTag;
    }
}

// Gestion des projets *****************************************************************

void MainWindow::ajouterProjet()
{
    QString nom_projet = ui->lineEdit->text();
    QString description = ui->description->text();
    QString date_debut = ui->dated->text();
    QString date_fin = ui->datef->text();

    double budget = ui->datef->text().toDouble();
    QString status = ui->statut->text();


    qDebug() << "Nom:" << nom_projet;
    qDebug() << "Description:" << description;
    qDebug() << "Date début:" << date_debut;
    qDebug() << "Date fin:" << date_fin;
    qDebug() << "Budget (double):" << budget;
    qDebug() << "Status:" << status;




    int id = ui->dated->text().toInt();

    if (nom_projet.isEmpty() || description.isEmpty() || date_debut.isEmpty() || date_fin.isEmpty() || status.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    projets p(id, nom_projet, description, date_debut, date_fin, budget, status);

    if (p.ajouter()) {
        QMessageBox::information(this, "Succès", "Projet ajouté !");
        afficherProjet();  // Rafraîchir la vue
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du projet.");
    }
}

void MainWindow::afficherProjet()
{
    projets p;
    ui->aff->setModel(p.afficher());
}

void MainWindow::supprimerProjet()
{
    QModelIndexList selectedRows = ui->aff->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Suppression", "Veuillez sélectionner un projet à supprimer.");
        return;
    }

    QModelIndex index = selectedRows.first();
    int id = index.sibling(index.row(),6).data().toInt();

    qDebug() << "ID sélectionné pour suppression:" << id;

    projets p;
    if (p.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Projet supprimé !");
        afficherProjet();  // Refresh table
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du projet.");
    }
}



void MainWindow::modifierprojet()
{
    QModelIndexList selectedRows = ui->aff->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Veuillez sélectionner un projet à modifier.");
        return;
    }

    QModelIndex index = selectedRows.first();
    int id = index.sibling(index.row(), 6).data().toInt();

    QString nom_projet = ui->lineEdit->text();
    QString description = ui->description->text();
    QString date_debut = ui->dated->text();
    QString date_fin = ui->datef->text();
    double budget = ui->datef->text().toDouble();
    QString status = ui->statut->text();

    if (nom_projet.trimmed().isEmpty() || description.trimmed().isEmpty() ||
        date_debut.trimmed().isEmpty() || date_fin.trimmed().isEmpty() || status.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }


    projets p(id, nom_projet, description, date_debut, date_fin, budget, status);

    if (p.modifier(id)) {
        QMessageBox::information(this, "Succès", "Projet modifié avec succès.");

        afficherProjet();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du projet.");
    }
}



void MainWindow::onshowStatsButton_clicked()
{
    afficherStat();
}


void MainWindow::afficherStat()
{
    ui->stackedWidget_3->setCurrentIndex(0);

    int encours = pr.getProjectCountByStatus("en cours");
    int termine = pr.getProjectCountByStatus("terminé");
    int afaire = pr.getProjectCountByStatus("à faire");

    qDebug() << "En cours:" << encours << "terminé:" << termine << "à faire" << afaire;

    QPieSeries *series = new QPieSeries();


    if (encours == 0 && termine == 0 && afaire == 0) {
        QMessageBox::information(this, "Aucune donnée", "Aucune statistique à afficher.");
        return;
    }

    if (encours > 0)
        series->append("En cours", encours);
    if (termine > 0)
        series->append("Terminé", termine);
    if (afaire > 0)
        series->append("à faire", afaire);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des projets par statut");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QLayoutItem *child;
    while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }


    ui->verticalLayout->addWidget(chartView);
}




void MainWindow::ontrier_clicked()
{
    QSqlQueryModel* sortedModel = pr.trier();

    if (sortedModel) {
        ui->aff->setModel(sortedModel);
        QMessageBox::information(this, "Succès", "Tri effectué.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec du tri.");
    }
}

void MainWindow::onchercher_clicked()
{
    QString id = ui->cherche->text();
    QSqlQueryModel* searchedModel = pr.chercher(id);

    if (searchedModel) {
        ui->aff->setModel(searchedModel);
        QMessageBox::information(this, "Succès", "Recherche effectuée.");
    } else {
        QMessageBox::critical(this, "Erreur", "Aucun résultat trouvé.");
    }
}


void MainWindow::onexporter_clicked()
{
    bool test = pr.PDF();

    if (test) {
        QMessageBox::information(this, "Succès", "Exportation en PDF réussie.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l’exportation PDF.");
    }
}





void MainWindow::afficherDashboardASCII()
{
    QSqlQuery query("SELECT STATUS, COUNT(*) FROM PROJETS GROUP BY STATUS");

    QMap<QString, int> stats;
    int total = 0;

    while (query.next()) {
        QString status = query.value(0).toString().toLower();
        int count = query.value(1).toInt();
        stats[status] = count;
        total += count;
    }

    QString output = "<pre style='font-family: monospace; font-size: 11pt;'>";

    output += "┌─────────────────────────────────────────────┐<br>";
    output += "│             ÉTAT DES PROJETS                │<br>";
    output += "└─────────────────────────────────────────────┘<br><br>";
    output += "Statut       | Projets | Progression<br>";
    output += "─────────────┼─────────┼────────────────────────────<br>";

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QString status = it.key();
        int count = it.value();
        int barLength = (total > 0) ? (count * 25 / total) : 0;
        QString bar = QString(barLength, QChar(0x2501));  // ━ bar

        QString statusDisplay = status.leftJustified(12, ' ');
        output += QString("%1 |    %2    | %3<br>").arg(statusDisplay).arg(count).arg(bar);
    }

    output += "<br>──────────────────────────────────────────────<br>";
    output += QString("Total de projets : %1<br><br>").arg(total);

    // Résumé
    output += "<b>Résumé :</b><br>";
    if (stats.contains("terminé"))
        output += QString("- %1 terminés<br>").arg(stats["terminé"]);
    if (stats.contains("en cours"))
        output += QString("- %1 en cours<br>").arg(stats["en cours"]);
    if (stats.contains("à faire"))
        output += QString("- %1 à faire<br>").arg(stats["à faire"]);

    // Suggestion
    output += "<br><b>Analyse et Suggestion :</b><br>";
    if (stats["à faire"] > total / 2) {
        output += "Une majorité des projets n'ont pas encore été lancés. Il est conseillé de débuter rapidement ces travaux.";
    } else if (stats["en cours"] > stats["terminé"]) {
        output += "Un nombre important de projets sont en cours. Une attention particulière devrait être portée à leur clôture.";
    } else if (stats["terminé"] == total) {
        output += "Tous les projets sont terminés. Excellent travail !";
    } else {
        output += "La progression globale est positive. Poursuivez vos efforts.";
    }

    output += "</pre>";

    // Show in QLabel
    ui->label->setTextFormat(Qt::RichText);
    ui->label->setText(output);
}



// ✅ Cette fonction doit être EN DEHORS de l’autre
void MainWindow::onbtnAfficherDashboard_clicked()
{
    afficherDashboardASCII();
}
void MainWindow::showAsciiDashboardPage()
{
    ui->stackedWidget_3->setCurrentIndex(2); // Replace DASHBOARD_INDEX with the correct number!
}

//FORMATIONS *******************************************************************************************************************************************





void MainWindow::on_ajouter_clicked()
{
    int id = ui->id->text().toInt();
    QString date = ui->date->text();
    int duree = ui->duree->text().toInt();
    QString participant = ui->participant->text();
    QString intitule = ui->intitule->text();
    QString statut = ui->statut->text();
    int nbr_participants = ui->nbr_participants->text().toInt();  // ← nouveau champ

    if (date.isEmpty() || duree <= 0 || participant.isEmpty() ||
        intitule.isEmpty() || statut.isEmpty() || nbr_participants < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement.");
        return;
    }

    Formation f(id, date, duree, participant, intitule, statut, nbr_participants);

    if (f.ajouter()) {
        FormationService service;
        QString presence = "P";
        if (service.ajouterParticipation(f.getId(), participant, presence)) {
            QMessageBox::information(this, "Ajout", "Formation et participation ajoutées avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la participation.");
        }
        on_afficher_clicked();
    } else {
        QMessageBox::critical(this, "Erreur SQL", "Échec de l'ajout de la formation.");
    }
}

void MainWindow::on_supprimer_clicked()
{
    QItemSelectionModel *select = ui->tableWidget->selectionModel();
    if (!select->hasSelection()) {
        QMessageBox::warning(this, "Suppression", "Veuillez sélectionner une ligne.");
        return;
    }

    QModelIndex index = select->currentIndex();
    int id = index.sibling(index.row(), 0).data().toInt();

    QSqlQuery query;
    query.prepare("DELETE FROM FORMATIONS WHERE ID = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de suppression !");
    } else {
        QMessageBox::information(this, "Suppression", "Formation supprimée avec succès.");
        on_afficher_clicked();
    }
}

void MainWindow::on_modifier_clicked()
{
    int id = ui->id->text().toInt();
    QString date = ui->date->text();
    int duree = ui->duree->text().toInt();
    QString participant = ui->participant->text();
    QString intitule = ui->intitule->text();
    QString statut = ui->statut->text();
    int nbr_participants = ui->nbr_participants->text().toInt();  // ← nouveau champ

    if (date.isEmpty() || duree <= 0 || participant.isEmpty() ||
        intitule.isEmpty() || statut.isEmpty() || nbr_participants < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement.");
        return;
    }

    Formation f(id, date, duree, participant, intitule, statut, nbr_participants);

    if (f.modifier(id)) {
        QMessageBox::information(this, "Modification", "Formation modifiée avec succès !");
        on_afficher_clicked();
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification.");
    }
}

void MainWindow::on_afficher_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare(
        "SELECT ID, DATES, DUREE, PARTICIPANT, INTITULE, STATUT, NBR_PARTICIPANTS "
        "FROM FORMATIONS");
    query.exec();
    model->setQuery(std::move(query));

    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("DATES"));
    model->setHeaderData(2, Qt::Horizontal, tr("DURÉE"));
    model->setHeaderData(3, Qt::Horizontal, tr("PARTICIPANT"));
    model->setHeaderData(4, Qt::Horizontal, tr("INTITULÉ"));
    model->setHeaderData(5, Qt::Horizontal, tr("STATUT"));
    model->setHeaderData(6, Qt::Horizontal, tr("Nbr Participants"));  // ← nouveau header

    ui->tableWidget->setModel(model);
}

void MainWindow::on_statistiques_clicked()
{
    FormationService service;
    QSqlQueryModel* model = service.afficherStatistiques();
    if (model->rowCount() == 0) {
        QMessageBox::warning(this, "Statistiques", "Aucune donnée trouvée.");
        return;
    }
    ui->tableWidget->setModel(model);
    QMessageBox::information(this, "Statistiques", "Les statistiques des formations ont été affichées.");
}

void MainWindow::on_pdf_clicked()
{
    FormationService service;
    QList<Formation> formations = service.obtenirFormations();
    service.exporterPDF(formations);
}

void MainWindow::on_presence_clicked()
{
    FormationService service;
    QSqlQueryModel* model = service.afficherPresence();
    ui->tableWidget->setModel(model);
    QMessageBox::information(this, "Présence", "Les informations de présence ont été affichées.");
}

void MainWindow::on_evaluations_clicked()
{
    // 1) Vérification de la sélection
    QModelIndexList rows = ui->tableWidget->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une formation.");
        return;
    }
    int formationId = rows.first().data().toInt();  // Colonne 0 = ID de la formation

    // 2) Préparer la requête JOIN
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QStringLiteral(R"(
        SELECT
            F.ID         AS FormationID,
            F.INTITULE   AS Intitule,
            E.ID_EVALUATION AS ID_Evaluation,
            E.PARTICIPANT_ID,
            E.POURCENTAGE,
            E.COMMENTAIRE
        FROM FORMATIONS F
        INNER JOIN EVALUATIONS E
          ON F.ID = E.ID_FORMATION
        WHERE F.ID = %1
    )").arg(formationId));

    if (model->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur SQL", model->lastError().text());
        delete model;
        return;
    }

    // 3) Nommer les colonnes pour l'affichage
    model->setHeaderData(0, Qt::Horizontal, "ID Formation");
    model->setHeaderData(1, Qt::Horizontal, "Intitulé");
    model->setHeaderData(2, Qt::Horizontal, "ID Éval.");
    model->setHeaderData(3, Qt::Horizontal, "ID Participant");
    model->setHeaderData(4, Qt::Horizontal, "Pourcentage");
    model->setHeaderData(5, Qt::Horizontal, "Commentaire");

    // 4) Afficher dans la vue
    ui->tableWidget->setModel(model);
    ui->tableWidget->resizeColumnsToContents();
}



void MainWindow::on_ajouterEvaluationBtn_clicked()
{
    // Step 1: Check selection
    QItemSelectionModel *selection = ui->tableWidget->selectionModel();
    if (!selection || !selection->hasSelection()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une formation dans le tableau.");
        return;
    }

    QModelIndex index = selection->currentIndex();
    int row = index.row();

    // Step 2: Get ID_FORMATION (col 0) and PARTICIPANT_ID (adjust if needed, e.g. col 3)
    int idFormation = ui->tableWidget->model()->index(row, 0).data().toInt();
    int participantId = ui->tableWidget->model()->index(row, 3).data().toInt(); // change if PARTICIPANT_ID is elsewhere

    qDebug() << "Selected formation ID:" << idFormation;
    qDebug() << "Selected participant ID:" << participantId;

    // Step 3: Ask for ID_EVALUATION
    bool ok;
    int idEvaluation = QInputDialog::getInt(this, "ID Évaluation", "Entrez un ID d'évaluation :", 0, 0, 1000000, 1, &ok);
    if (!ok) return;

    // Step 4: Ask for percentage
    double pourcentage = QInputDialog::getDouble(this, "Pourcentage", "Entrez le pourcentage :", 0, 0, 100, 2, &ok);
    if (!ok) return;

    // Step 5: Ask for comment
    QString commentaire = QInputDialog::getText(this, "Commentaire", "Entrez un commentaire :", QLineEdit::Normal, "", &ok);
    if (!ok || commentaire.isEmpty()) return;

    // Step 6: Insert into EVALUATIONS
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO EVALUATIONS (ID_EVALUATION, ID_FORMATION, PARTICIPANT_ID, POURCENTAGE, COMMENTAIRE)
        VALUES (:idEvaluation, :formationId, :participantId, :pourcentage, :commentaire)
    )");
    query.bindValue(":idEvaluation", idEvaluation);
    query.bindValue(":formationId", idFormation);
    query.bindValue(":participantId", participantId);
    query.bindValue(":pourcentage", pourcentage);
    query.bindValue(":commentaire", commentaire);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "✅ Évaluation ajoutée avec succès !");
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Échec de l'ajout : " + query.lastError().text());
    }
}




void MainWindow::on_tripardate_clicked()
{
    FormationService service;
    QSqlQueryModel* model = service.triParDate();
    ui->tableWidget->setModel(model);
    QMessageBox::information(this, "Tri par Date", "Les formations ont été triées par date.");
}

void MainWindow::on_triparduree_clicked()
{
    FormationService service;
    QSqlQueryModel* model = service.triParDuree();
    ui->tableWidget->setModel(model);
    QMessageBox::information(this, "Tri par Durée", "Les formations ont été triées par durée.");
}


//MAINWINDOW CONSULTANTS*******************************************************************************************

void MainWindow::setupStatisticsChart()
{
    // Only proceed if we're on page 5 (index 4)
    if (ui->stackedWidget->currentIndex() != 4) {
        if (chartContainer) {
            chartContainer->hide();  // Hide the chart if not on page 5
        }
        return;
    }

    // Create a query to get consultant names and hours
    QSqlQuery query;
    query.prepare("SELECT PRENOM_CONS, NOM_CONS, HEURES FROM consultants ORDER BY HEURES DESC");

    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError().text();
        return;
    }

    // Create bar sets
    QBarSet *set = new QBarSet("Heures travaillées");
    QStringList categories;

    while (query.next()) {
        QString firstName = query.value(0).toString();
        QString lastName = query.value(1).toString();
        int hours = query.value(2).toInt();

        *set << hours;
        categories << QString("%1 \n %2").arg(firstName).arg(lastName);
    }

    // Create series and add the bar set
    QBarSeries *series = new QBarSeries();
    series->append(set);
    series->setLabelsVisible(true);
    series->setLabelsFormat("@value heures");
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);

    // Create chart and add series
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des heures travaillées par consultant");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Create axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Heures");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Customize chart appearance
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Create chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Clean up previous container if it exists
    if (chartContainer) {
        chartContainer->deleteLater();
    }

    // Create a container widget for the chart
    chartContainer = new QWidget(this);
    chartContainer->setGeometry(1200, 450, 600, 350);  // x, y, width, height
    chartContainer->setStyleSheet("background-color: white; border: 1px solid #d0d0d0;");

    // Create and set the layout
    QVBoxLayout *chartLayout = new QVBoxLayout(chartContainer);
    chartLayout->setContentsMargins(5, 5, 5, 5);  // Small margin inside the container
    chartLayout->addWidget(chartView);

    // Show the container only if we're on page 5
    if (ui->stackedWidget->currentIndex() == 4) {
        chartContainer->show();
    } else {
        chartContainer->hide();
    }
}

void MainWindow::on_sortheureChanged(int index)
{
    // Get access to the consultant table view
    QStackedWidget* stackedWidget = ui->stackedWidget;
    QWidget* page = stackedWidget->widget(4);
    QStackedWidget* constStacked = page ? page->findChild<QStackedWidget*>("conststacked") : nullptr;
    QWidget* constPage = constStacked ? constStacked->widget(0) : nullptr;
    QTableView* consultant_tableview = constPage ? constPage->findChild<QTableView*>("consultant_tableview") : nullptr;

    if (!consultant_tableview) {
        qDebug() << "Failed to access consultant table view";
        return;
    }

    consultants consultant;
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr = "SELECT ID_CONS, NOM_CONS, PRENOM_CONS, EMAIL, TEL, CATEGORIE, MDP, HEURES, QUESTION, REPONSE "
                       "FROM consultants ";

    // Add sorting based on the selected option
    switch(index) {
    case 1: // "Nombre heures croissant"
        queryStr += "ORDER BY HEURES ASC";
        break;
    case 2: // "Nombre heures decroissant"
        queryStr += "ORDER BY HEURES DESC";
        break;
    case 3: // "Alphabétique croissant (Prénom)"
        queryStr += "ORDER BY PRENOM_CONS ASC";
        break;
    case 4: // "Alphabétique decroissant (Prénom)"
        queryStr += "ORDER BY PRENOM_CONS DESC";
        break;
    default:
        // No sorting (shouldn't happen as we have defined all options)
        break;
    }

    QSqlQuery query;
    if (query.exec(queryStr)) {
        model->setQuery(query);
        // Set headers
        model->setHeaderData(0, Qt::Horizontal, tr("ID_CONS"));
        model->setHeaderData(1, Qt::Horizontal, tr("NOM_CONS"));
        model->setHeaderData(2, Qt::Horizontal, tr("PRENOM_CONS"));
        model->setHeaderData(3, Qt::Horizontal, tr("EMAIL"));
        model->setHeaderData(4, Qt::Horizontal, tr("TEL"));
        model->setHeaderData(5, Qt::Horizontal, tr("CATEGORIE"));
        model->setHeaderData(6, Qt::Horizontal, tr("MDP"));
        model->setHeaderData(7, Qt::Horizontal, tr("HEURES"));
        model->setHeaderData(8, Qt::Horizontal, tr("QUESTION"));
        model->setHeaderData(9, Qt::Horizontal, tr("REPONSE"));

        consultant_tableview->setModel(model);
        consultant_tableview->resizeColumnsToContents();
    } else {
        qDebug() << "Sorting query error:" << query.lastError().text();
        delete model;
    }
}



void MainWindow::on_searchTextChanged(const QString &searchText)
{
    // Get access to the consultant table view (same way as in your constructor)
    QStackedWidget* stackedWidget = ui->stackedWidget;
    QWidget* page = stackedWidget->widget(4);
    QStackedWidget* constStacked = page ? page->findChild<QStackedWidget*>("conststacked") : nullptr;
    QWidget* constPage = constStacked ? constStacked->widget(0) : nullptr;
    QTableView* consultant_tableview = constPage ? constPage->findChild<QTableView*>("consultant_tableview") : nullptr;

    if (!consultant_tableview) {
        qDebug() << "Failed to access consultant table view";
        return;
    }

    consultants consultant;
    QSqlQueryModel *model;

    if (searchText.isEmpty()) {
        // If search is empty, show all consultants
        model = consultant.Afficherconsultants();
    } else {
        // Create a filtered model
        model = new QSqlQueryModel();
        QString queryStr = "SELECT ID_CONS, NOM_CONS, PRENOM_CONS, EMAIL, TEL, CATEGORIE, MDP, HEURES, QUESTION, REPONSE "
                           "FROM consultants WHERE "
                           "ID_CONS LIKE :search OR "
                           "NOM_CONS LIKE :search OR "
                           "PRENOM_CONS LIKE :search OR "
                           "EMAIL LIKE :search OR "
                           "TEL LIKE :search";

        QSqlQuery query;
        query.prepare(queryStr);
        query.bindValue(":search", "%" + searchText + "%");

        if (query.exec()) {
            model->setQuery(query);
            // Set headers (same as in Afficherconsultants())
            model->setHeaderData(0, Qt::Horizontal, tr("ID_CONS"));
            model->setHeaderData(1, Qt::Horizontal, tr("NOM_CONS"));
            model->setHeaderData(2, Qt::Horizontal, tr("PRENOM_CONS"));
            model->setHeaderData(3, Qt::Horizontal, tr("EMAIL"));
            model->setHeaderData(4, Qt::Horizontal, tr("TEL"));
            model->setHeaderData(5, Qt::Horizontal, tr("CATEGORIE"));
            model->setHeaderData(6, Qt::Horizontal, tr("MDP"));
            model->setHeaderData(7, Qt::Horizontal, tr("HEURES"));
            model->setHeaderData(8, Qt::Horizontal, tr("QUESTION"));
            model->setHeaderData(9, Qt::Horizontal, tr("REPONSE"));
        } else {
            qDebug() << "Search query error:" << query.lastError().text();
            delete model;
            return;
        }
    }

    consultant_tableview->setModel(model);
    consultant_tableview->resizeColumnsToContents();
}


void MainWindow::on_ajouterConst_clicked()
{

    // Retrieve input values from the UI
    QString nom_cons = ui->nom_9->text().trimmed(); // Trim whitespace
    QString prenom_cons = ui->prenom_9->text().trimmed();
    QString email = ui->email_9->text().trimmed();
    QString telStr = ui->tel_9->text().trimmed();
    QString categorie = ui->categorie_9->currentText();
    QString mdp = ui->mdp_9->text();
    QString heuresStr = ui->heures_9->text().trimmed();
    QString question = ui->question_9->currentText();
    QString reponse = ui->rep_9->text().trimmed();

    // Convert numeric fields
    bool telOk, heuresOk;
    int tel = telStr.toInt(&telOk);      // Convert to int (for NUMBER type in DB)
    int heures = heuresStr.toInt(&heuresOk); // Convert to int

    // Regular expressions for validation
    QRegularExpression nameRx("^[a-zA-Z]+$"); // Only letters for names
    QRegularExpression emailRx("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"); // Basic email validation
    QRegularExpression numberRx("^\\d+$"); // Only digits for phone number

    // Input validation
    if (!nameRx.match(nom_cons).hasMatch() || !nameRx.match(prenom_cons).hasMatch()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Le nom et le prénom doivent contenir uniquement des lettres."), QMessageBox::Cancel);
        return;
    }
    if (!emailRx.match(email).hasMatch()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez entrer une adresse email valide."), QMessageBox::Cancel);
        return;
    }
    if (!telOk) {
        QMessageBox::critical(this, tr("Erreur"), tr("Le numéro de téléphone doit être un nombre valide."), QMessageBox::Cancel);
        return;
    }


    // Create consultants object
    consultants consultant(0, nom_cons, prenom_cons, email, tel, categorie, mdp, heures, question, reponse);

    // Attempt to add consultant
    if (consultant.Ajouterconsultants()) {
        // Update the table view if addition was successful
        QStackedWidget* stackedWidget = ui->stackedWidget;
        QWidget* page = stackedWidget->widget(4);
        QStackedWidget* constStacked = page->findChild<QStackedWidget*>("conststacked");
        QWidget* constPage = constStacked->widget(0);
        QTableView* consultant_tableview = constPage->findChild<QTableView*>("consultant_tableview");

        if (consultant_tableview) {
            consultant_tableview->setModel(consultant.Afficherconsultants());
        }

        QMessageBox::information(this, tr("Succès"), tr("Ajout effectué."), QMessageBox::Cancel);

        // Clear input fields after addition
        ui->nom_9->clear();
        ui->prenom_9->clear();
        ui->email_9->clear();
        ui->tel_9->clear();
        ui->categorie_9->setCurrentIndex(-1); // Reset QComboBox selection
        ui->mdp_9->clear();
        ui->heures_9->clear();
        ui->question_9->setCurrentIndex(-1); // Reset QComboBox selection
        ui->rep_9->clear();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de l'ajout du consultant."), QMessageBox::Cancel);
    }
}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    if (!index.isValid()) {
        qDebug() << "Invalid index";
        return;
    }

    // Get the ID_CONS value from the selected row
    QString id_cons = ui->consultant_tableview->model()->data(ui->consultant_tableview->model()->index(index.row(), 0)).toString();

    // Display the selected ID in the QLineEdit
    ui->id_selected->setText(id_cons);

    // Check if it's a double-click event*********************************************************************************************************************
    if (QApplication::mouseButtons() == Qt::LeftButton && QApplication::keyboardModifiers() == Qt::NoModifier) {
        // Fetch the consultant's details from the database
        Connection c;
        c.closeConnection();
        QSqlQuery qry;

        qry.prepare("SELECT NOM_CONS, PRENOM_CONS, EMAIL, TEL, CATEGORIE, MDP, HEURES, QUESTION, REPONSE FROM consultants WHERE ID_CONS = :ID_CONS");
        qry.bindValue(":ID_CONS", id_cons);

        if (qry.exec() && qry.next()) {
            // Populate the input fields with the fetched data
            ui->nom_9->setText(qry.value(0).toString()); // NOM_CONS
            ui->prenom_9->setText(qry.value(1).toString()); // PRENOM_CONS
            ui->email_9->setText(qry.value(2).toString()); // EMAIL
            ui->tel_9->setText(qry.value(3).toString()); // TEL
            ui->categorie_9->setCurrentText(qry.value(4).toString()); // CATEGORIE
            ui->mdp_9->setText(qry.value(5).toString()); // MDP
            ui->heures_9->setText(qry.value(6).toString()); // HEURES
            ui->question_9->setCurrentText(qry.value(7).toString()); // QUESTION
            ui->rep_9->setText(qry.value(8).toString()); // REPONSE

            // Access the nested stacked widget (consultant_tableview) within stackedWidget (page 5)
            QStackedWidget* stackedWidget = ui->stackedWidget;
            QWidget* page = stackedWidget->widget(4); // Access page 5 (index 4)
            QStackedWidget* constStacked = page->findChild<QStackedWidget*>("conststacked");

            if (constStacked) {
                // Navigate to page 2 of the nested stacked widget
                constStacked->setCurrentIndex(1); // Assuming index 1 is page 2
            } else {
                qDebug() << "Failed to find the nested stacked widget 'conststacked'.";
            }
        } else {
            qDebug() << "Error fetching consultant details:" << qry.lastError().text();
        }

        // Close the database connection
        c.closeConnection();
    }
}
void MainWindow::onmodifier_clicked()
{
    // Get the selected row's ID_CONS
    QModelIndexList selectedIndexes = ui->consultant_tableview->selectionModel()->selectedIndexes();

    if (selectedIndexes.size() == 0) {
        return; // No selection, do nothing
    } else if (selectedIndexes.size() > 1) {
        QMessageBox::warning(this, tr("Sélection multiple"), tr("Veuillez sélectionner une seule ligne à modifier."), QMessageBox::Ok);
        return;
    }

    int id_cons = selectedIndexes.at(0).sibling(selectedIndexes.at(0).row(), 0).data().toInt();

    // Retrieve input values from the UI
    QString nom_cons = ui->nom_9->text();
    QString prenom_cons = ui->prenom_9->text();
    QString email = ui->email_9->text();
    QString telStr = ui->tel_9->text();
    QString categorie = ui->categorie_9->currentText();
    QString mdp = ui->mdp_9->text();
    QString heuresStr = ui->heures_9->text();
    QString question = ui->question_9->currentText();
    QString reponse = ui->rep_9->text();

    // Convert numeric fields
    bool telOk, heuresOk;
    int tel = telStr.toInt(&telOk);
    int heures = heuresStr.toInt(&heuresOk);

    // Input validation
    QRegularExpression nameRx("^[a-zA-Z]+$"); // Only letters for name fields
    QRegularExpression emailRx("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"); // Basic email validation
    QRegularExpression numberRx("^\\d+$"); // Only digits for numeric fields

    if (!nameRx.match(nom_cons).hasMatch() || !nameRx.match(prenom_cons).hasMatch()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Le nom et le prénom doivent contenir uniquement des lettres."), QMessageBox::Cancel);
    } else if (!emailRx.match(email).hasMatch()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez entrer une adresse email valide."), QMessageBox::Cancel);
    } else if (!numberRx.match(telStr).hasMatch()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Le numéro de téléphone doit contenir uniquement des chiffres."), QMessageBox::Cancel);
    } else {
        // Create consultants object
        consultants consultant(id_cons, nom_cons, prenom_cons, email, tel, categorie, mdp, heures, question, reponse);

        // Attempt to update consultant
        if (consultant.Modifierconsultants()) {
            // Update the table view if modification was successful
            ui->consultant_tableview->setModel(consultant.Afficherconsultants());
            QMessageBox::information(this, tr("Succès"), tr("Modification effectuée."), QMessageBox::Cancel);

            // Clear input fields after modification
            ui->nom_9->clear();
            ui->prenom_9->clear();
            ui->email_9->clear();
            ui->tel_9->clear();
            ui->categorie_9->setCurrentIndex(-1); // Reset QComboBox selection
            ui->mdp_9->clear();
            ui->heures_9->clear();
            ui->question_9->setCurrentIndex(-1); // Reset QComboBox selection
            ui->rep_9->clear();

            // Navigate back to page 1 of the nested stacked widget (consultant_tableview)
            QStackedWidget* stackedWidget = ui->stackedWidget;
            QWidget* page = stackedWidget->widget(4); // Access page 5 (index 4) of the outer stacked widget
            QStackedWidget* constStacked = page->findChild<QStackedWidget*>("conststacked");

            if (constStacked) {
                constStacked->setCurrentIndex(0); // Navigate to page 1 (index 0) of the nested stacked widget
            } else {
                qDebug() << "Failed to find the nested stacked widget 'conststacked'.";
            }
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de la modification du consultant."), QMessageBox::Cancel);
        }
    }
}
void MainWindow::on_supprimerbtn_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Voulez-vous supprimer ce consultant ?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Get the selected row's ID_CONS
        QModelIndexList selectedIndexes = ui->consultant_tableview->selectionModel()->selectedIndexes();

        if (selectedIndexes.size() == 0) {
            QMessageBox::warning(this, tr("Aucune sélection"), tr("Veuillez sélectionner une ligne à supprimer."), QMessageBox::Ok);
            return;
        }

        int id_cons = selectedIndexes.at(0).sibling(selectedIndexes.at(0).row(), 0).data().toInt();

        // Create consultants object
        consultants consultant;
        consultant.setID_CONS(id_cons);

        // Attempt to delete consultant
        if (consultant.Supprimerconsultants(QString::number(id_cons))) {
            // Update the table view if deletion was successful
            ui->consultant_tableview->setModel(consultant.Afficherconsultants());
            QMessageBox::information(this, tr("Succès"), tr("Suppression effectuée."), QMessageBox::Cancel);

            // Clear input fields after deletion
            ui->nom_9->clear();
            ui->prenom_9->clear();
            ui->email_9->clear();
            ui->tel_9->clear();
            ui->categorie_9->setCurrentIndex(-1); // Reset QComboBox selection
            ui->mdp_9->clear();
            ui->heures_9->clear();
            ui->question_9->setCurrentIndex(-1); // Reset QComboBox selection
            ui->rep_9->clear();
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de la suppression du consultant."), QMessageBox::Cancel);
        }
    }
}

void MainWindow::navigateToPage(int pageIndex)
{
    ui->stackedWidget->setCurrentIndex(pageIndex);
}


//Consultants

void MainWindow::navigateToEmployees()
{
    // Only allow navigation if user is a Consultant
    if (UserSession::instance().getCategory() == "Consultants") {
        ui->stackedWidget->setCurrentIndex(4); // Page 5 (index 4)
    }
}

void MainWindow::navigateToHome()
{
    // Only allow navigation if user is a Consultant
    if (UserSession::instance().getCategory() == "Consultants") {
        ui->stackedWidget->setCurrentIndex(2); // Page 3 (index 2)
    }
}

void MainWindow::navigateToStock()
{
    // Only allow navigation if user is a Consultant
    if (UserSession::instance().getCategory() == "Consultants") {
        ui->stackedWidget->setCurrentIndex(7); // Page 8 (index 7)
    }
}



void MainWindow::navigateBack()
{
    ui->stackedWidget->setCurrentIndex(0);  // Navigate to page 1 (index 0)
}

void MainWindow::navigateToClients()
{
    if (UserSession::instance().getCategory() == "Consultants") {
        QMessageBox::warning(this, tr("Accès refusé"),
                             tr("Désolé, vous n'avez pas les autorisations nécessaires pour accéder à cette page.\n"
                                "Seuls les clients de categorie direction et management peuvent accéder à cette section."));    }
}

void MainWindow::navigateToAppointments()
{
    if (UserSession::instance().getCategory() == "Consultants") {
        QMessageBox::warning(this, tr("Accès refusé"),
                             tr("Désolé, vous n'avez pas les autorisations nécessaires pour accéder à cette page.\n"
                                "Seuls les clients de categorie direction et management peuvent accéder à cette section."));    }
}

void MainWindow::navigateToTreatments()
{
    if (UserSession::instance().getCategory() == "Consultants") {
        QMessageBox::warning(this, tr("Accès refusé"),
                             tr("Désolé, vous n'avez pas les autorisations nécessaires pour accéder à cette page.\n"
                                "Seuls les personnels du support peuvent accéder à cette section."));    }
}



//Personnel du support

void MainWindow::navigateToResources()
{
    // Only allow navigation if user is a Consultant
    if (UserSession::instance().getCategory() == "Personnel du support") {
        ui->stackedWidget->setCurrentIndex(6);
    }
}

void MainWindow::stop1()
{
    if (UserSession::instance().getCategory() == "Personnel du support") {
        QMessageBox::warning(this, tr("Accès refusé"),
                             tr("Désolé, vous n'avez pas les autorisations nécessaires pour accéder à cette page.\n"
                                ));    }
}



//Direction et management
void MainWindow::navigateToclient()
{
    // Only allow navigation if user is a Consultant
    if (UserSession::instance().getCategory() == "Direction et management") {
        ui->stackedWidget->setCurrentIndex(3);
    }
}
void MainWindow::navigateToformation()
{
    // Only allow navigation if user is a Consultant
    if (UserSession::instance().getCategory() == "Direction et management") {
        ui->stackedWidget->setCurrentIndex(5);
    }
}

void MainWindow::stop2()
{
    if (UserSession::instance().getCategory() == "Direction et management") {
        QMessageBox::warning(this, tr("Accès refusé"),
                             tr("Désolé, vous n'avez pas les autorisations nécessaires pour accéder à cette page.\n"
                                ));    }
}
