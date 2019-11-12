/**
 * 叶海辉
 * QQ群121376426
 * http://blog.yundiantech.com/
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mPlayer = new VideoPlayer;
    connect(mPlayer,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(slotGetOneFrame(QImage))); //同步刷新显示的画面的信号与曹

    mPlayer->setFileName("E:\\2\\VideoPlayer_1\\Forrest.mp4"); //要播放的视频文件
    mPlayer->startPlay();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height()); //先画成黑色

    if (mImage.size().width() <= 0) return;//若图片的尺寸的宽度小于等于0，则返回，即没有图片则返回

    ///将图像按比例缩放成和窗口一样大小
    QImage img = mImage.scaled(this->size(),Qt::KeepAspectRatio);//为什么横着的是一样的大小？

    int x = this->width() - img.width();//显示电影画面周围的黑边框（x=0,y=h）
    int y = this->height() - img.height();
    //qDebug()<<"x1:"<<x<<"y1:"<<y<<endl;

    x /= 2;
    y /= 2;
    //qDebug()<<"x2:"<<x<<"y2:"<<y<<endl;


    painter.drawImage(QPoint(x,y),img); //画出图像

}

void MainWindow::slotGetOneFrame(QImage img)
{
    mImage = img;
    update(); //调用update将执行 paintEvent函数  会触发重绘的事件
}
