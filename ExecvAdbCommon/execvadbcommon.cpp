#include "execvadbcommon.h"
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QString>

ExecvAdbCommon::ExecvAdbCommon(QObject *parent) : QObject(parent)
{
    fflush = new QTimer();
    connect(fflush,SIGNAL(timeout()),this,SLOT(fflushImageData()));
    fflush->start();
}

void ExecvAdbCommon::execvAdbCommon(QString cmd)
{
    cmdLock.lock();
    qDebug()<<cmd;
    QProcess::execute(cmd);
    cmdLock.unlock();
}
void ExecvAdbCommon::fflushImageData()
{
    cmdLock.lock();
    QProcess Cmd;
    Cmd.start("adb shell screencap -p");
    Cmd.waitForStarted();
    Cmd.waitForFinished();
    QByteArray buf=Cmd.readAllStandardOutput().replace("'\r\r\n'","\n");
    cmdLock.unlock();
    emit sendImageData(buf);
    fflush->start();
}
