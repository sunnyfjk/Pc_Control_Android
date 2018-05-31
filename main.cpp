#include "rimet.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rimet w;
    w.show();

    return a.exec();
}
