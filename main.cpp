#include "tracking.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tracking w;
    w.show();

    return a.exec();
}
