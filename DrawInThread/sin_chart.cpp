#include "sin_chart.h"

#define _USE_MATH_DEFINES
#include <math.h>
Sin_Chart::Sin_Chart(int x, int y, int chart_width, int chart_height, QObject *parent) :
    QObject(parent), x_pos(x), y_pos(y)
{
}

void Sin_Chart::drawChart(QPainter *painter)
{
    QPen pen(QColor(0,0,0));
    painter->setPen(pen);

    //----------------------------------------------------
    int len = angle_ist.size();
    int pos = 0;
    int x = angle_ist[pos];
    while(pos < len)
    {
        double dsin = sin(x*M_PI/180);
        int y = dsin*180;
        painter->drawPoint(x_pos+x, y_pos-y);

        x = angle_ist[pos];
        pos++;
    }
    //-------------------------------------------------------
}
void Sin_Chart::addAngle(int val)
{
    angle_ist.append(val);
}
