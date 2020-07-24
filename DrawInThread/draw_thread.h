#ifndef DRAW_ECG_H
#define DRAW_ECG_H

#include <QObject>
#include <QPointer>
#include <QThread>

#include "sin_chart.h"

class Draw_Thread : public QThread
{
    Q_OBJECT
public:
    explicit Draw_Thread(QSize win_size, double devicePixelRatio, QObject *parent = nullptr);
    virtual ~Draw_Thread(){wait();}

    void startDraw();

signals:
    void updatePage(const QImage &image);

protected:
    void run() override;

private:
    QSize window_size;
    double devicePixelRatio;

    QPointer<Sin_Chart> SinChart;
};

#endif // DRAW_ECG_H
