#ifndef STATISTICS_H
#define STATISTICS_H

#include <QApplication>
#include <QMap>
#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace QtCharts {
class QChartView;
class QChart;
class QPieSeries;
class QPieSlice;
}
QT_END_NAMESPACE

class statistics
{
public:
    statistics();
    QtCharts::QChartView* genererStatistiques();
};

#endif // STATISTICS_H
