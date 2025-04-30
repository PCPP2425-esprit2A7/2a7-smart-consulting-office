#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "consultants.h" // Include the consultants header
#include "login.h"
#include "ui_login.h"
#include "usersession.h"
#include "connection.h"
#include <QDebug>
#include <QPrinter>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QPdfWriter>
#include <QAxObject>
#include <QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QChartView>
#include <QVBoxLayout> //Gère la disposition des éléments graphiques

using namespace QtCharts;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // Initialize the ui pointer
{
    ui->setupUi(this); // Initialisation de l'interface utilisateur

    // un conteneur d'interfaces où l'on peut naviguer entre différentes pages
    QStackedWidget* stackedWidget = ui->stackedWidget;

    // Access page 5 (index 4) of the outer stacked widget
    QWidget* page = stackedWidget->widget(4);

    if (page) {
        // Access the inner stacked widget named "conststacked" within page 5
        QStackedWidget* constStacked = page->findChild<QStackedWidget*>("conststacked");

        if (constStacked) {
            // Access the first page (index 0) of the inner stacked widget
            QWidget* constPage = constStacked->widget(0);

            if (constPage) {
                // Access the table view named "consultant_tableview" within the first page of the inner stacked widget
                QTableView* consultant_tableview = constPage->findChild<QTableView*>("consultant_tableview");

                if (consultant_tableview) {
                    consultants consultants;
                    Connection c;

                    if (c.createconnect()) {
                        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                                QObject::tr("Connection successful.\nClick Cancel to exit."),
                                                QMessageBox::Cancel);

                        // Si des éléments ne sont pas trouvés des messages d'erreur sont affichés via QMessageBox
                        consultant_tableview->setModel(consultants.Afficherconsultants());
                        consultant_tableview->resizeColumnsToContents();
                        consultant_tableview->horizontalHeader()->setStretchLastSection(true);
                    } else {
                        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                                             QObject::tr("Connection failed.\nClick Cancel to exit."),
                                             QMessageBox::Cancel);
                    }
                } else {
                    QMessageBox::critical(nullptr, QObject::tr("Error"),
                                         QObject::tr("Failed to find the table view for consultants data."),
                                         QMessageBox::Cancel);
                }
            } else {
                QMessageBox::critical(nullptr, QObject::tr("Error"),
                                     QObject::tr("Failed to find the first page of the inner stacked widget."),
                                     QMessageBox::Cancel);
            }
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Error"),
                                 QObject::tr("Failed to find the inner stacked widget named 'conststacked'."),
                                 QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                             QObject::tr("Failed to find page 5 in the outer stacked widget."),
                             QMessageBox::Cancel);
    }


    // In MainWindow constructor

    connect(ui->employees_55, &QPushButton::clicked, this, &MainWindow::stop2);
    connect(ui->stock_55, &QPushButton::clicked, this, &MainWindow::stop2);
    connect(ui->clients_55, &QPushButton::clicked, this, &MainWindow::navigateToclient);
    connect(ui->appointements_55, &QPushButton::clicked, this, &MainWindow::navigateToformation);
    connect(ui->home_64, &QPushButton::clicked, this, &MainWindow::stop2);
    connect(ui->treatments_55, &QPushButton::clicked, this, &MainWindow::stop2);

    connect(ui->employees_55, &QPushButton::clicked, this, &MainWindow::stop1);
    connect(ui->stock_55, &QPushButton::clicked, this, &MainWindow::stop1);
    connect(ui->clients_55, &QPushButton::clicked, this, &MainWindow::stop1);
    connect(ui->appointements_55, &QPushButton::clicked, this, &MainWindow::stop1);
    connect(ui->home_64, &QPushButton::clicked, this, &MainWindow::stop1);
    connect(ui->treatments_55, &QPushButton::clicked, this, &MainWindow::navigateToResources);


    connect(ui->clients_55, &QPushButton::clicked, this, &MainWindow::navigateToClients);
    connect(ui->appointements_55, &QPushButton::clicked, this, &MainWindow::navigateToAppointments);
    connect(ui->treatments_55, &QPushButton::clicked, this, &MainWindow::navigateToTreatments);

    connect(ui->back_6, &QPushButton::clicked, this, &MainWindow::navigateBack);
    connect(ui->back_5, &QPushButton::clicked, this, &MainWindow::navigateBack);
    connect(ui->back_4, &QPushButton::clicked, this, &MainWindow::navigateBack);
    connect(ui->back_3, &QPushButton::clicked, this, &MainWindow::navigateBack);
    connect(ui->back_2, &QPushButton::clicked, this, &MainWindow::navigateBack);
    connect(ui->back, &QPushButton::clicked, this, &MainWindow::navigateBack);
    connect(ui->employees_55, &QPushButton::clicked, this, &MainWindow::navigateToEmployees);
    connect(ui->home_64, &QPushButton::clicked, this, &MainWindow::navigateToHome);
    connect(ui->stock_55, &QPushButton::clicked, this, &MainWindow::navigateToStock);
    // Connect the tableView's clicked and doubleClicked signals to the same slot
    connect(ui->consultant_tableview, &QTableView::clicked, this, &MainWindow::on_tableView_activated);
    connect(ui->consultant_tableview, &QTableView::doubleClicked, this, &MainWindow::on_tableView_activated);

    // Connect the modifier button's clicked signal
    connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifier_clicked);

    // Connect the delete button's clicked signal
    connect(ui->supprimerbtn, &QPushButton::clicked, this, &MainWindow::on_supprimerbtn_clicked);

    // Connect the navigation button's clicked signal
    connect(ui->gototable, &QPushButton::clicked, this, [this]() {
        // Access the outer stacked widget
        QStackedWidget* stackedWidget = ui->stackedWidget;

        // Access page 5 (index 4) of the outer stacked widget
        QWidget* page = stackedWidget->widget(4);

        if (page) {
            // Access the nested stacked widget named "conststacked" within page 5
            QStackedWidget* constStacked = page->findChild<QStackedWidget*>("conststacked");

            if (constStacked) {
                // Navigate to page 1 (index 0) of the nested stacked widget
                constStacked->setCurrentIndex(0);
            } else {
                qDebug() << "Failed to find the nested stacked widget 'conststacked'.";
            }
        } else {
            qDebug() << "Failed to find page 5 in the outer stacked widget.";
        }
    });
    connect(ui->goback, &QPushButton::clicked, this, [this]() {
        // Access the outer stacked widget
        QStackedWidget* stackedWidget = ui->stackedWidget;

        // Access page 5 (index 4) of the outer stacked widget
        QWidget* page = stackedWidget->widget(4);

        if (page) {
            // Access the nested stacked widget named "conststacked" within page 5
            QStackedWidget* constStacked = page->findChild<QStackedWidget*>("conststacked");

            if (constStacked) {
                // Navigate to page 1 (index 0) of the nested stacked widget
                constStacked->setCurrentIndex(1);
            } else {
                qDebug() << "Failed to find the nested stacked widget 'conststacked'.";
            }
        } else {
            qDebug() << "Failed to find page 5 in the outer stacked widget.";
        }
    });


    //recherche
    connect(ui->all_search_in_e_17, &QLineEdit::textChanged, this, &MainWindow::on_searchTextChanged);
    //trier
        ui->up_del_cin_in_e_17->addItem("trier");
        ui->up_del_cin_in_e_17->addItem("Nombre heures croissant");
        ui->up_del_cin_in_e_17->addItem("Nombre heures decroissant");
        ui->up_del_cin_in_e_17->addItem("Alphabétique croissant (Prénom)");  // Index 2
        ui->up_del_cin_in_e_17->addItem("Alphabétique decroissant (Prénom)"); // Index 3

        // Connect the combo box's currentIndexChanged signal
        connect(ui->up_del_cin_in_e_17, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &MainWindow::on_sortheureChanged);




        // In MainWindow constructor
        connect(ui->stackedWidget, &QStackedWidget::currentChanged, [this](int index) {
            if (index == 4) {  // Page 5
                setupStatisticsChart();
            } else if (chartContainer) {
                chartContainer->hide();
            }
        });

}

