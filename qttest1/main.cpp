#include "qttest1.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qttest1 w;
    w.show();
    return a.exec();
}
