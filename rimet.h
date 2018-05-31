#ifndef RIMET_H
#define RIMET_H

#include <QWidget>
#include <QTimer>
#include <QStringList>
#include <QMouseEvent>

namespace Ui {
class rimet;
}

class rimet : public QWidget
{
    Q_OBJECT

public:
    explicit rimet(QWidget *parent = 0);
    enum CMD{
        CMD_JIESUO,
        CMD_ZUOHUA,
        CMD_SHOUYE,
        CMD_LeftButton,
    };
    ~rimet();
private slots:
    void fflushImage();

    void on_home_clicked();

    void on_Unlock_clicked();

    void on_Right_clicked();

private:
    Ui::rimet *ui;
    QTimer *fflushTimer;
    uint8_t jiesuo,zuohua,shouye,zuojian;
    void mousePressEvent(QMouseEvent *event);
    QPoint leftPoint;
};

#endif // RIMET_H
