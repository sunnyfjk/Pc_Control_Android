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
    ui->setupUi(this);
    adb = new ExecvAdbCommon();
    connect(adb,SIGNAL(sendImageData(QByteArray)),this,SLOT(DisplayImage(QByteArray)));
    connect(this,SIGNAL(sendAdbCommon(QString)),adb,SLOT(execvAdbCommon(QString)));

}

rimet::~rimet()
{
    delete ui;
}


void rimet::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        QPoint leftPoint=event->globalPos();
        leftPoint=ui->image->mapFromGlobal(leftPoint);
        leftPoint=leftPoint*3;
        emit sendAdbCommon(tr("adb shell input tap %1 %2").arg(leftPoint.x()).arg(leftPoint.y()));
    }
}

void rimet::on_home_clicked()
{
    emit sendAdbCommon("adb shell input keyevent 3");
}

void rimet::on_Unlock_clicked()
{
    emit sendAdbCommon("adb shell input keyevent 3");
    emit sendAdbCommon("adb shell input swipe 500 2000 500 1000");
    emit sendAdbCommon("adb shell input text 1994");
}

void rimet::on_Right_clicked()
{
    emit sendAdbCommon("adb shell input swipe 1000 1000 100 1000 300");
}

void rimet::DisplayImage(QByteArray buf)
{
    QImage image;
    image.loadFromData(buf);
    image=image.scaled(image.size()/3,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->image->setPixmap(QPixmap::fromImage(image));
    ui->image->setMaximumSize(image.size());
    ui->image->setMinimumSize(image.size());
    ui->image->resize(image.size());
}
