#include "sac.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SAC w;
    w.show();

    return a.exec();
}
