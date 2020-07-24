#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include "draw_thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent (QPaintEvent *e);

public slots:
    void updatePage(const QImage &image);

private:
    Ui::MainWindow *ui;
    QPixmap pixmap;
    QPointer<Draw_Thread> mySin;
};
#endif // MAINWINDOW_H
