#ifndef EXECVADBCOMMON_H
#define EXECVADBCOMMON_H

#include <QObject>
#include <QImage>
#include <QMutex>
#include <QTimer>
#include <QString>
#include <QQueue>


class ExecvAdbCommon : public QObject
{
    Q_OBJECT
public:
    explicit ExecvAdbCommon(QObject *parent = nullptr);
public slots:
    void execvAdbCommon(QString cmd);

    void fflushImageData(void);
signals:
    void sendImageData(QByteArray buf);
private:
    QTimer *fflush;
    QMutex cmdLock;
};

#endif // EXECVADBCOMMON_H
