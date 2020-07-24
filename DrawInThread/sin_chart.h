#ifndef SIN_CHART_H
#define SIN_CHART_H

#include <QObject>
#include <QPainter>

class Sin_Chart : public QObject
{
    Q_OBJECT
public:
    explicit Sin_Chart(int x, int y, int chart_width, int chart_height, QObject *parent = nullptr);

    void drawChart(QPainter *painter);
    void addAngle(int val);

private:
    int x_pos;
    int y_pos;
    QList<int> angle_ist;
};

#endif // SIN_CHART_H
