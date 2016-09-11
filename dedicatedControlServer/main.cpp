#include "dedicatedservcontrol.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dedicatedServControl w;
    w.show();

    return a.exec();
}
