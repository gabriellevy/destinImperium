#include "imperium.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Imperium w;
    w.LancerHistoire(Imperium::VIE_HUMAIN);
    w.show();

    return a.exec();
}
