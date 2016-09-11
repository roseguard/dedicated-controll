#include "dedicatedcontrol.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dedicatedControl w;
    w.show();

    return a.exec();
}
