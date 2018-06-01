#ifndef RIMET_H
#define RIMET_H

#include <QWidget>
#include <QTimer>
#include <QStringList>
#include <QMouseEvent>
#include <ExecvAdbCommon/execvadbcommon.h>
#include <QThread>

namespace Ui {
class rimet;
}

class rimet : public QWidget
{
    Q_OBJECT

public:
    explicit rimet(QWidget *parent = 0);
    ~rimet();
private slots:
    void on_home_clicked();

    void on_Unlock_clicked();

    void on_Right_clicked();

    void DisplayImage(QByteArray buf);
signals:
    void sendAdbCommon(QString cmd);

private:
    Ui::rimet *ui;
    ExecvAdbCommon *adb;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QPoint s_RighetPoint,e_RighetPoint,leftPoint;
};

#endif // RIMET_H
