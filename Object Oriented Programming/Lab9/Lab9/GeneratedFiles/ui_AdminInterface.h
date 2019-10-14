/********************************************************************************
** Form generated from reading UI file 'AdminInterface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMININTERFACE_H
#define UI_ADMININTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminInterfaceClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *AdminInterfaceClass)
    {
        if (AdminInterfaceClass->objectName().isEmpty())
            AdminInterfaceClass->setObjectName(QString::fromUtf8("AdminInterfaceClass"));
        AdminInterfaceClass->resize(800, 600);
        centralWidget = new QWidget(AdminInterfaceClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        AdminInterfaceClass->setCentralWidget(centralWidget);

        retranslateUi(AdminInterfaceClass);

        QMetaObject::connectSlotsByName(AdminInterfaceClass);
    } // setupUi

    void retranslateUi(QMainWindow *AdminInterfaceClass)
    {
        AdminInterfaceClass->setWindowTitle(QApplication::translate("AdminInterfaceClass", "AdminInterface", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminInterfaceClass: public Ui_AdminInterfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMININTERFACE_H
