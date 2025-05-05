#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QWidget>
#include <QMap>
#include <QString>

class PieChartWidget : public QWidget {
    Q_OBJECT

public:
    explicit PieChartWidget(const QMap<QString, int>& data, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QMap<QString, int> m_data;
};

#endif // PIECHARTWIDGET_H
