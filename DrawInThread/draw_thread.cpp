#include "draw_thread.h"

Draw_Thread::Draw_Thread(QSize win_size, double pixelRatio, QObject *parent) :
    QThread(parent), window_size(win_size), devicePixelRatio(pixelRatio)
{
    //--- chart count == 6
    int chart_width = window_size.width();
    int chart_height = window_size.height();

    SinChart = new Sin_Chart(200, 200, chart_width, chart_height);
}

void Draw_Thread::startDraw()
{
    if (!isRunning())
        start(LowPriority);
}
void Draw_Thread::run()
{
    int angle = 0;

    QImage image(window_size, QImage::Format_ARGB32);
    image.setDevicePixelRatio(devicePixelRatio);
    QPainter pain(&image);
    while(true)
    {
       pain.eraseRect(image.rect());

       if(angle > 360)
           break;

       SinChart->addAngle(angle);
       SinChart->drawChart(&pain);

       emit updatePage(image);
       QThread::msleep(10);

       angle++;
    }
}
