#include "rimet.h"
#include "ui_rimet.h"
#include <QProcess>
#include <QImage>
#include <QFile>
#include <QDebug>


rimet::rimet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rimet)
{
    this->jiesuo=0;
    this->zuohua=0;
    this->shouye=0;
    this->zuojian=0;
    ui->setupUi(this);
    fflushTimer=new QTimer();
    connect(fflushTimer,SIGNAL(timeout()),this,SLOT(fflushImage()));
    fflushTimer->start();

}

rimet::~rimet()
{
    fflushTimer->stop();
    delete fflushTimer;
    delete ui;
}

void rimet::fflushImage()
{
    fflushTimer->stop();
    QProcess Cmd;
    Cmd.start("adb shell screencap -p");
    Cmd.waitForStarted();
    Cmd.waitForFinished();
    QByteArray img=Cmd.readAllStandardOutput().replace("'\r\r\n'","\n");
    QFile file("a.png");
    file.open(QIODevice::WriteOnly);
    file.write(img);
    file.close();
    QImage image("a.png");
    image=image.scaled(image.size()/4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->image->setPixmap(QPixmap::fromImage(image));
    ui->image->resize(image.size());
    if(zuojian==1)
    {
        QString zuojiancmd=tr("adb shell input tap %1 %2").arg(leftPoint.x()*4).arg(leftPoint.y()*4);
        qDebug()<<zuojiancmd;
        QProcess::execute(zuojiancmd);
        zuojian=0;
    }
    if(shouye==1){
        QProcess::execute("adb shell input keyevent 3");
        shouye=0;
    }
    if(zuohua==1)
    {
        QProcess::execute("adb shell input swipe 1000 1000 100 1000 300");
        zuohua=0;
    }
    if(jiesuo==1)
    {
        QProcess::execute("adb shell input keyevent 3");
        QProcess::execute("adb shell input swipe 500 2000 500 1000");
        QProcess::execute("adb shell input text 1994");
        jiesuo=0;
    }
    fflushTimer->start();
}

void rimet::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        leftPoint=event->globalPos();
        leftPoint=ui->image->mapFromGlobal(leftPoint);
        zuojian=1;
    }
}

void rimet::on_home_clicked()
{
    shouye=1;
}

void rimet::on_Unlock_clicked()
{
    jiesuo=1;
}

void rimet::on_Right_clicked()
{
    zuohua=1;
}
