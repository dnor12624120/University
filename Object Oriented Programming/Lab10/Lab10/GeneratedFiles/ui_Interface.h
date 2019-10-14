/********************************************************************************
** Form generated from reading UI file 'Interface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceClass
{
public:
    QWidget *centralWidget;
    QTabWidget *tab;
    QWidget *admin_tab;
    QLabel *add_record_label;
    QLabel *title_label;
    QLabel *location_label;
    QLabel *toc_label;
    QLabel *at_label;
    QLabel *fp_label;
    QLineEdit *title_edit;
    QLineEdit *location_edit;
    QLineEdit *toc_edit;
    QLineEdit *at_edit;
    QLineEdit *fp_edit;
    QPushButton *add_record;
    QListWidget *list;
    QLabel *list_label;
    QPushButton *update_record;
    QPushButton *delete_record;
    QPushButton *add_to_list;
    QLabel *filter_label;
    QLabel *filter_location_label;
    QLabel *filter_at_label;
    QLineEdit *filter_location_edit;
    QLineEdit *filter_at_edit;
    QPushButton *filter;
    QLabel *set_filepath_label;
    QLineEdit *filepath_edit;
    QPushButton *set_filepath;
    QPushButton *view_list;
    QPushButton *open_list;
    QPushButton *next;
    QPushButton *undo;
    QPushButton *redo;
    QWidget *user_tab;
    QLabel *list_label_user;
    QPushButton *add_to_list_user;
    QPushButton *open_list_user;
    QListWidget *list_user;
    QPushButton *view_list_user;
    QLabel *set_filepath_label_user;
    QLabel *filter_location_label_user;
    QLineEdit *filepath_edit_user;
    QLabel *filter_label_user;
    QLabel *filter_at_label_user;
    QPushButton *filter_user;
    QLineEdit *filter_at_edit_user;
    QLineEdit *filter_location_edit_user;
    QPushButton *set_filepath_user;
    QPushButton *next_user;
    QPushButton *redo_user;
    QPushButton *undo_user;

    void setupUi(QMainWindow *InterfaceClass)
    {
        if (InterfaceClass->objectName().isEmpty())
            InterfaceClass->setObjectName(QString::fromUtf8("InterfaceClass"));
        InterfaceClass->resize(451, 445);
        centralWidget = new QWidget(InterfaceClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tab = new QTabWidget(centralWidget);
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setGeometry(QRect(0, 0, 611, 491));
        admin_tab = new QWidget();
        admin_tab->setObjectName(QString::fromUtf8("admin_tab"));
        add_record_label = new QLabel(admin_tab);
        add_record_label->setObjectName(QString::fromUtf8("add_record_label"));
        add_record_label->setGeometry(QRect(10, 10, 81, 16));
        title_label = new QLabel(admin_tab);
        title_label->setObjectName(QString::fromUtf8("title_label"));
        title_label->setGeometry(QRect(10, 30, 55, 16));
        location_label = new QLabel(admin_tab);
        location_label->setObjectName(QString::fromUtf8("location_label"));
        location_label->setGeometry(QRect(10, 50, 71, 16));
        toc_label = new QLabel(admin_tab);
        toc_label->setObjectName(QString::fromUtf8("toc_label"));
        toc_label->setGeometry(QRect(10, 70, 121, 16));
        at_label = new QLabel(admin_tab);
        at_label->setObjectName(QString::fromUtf8("at_label"));
        at_label->setGeometry(QRect(10, 90, 81, 16));
        fp_label = new QLabel(admin_tab);
        fp_label->setObjectName(QString::fromUtf8("fp_label"));
        fp_label->setGeometry(QRect(10, 110, 101, 16));
        title_edit = new QLineEdit(admin_tab);
        title_edit->setObjectName(QString::fromUtf8("title_edit"));
        title_edit->setGeometry(QRect(120, 30, 113, 16));
        location_edit = new QLineEdit(admin_tab);
        location_edit->setObjectName(QString::fromUtf8("location_edit"));
        location_edit->setGeometry(QRect(120, 50, 113, 16));
        toc_edit = new QLineEdit(admin_tab);
        toc_edit->setObjectName(QString::fromUtf8("toc_edit"));
        toc_edit->setGeometry(QRect(120, 70, 113, 16));
        at_edit = new QLineEdit(admin_tab);
        at_edit->setObjectName(QString::fromUtf8("at_edit"));
        at_edit->setGeometry(QRect(120, 90, 113, 16));
        fp_edit = new QLineEdit(admin_tab);
        fp_edit->setObjectName(QString::fromUtf8("fp_edit"));
        fp_edit->setGeometry(QRect(120, 110, 113, 16));
        add_record = new QPushButton(admin_tab);
        add_record->setObjectName(QString::fromUtf8("add_record"));
        add_record->setGeometry(QRect(80, 140, 93, 21));
        list = new QListWidget(admin_tab);
        list->setObjectName(QString::fromUtf8("list"));
        list->setGeometry(QRect(260, 30, 151, 251));
        list_label = new QLabel(admin_tab);
        list_label->setObjectName(QString::fromUtf8("list_label"));
        list_label->setGeometry(QRect(260, 10, 55, 16));
        update_record = new QPushButton(admin_tab);
        update_record->setObjectName(QString::fromUtf8("update_record"));
        update_record->setGeometry(QRect(80, 170, 93, 21));
        delete_record = new QPushButton(admin_tab);
        delete_record->setObjectName(QString::fromUtf8("delete_record"));
        delete_record->setGeometry(QRect(80, 200, 93, 21));
        add_to_list = new QPushButton(admin_tab);
        add_to_list->setObjectName(QString::fromUtf8("add_to_list"));
        add_to_list->setGeometry(QRect(290, 290, 93, 21));
        filter_label = new QLabel(admin_tab);
        filter_label->setObjectName(QString::fromUtf8("filter_label"));
        filter_label->setGeometry(QRect(10, 230, 81, 16));
        filter_location_label = new QLabel(admin_tab);
        filter_location_label->setObjectName(QString::fromUtf8("filter_location_label"));
        filter_location_label->setGeometry(QRect(10, 250, 91, 16));
        filter_at_label = new QLabel(admin_tab);
        filter_at_label->setObjectName(QString::fromUtf8("filter_at_label"));
        filter_at_label->setGeometry(QRect(10, 270, 91, 16));
        filter_location_edit = new QLineEdit(admin_tab);
        filter_location_edit->setObjectName(QString::fromUtf8("filter_location_edit"));
        filter_location_edit->setGeometry(QRect(120, 250, 113, 16));
        filter_at_edit = new QLineEdit(admin_tab);
        filter_at_edit->setObjectName(QString::fromUtf8("filter_at_edit"));
        filter_at_edit->setGeometry(QRect(120, 270, 113, 16));
        filter = new QPushButton(admin_tab);
        filter->setObjectName(QString::fromUtf8("filter"));
        filter->setGeometry(QRect(80, 300, 93, 21));
        set_filepath_label = new QLabel(admin_tab);
        set_filepath_label->setObjectName(QString::fromUtf8("set_filepath_label"));
        set_filepath_label->setGeometry(QRect(10, 330, 151, 16));
        filepath_edit = new QLineEdit(admin_tab);
        filepath_edit->setObjectName(QString::fromUtf8("filepath_edit"));
        filepath_edit->setGeometry(QRect(10, 350, 113, 16));
        set_filepath = new QPushButton(admin_tab);
        set_filepath->setObjectName(QString::fromUtf8("set_filepath"));
        set_filepath->setGeometry(QRect(20, 370, 93, 21));
        view_list = new QPushButton(admin_tab);
        view_list->setObjectName(QString::fromUtf8("view_list"));
        view_list->setGeometry(QRect(290, 320, 93, 21));
        open_list = new QPushButton(admin_tab);
        open_list->setObjectName(QString::fromUtf8("open_list"));
        open_list->setGeometry(QRect(290, 350, 93, 21));
        next = new QPushButton(admin_tab);
        next->setObjectName(QString::fromUtf8("next"));
        next->setGeometry(QRect(290, 380, 93, 21));
        undo = new QPushButton(admin_tab);
        undo->setObjectName(QString::fromUtf8("undo"));
        undo->setGeometry(QRect(180, 350, 93, 21));
        redo = new QPushButton(admin_tab);
        redo->setObjectName(QString::fromUtf8("redo"));
        redo->setGeometry(QRect(180, 380, 93, 20));
        tab->addTab(admin_tab, QString());
        user_tab = new QWidget();
        user_tab->setObjectName(QString::fromUtf8("user_tab"));
        list_label_user = new QLabel(user_tab);
        list_label_user->setObjectName(QString::fromUtf8("list_label_user"));
        list_label_user->setGeometry(QRect(260, 10, 55, 16));
        add_to_list_user = new QPushButton(user_tab);
        add_to_list_user->setObjectName(QString::fromUtf8("add_to_list_user"));
        add_to_list_user->setGeometry(QRect(290, 290, 93, 21));
        open_list_user = new QPushButton(user_tab);
        open_list_user->setObjectName(QString::fromUtf8("open_list_user"));
        open_list_user->setGeometry(QRect(290, 350, 93, 21));
        list_user = new QListWidget(user_tab);
        list_user->setObjectName(QString::fromUtf8("list_user"));
        list_user->setGeometry(QRect(260, 30, 151, 251));
        view_list_user = new QPushButton(user_tab);
        view_list_user->setObjectName(QString::fromUtf8("view_list_user"));
        view_list_user->setGeometry(QRect(290, 320, 93, 21));
        set_filepath_label_user = new QLabel(user_tab);
        set_filepath_label_user->setObjectName(QString::fromUtf8("set_filepath_label_user"));
        set_filepath_label_user->setGeometry(QRect(10, 210, 151, 16));
        filter_location_label_user = new QLabel(user_tab);
        filter_location_label_user->setObjectName(QString::fromUtf8("filter_location_label_user"));
        filter_location_label_user->setGeometry(QRect(10, 130, 91, 16));
        filepath_edit_user = new QLineEdit(user_tab);
        filepath_edit_user->setObjectName(QString::fromUtf8("filepath_edit_user"));
        filepath_edit_user->setGeometry(QRect(10, 230, 113, 16));
        filter_label_user = new QLabel(user_tab);
        filter_label_user->setObjectName(QString::fromUtf8("filter_label_user"));
        filter_label_user->setGeometry(QRect(10, 110, 81, 16));
        filter_at_label_user = new QLabel(user_tab);
        filter_at_label_user->setObjectName(QString::fromUtf8("filter_at_label_user"));
        filter_at_label_user->setGeometry(QRect(10, 150, 91, 16));
        filter_user = new QPushButton(user_tab);
        filter_user->setObjectName(QString::fromUtf8("filter_user"));
        filter_user->setGeometry(QRect(80, 180, 93, 21));
        filter_at_edit_user = new QLineEdit(user_tab);
        filter_at_edit_user->setObjectName(QString::fromUtf8("filter_at_edit_user"));
        filter_at_edit_user->setGeometry(QRect(120, 150, 113, 16));
        filter_location_edit_user = new QLineEdit(user_tab);
        filter_location_edit_user->setObjectName(QString::fromUtf8("filter_location_edit_user"));
        filter_location_edit_user->setGeometry(QRect(120, 130, 113, 16));
        set_filepath_user = new QPushButton(user_tab);
        set_filepath_user->setObjectName(QString::fromUtf8("set_filepath_user"));
        set_filepath_user->setGeometry(QRect(20, 250, 93, 21));
        next_user = new QPushButton(user_tab);
        next_user->setObjectName(QString::fromUtf8("next_user"));
        next_user->setGeometry(QRect(290, 380, 93, 21));
        redo_user = new QPushButton(user_tab);
        redo_user->setObjectName(QString::fromUtf8("redo_user"));
        redo_user->setGeometry(QRect(180, 380, 93, 21));
        undo_user = new QPushButton(user_tab);
        undo_user->setObjectName(QString::fromUtf8("undo_user"));
        undo_user->setGeometry(QRect(180, 350, 93, 21));
        tab->addTab(user_tab, QString());
        InterfaceClass->setCentralWidget(centralWidget);

        retranslateUi(InterfaceClass);

        tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InterfaceClass);
    } // setupUi

    void retranslateUi(QMainWindow *InterfaceClass)
    {
        InterfaceClass->setWindowTitle(QApplication::translate("InterfaceClass", "Interface", nullptr));
#ifndef QT_NO_TOOLTIP
        tab->setToolTip(QApplication::translate("InterfaceClass", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        add_record_label->setText(QApplication::translate("InterfaceClass", "Add record", nullptr));
        title_label->setText(QApplication::translate("InterfaceClass", "Title:", nullptr));
        location_label->setText(QApplication::translate("InterfaceClass", "Location:", nullptr));
        toc_label->setText(QApplication::translate("InterfaceClass", "Time of creation:", nullptr));
        at_label->setText(QApplication::translate("InterfaceClass", "Access time:", nullptr));
        fp_label->setText(QApplication::translate("InterfaceClass", "Footage preview:", nullptr));
        add_record->setText(QApplication::translate("InterfaceClass", "Add record", nullptr));
        list_label->setText(QApplication::translate("InterfaceClass", "List", nullptr));
        update_record->setText(QApplication::translate("InterfaceClass", "Update", nullptr));
        delete_record->setText(QApplication::translate("InterfaceClass", "Delete", nullptr));
        add_to_list->setText(QApplication::translate("InterfaceClass", "Add to list", nullptr));
        filter_label->setText(QApplication::translate("InterfaceClass", "Filter records", nullptr));
        filter_location_label->setText(QApplication::translate("InterfaceClass", "Location:", nullptr));
        filter_at_label->setText(QApplication::translate("InterfaceClass", "Acces time:", nullptr));
        filter->setText(QApplication::translate("InterfaceClass", "Filter", nullptr));
        set_filepath_label->setText(QApplication::translate("InterfaceClass", "Set user list filepath", nullptr));
        set_filepath->setText(QApplication::translate("InterfaceClass", "Set", nullptr));
        view_list->setText(QApplication::translate("InterfaceClass", "View list", nullptr));
        open_list->setText(QApplication::translate("InterfaceClass", "Open list", nullptr));
        next->setText(QApplication::translate("InterfaceClass", "Next", nullptr));
        undo->setText(QApplication::translate("InterfaceClass", "Undo", nullptr));
        redo->setText(QApplication::translate("InterfaceClass", "Redo", nullptr));
        tab->setTabText(tab->indexOf(admin_tab), QApplication::translate("InterfaceClass", "Admin", nullptr));
        list_label_user->setText(QApplication::translate("InterfaceClass", "List", nullptr));
        add_to_list_user->setText(QApplication::translate("InterfaceClass", "Add to list", nullptr));
        open_list_user->setText(QApplication::translate("InterfaceClass", "Open list", nullptr));
        view_list_user->setText(QApplication::translate("InterfaceClass", "View list", nullptr));
        set_filepath_label_user->setText(QApplication::translate("InterfaceClass", "Set user list filepath", nullptr));
        filter_location_label_user->setText(QApplication::translate("InterfaceClass", "Location:", nullptr));
        filter_label_user->setText(QApplication::translate("InterfaceClass", "Filter records", nullptr));
        filter_at_label_user->setText(QApplication::translate("InterfaceClass", "Acces time:", nullptr));
        filter_user->setText(QApplication::translate("InterfaceClass", "Filter", nullptr));
        set_filepath_user->setText(QApplication::translate("InterfaceClass", "Set", nullptr));
        next_user->setText(QApplication::translate("InterfaceClass", "Next", nullptr));
        redo_user->setText(QApplication::translate("InterfaceClass", "Redo", nullptr));
        undo_user->setText(QApplication::translate("InterfaceClass", "Undo", nullptr));
        tab->setTabText(tab->indexOf(user_tab), QApplication::translate("InterfaceClass", "User", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceClass: public Ui_InterfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
