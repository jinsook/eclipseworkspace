#include "ui_mainwindow.h"

#include <QtGui>
#include <QApplication>
#include "qtgui/ecanvas.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow *widget = new QMainWindow;
    Ui::MainWindow ui;
    ui.setupUi(widget);
    widget->setCentralWidget(new ECanvas());
    widget->show();
    return a.exec();
}
