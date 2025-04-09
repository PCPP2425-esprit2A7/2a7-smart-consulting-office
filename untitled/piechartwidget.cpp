#include "piechartwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QtMath>

PieChartWidget::PieChartWidget(const QMap<QString, int>& data, QWidget* parent)
    : QWidget(parent), m_data(data) {
    setMinimumSize(600, 600);  // Taille minimale du widget
}

void PieChartWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int total = 0;
    for (auto value : m_data) {
        total += value;
    }

    if (total == 0) return;  // Evite la division par zéro

    QRectF rect(50, 50, width() - 150, height() - 100);  // Zone pour le pie chart
    int startAngle = 0;

    int colorIndex = 0;
    QVector<QColor> colors = {Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};

    // Dessiner le pie chart
    for (auto it = m_data.constBegin(); it != m_data.constEnd(); ++it) {
        int angleSpan = static_cast<int>(360.0 * it.value() / total * 16);
        painter.setBrush(colors[colorIndex % colors.size()]);
        painter.drawPie(rect, startAngle, angleSpan);
        startAngle += angleSpan;
        colorIndex++;
    }

    // Ajouter la légende
    int legendX = width() - 80;  // Position X de la légende
    int legendY = 50;            // Position Y de départ pour la légende
    int legendSpacing = 20;      // Espace vertical entre chaque item de la légende
    int colorIndexLegend = 0;

    for (auto it = m_data.constBegin(); it != m_data.constEnd(); ++it) {
        // Dessiner un carré de couleur pour chaque item
        painter.setBrush(colors[colorIndexLegend % colors.size()]);
        painter.drawRect(legendX, legendY, 15, 15);  // Carré de 15x15 pixels

        // Dessiner le texte de l'étiquette à côté du carré
        QString labelText = QString("%1: %2").arg(it.key()).arg(it.value());
        painter.setPen(Qt::black);  // Texte en noir
        painter.drawText(legendX + 20, legendY + 12, labelText);  // Texte à côté du carré

        legendY += legendSpacing;  // Passer à la ligne suivante
        colorIndexLegend++;
    }
}
