#include "mainwindow.h"
#include "qsqlerror.h"
#include "ui_mainwindow.h"
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




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Calendar settings
    ui->calendarWidget->setGridVisible(true);   // Show the date grid
    ui->calendarWidget->setNavigationBarVisible(true);  // Show month/year navigation
    ui->calendarWidget->setDateEditEnabled(true);  // Enable date editing
    ui->tableView->setSortingEnabled(true);


    // Connect button clicks to respective slots
    connect(ui->btnAjouter, &QPushButton::clicked, this, &MainWindow::ajouterClient);
    connect(ui->btnAfficher, &QPushButton::clicked, this, &MainWindow::afficherClients);
    connect(ui->btnAfficher_1, &QPushButton::clicked, this, &MainWindow::afficherClients);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &MainWindow::supprimerClient);
    connect(ui->btnModifier, &QPushButton::clicked, this, &MainWindow::modifierClient);
    connect(ui->btnConfirmer, &QPushButton::clicked, this, &MainWindow::confirmerModification);
    connect(ui->btnNext, &QPushButton::clicked, this, &MainWindow::nextPage);
    connect(ui->btnPrev, &QPushButton::clicked, this, &MainWindow::prevPage);
    connect(ui->btnExportPDF, &QPushButton::clicked, this, &MainWindow::exportClientsToPDF);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::sortClientsByJoinDate);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchClientByCIN);




    afficherClients();

    // Connect the calendar date selection signal to the slot
    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &MainWindow::onCalendarDateSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ajouterClient()
{
    QString name = ui->lineEdit_name->text().trimmed();
    QString address = ui->lineEdit_address->text().trimmed();
    QString phone = ui->lineEdit_phone->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString nomEntreprise = ui->lineEdit_nom_entreprise->text().trimmed();
    QDate join_date = ui->calendarWidget->selectedDate();
    QString cin_client = ui->lineEdit_cin->text().trimmed();

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
    Client client(0, name, address, phone, email, nomEntreprise, nbr_consultation, join_date, cin_client);

    if (client.ajouter()) {
        QMessageBox::information(this, "Succès", "Client ajouté !");
        // Manually clear the input fields
        ui->lineEdit_name->clear();
        ui->lineEdit_address->clear();
        ui->lineEdit_phone->clear();
        ui->lineEdit_email->clear();
        ui->lineEdit_nom_entreprise->clear();
        ui->lineEdit_cin->clear();
        afficherClients();  // Refresh the list of clients
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du client.");
    }
}

void MainWindow::afficherClients()
{
    Client client(0, "", "", "", "", "", 0, QDate::currentDate(), "");
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

    Client client(0, "", "", "", "", "", 0, QDate::currentDate(), "");

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

    QString name = ui->lineEdit_name_2->text();
    QString address = ui->lineEdit_address_2->text();
    QString phone = ui->lineEdit_phone_2->text();
    QString email = ui->lineEdit_email_2->text();
    QString nomEntreprise = ui->lineEdit_nom_entreprise_2->text();
    int nbr_consultation = ui->lineEdit_nbr_consultation->text().toInt();
    QDate join_date = QDate::currentDate();
    QString cin_client = ui->lineEdit_cin2->text();

    Client client(id, name, address, phone, email, nomEntreprise, nbr_consultation, join_date, cin_client);

    if (client.modifier()) {
        QMessageBox::information(this, "Succès", "Client modifié avec succès.");

        // Manually clear the input fields
        ui->lineEdit_name_2->clear();
        ui->lineEdit_address_2->clear();
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

#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QSqlQueryModel>
#include <QFontMetrics>

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
void MainWindow::setupStatistics()
{
    // Create a new chart view using the stat() function from the Client class
    QChartView* chartView = client->stat();

    // Check if chartView is valid
    if (chartView != nullptr) {
        // Assuming "chartViewWidget" is the name of the widget in your UI
        ui->chartViewWidget->setLayout(new QVBoxLayout); // Set a layout for the widget
        ui->chartViewWidget->layout()->addWidget(chartView); // Add the chart view to the widget
    }
}






