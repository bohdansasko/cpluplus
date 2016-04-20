/********************************************************************************
** Form generated from reading UI file 'dialogadddateview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGADDDATEVIEW_H
#define UI_DIALOGADDDATEVIEW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_dialogAddDateView
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QDateEdit *dateEdit_DataViewForChange;
    QTextEdit *textEdit_DateViewMore;
    QLabel *label_12;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Add;
    QPushButton *pushButton_Cancel;

    void setupUi(QDialog *dialogAddDateView)
    {
        if (dialogAddDateView->objectName().isEmpty())
            dialogAddDateView->setObjectName(QStringLiteral("dialogAddDateView"));
        dialogAddDateView->resize(370, 368);
        gridLayout_2 = new QGridLayout(dialogAddDateView);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        dateEdit_DataViewForChange = new QDateEdit(dialogAddDateView);
        dateEdit_DataViewForChange->setObjectName(QStringLiteral("dateEdit_DataViewForChange"));
        dateEdit_DataViewForChange->setCalendarPopup(true);
        dateEdit_DataViewForChange->setDate(QDate(2015, 1, 1));

        gridLayout->addWidget(dateEdit_DataViewForChange, 1, 0, 1, 1);

        textEdit_DateViewMore = new QTextEdit(dialogAddDateView);
        textEdit_DateViewMore->setObjectName(QStringLiteral("textEdit_DateViewMore"));

        gridLayout->addWidget(textEdit_DateViewMore, 3, 0, 1, 1);

        label_12 = new QLabel(dialogAddDateView);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 2, 0, 1, 1);

        label_13 = new QLabel(dialogAddDateView);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_Add = new QPushButton(dialogAddDateView);
        pushButton_Add->setObjectName(QStringLiteral("pushButton_Add"));

        horizontalLayout->addWidget(pushButton_Add);

        pushButton_Cancel = new QPushButton(dialogAddDateView);
        pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));

        horizontalLayout->addWidget(pushButton_Cancel);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(dialogAddDateView);

        QMetaObject::connectSlotsByName(dialogAddDateView);
    } // setupUi

    void retranslateUi(QDialog *dialogAddDateView)
    {
        dialogAddDateView->setWindowTitle(QApplication::translate("dialogAddDateView", "\320\224\320\276\320\264\320\260\321\202\320\270 \320\276\320\263\320\273\321\217\320\264", 0));
        dateEdit_DataViewForChange->setDisplayFormat(QApplication::translate("dialogAddDateView", "dd-MM-yyyy", 0));
        label_12->setText(QApplication::translate("dialogAddDateView", "\320\220\320\275\320\260\320\274\321\202\320\265\320\267, \321\201\321\202\320\260\321\202\321\203\321\201, \320\264\321\226\320\260\320\263\320\275\320\276\320\267, \320\273\321\226\320\272\321\203\320\262\320\260\320\275\320\275\321\217, \321\200\320\265\320\272\320\276\320\274\320\265\320\275\320\264\320\260\321\206\321\226\321\227:", 0));
        label_13->setText(QApplication::translate("dialogAddDateView", "\320\224\320\260\321\202\320\260 \320\276\320\263\320\273\321\217\320\264\321\203:", 0));
        pushButton_Add->setText(QApplication::translate("dialogAddDateView", "\320\224\320\276\320\264\320\260\321\202\320\270", 0));
        pushButton_Cancel->setText(QApplication::translate("dialogAddDateView", "\320\241\320\272\320\260\321\201\321\203\320\262\320\260\321\202\320\270", 0));
    } // retranslateUi

};

namespace Ui {
    class dialogAddDateView: public Ui_dialogAddDateView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDDATEVIEW_H
