#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mySin = new Draw_Thread(QSize(size().width(), size().height()), devicePixelRatioF());
    connect(mySin, &Draw_Thread::updatePage, this, &MainWindow::updatePage);

    mySin->startDraw();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent (QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    painter.drawPixmap(QPoint(), pixmap);
}

void MainWindow::updatePage(const QImage &image)
{
    pixmap = QPixmap::fromImage(image);
    update();
}
