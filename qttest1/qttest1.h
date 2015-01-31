#ifndef QTTEST1_H
#define QTTEST1_H

#include <QtGui/QWidget>
#include "ui_qttest1.h"

class qttest1 : public QWidget
{
    Q_OBJECT

public:
    qttest1(QWidget *parent = 0);
    ~qttest1();

private:
    Ui::qttest1Class ui;
};

#endif // QTTEST1_H