MainWindow::~MainWindow()
{
    delete ui; // Clean up the ui pointer
}


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
    QRegExp nameRx("^[a-zA-Z]+$"); // Only letters for names
    QRegExp emailRx("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"); // Basic email validation
    QRegExp numberRx("^\\d+$"); // Only digits for phone number

    // Input validation
    if (!nameRx.exactMatch(nom_cons) || !nameRx.exactMatch(prenom_cons)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Le nom et le prénom doivent contenir uniquement des lettres."), QMessageBox::Cancel);
        return;
    }
    if (!emailRx.exactMatch(email)) {
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
        c.closeconnection();
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
        c.closeconnection();
    }
}
void MainWindow::on_modifier_clicked()
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
    QRegExp nameRx("^[a-zA-Z]+$"); // Only letters for name fields
    QRegExp emailRx("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"); // Basic email validation
    QRegExp numberRx("^\\d+$"); // Only digits for numeric fields

    if (!nameRx.exactMatch(nom_cons) || !nameRx.exactMatch(prenom_cons)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Le nom et le prénom doivent contenir uniquement des lettres."), QMessageBox::Cancel);
    } else if (!emailRx.exactMatch(email)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez entrer une adresse email valide."), QMessageBox::Cancel);
    } else if (!numberRx.exactMatch(telStr)) {
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

