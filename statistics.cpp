#include "statistics.h"
#include <QSqlQuery>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "qsqlerror.h"

statistics::statistics() {}

QtCharts::QChartView* statistics::genererStatistiques() {
    QPieSeries *series = new QPieSeries();

    QSqlQuery query;
    query.prepare("SELECT STATUS, COUNT(*) FROM PROJETS GROUP BY STATUS");

    if (query.exec()) {
        while (query.next()) {
            QString status = query.value(0).toString();
            int count = query.value(1).toInt();
            series->append(status, count);
        }
    } else {
        qDebug() << "Erreur SQL:" << query.lastError().text();
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des projets par statut");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}
