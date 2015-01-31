/********************************************************************************
** Form generated from reading ui file 'qttest1.ui'
**
** Created: Fri Sep 19 22:34:53 2008
**      by: Qt User Interface Compiler version 4.4.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_QTTEST1_H
#define UI_QTTEST1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qttest1Class
{
public:

    void setupUi(QWidget *qttest1Class)
    {
    if (qttest1Class->objectName().isEmpty())
        qttest1Class->setObjectName(QString::fromUtf8("qttest1Class"));
    qttest1Class->resize(400, 300);

    retranslateUi(qttest1Class);

    QMetaObject::connectSlotsByName(qttest1Class);
    } // setupUi

    void retranslateUi(QWidget *qttest1Class)
    {
    qttest1Class->setWindowTitle(QApplication::translate("qttest1Class", "qttest1", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(qttest1Class);
    } // retranslateUi

};

namespace Ui {
    class qttest1Class: public Ui_qttest1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTEST1_H
