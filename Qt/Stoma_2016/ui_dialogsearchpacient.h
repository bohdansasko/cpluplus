/********************************************************************************
** Form generated from reading UI file 'dialogsearchpacient.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSEARCHPACIENT_H
#define UI_DIALOGSEARCHPACIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_dialogsearchpacient
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lineEdit_sName_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Details;
    QPushButton *pushButton_Cancel;

    void setupUi(QDialog *dialogsearchpacient)
    {
        if (dialogsearchpacient->objectName().isEmpty())
            dialogsearchpacient->setObjectName(QStringLiteral("dialogsearchpacient"));
        dialogsearchpacient->resize(580, 428);
        gridLayout_2 = new QGridLayout(dialogsearchpacient);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView = new QTableView(dialogsearchpacient);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 3, 0, 1, 1);

        label_3 = new QLabel(dialogsearchpacient);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(dialogsearchpacient);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        lineEdit_sName_2 = new QLineEdit(dialogsearchpacient);
        lineEdit_sName_2->setObjectName(QStringLiteral("lineEdit_sName_2"));
        lineEdit_sName_2->setEnabled(true);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        lineEdit_sName_2->setFont(font1);
        lineEdit_sName_2->setMouseTracking(true);
        lineEdit_sName_2->setReadOnly(false);

        gridLayout->addWidget(lineEdit_sName_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_Details = new QPushButton(dialogsearchpacient);
        pushButton_Details->setObjectName(QStringLiteral("pushButton_Details"));

        horizontalLayout->addWidget(pushButton_Details);

        pushButton_Cancel = new QPushButton(dialogsearchpacient);
        pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));

        horizontalLayout->addWidget(pushButton_Cancel);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(dialogsearchpacient);

        QMetaObject::connectSlotsByName(dialogsearchpacient);
    } // setupUi

    void retranslateUi(QDialog *dialogsearchpacient)
    {
        dialogsearchpacient->setWindowTitle(QApplication::translate("dialogsearchpacient", "\320\237\320\276\321\210\321\203\320\272 \320\277\320\260\321\206\321\226\321\224\320\275\321\202\320\260", 0));
        label_3->setText(QApplication::translate("dialogsearchpacient", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\270 \320\277\320\276\321\210\321\203\320\272\321\203:", 0));
        label_2->setText(QApplication::translate("dialogsearchpacient", "\320\237\321\200\321\226\320\267\320\262\320\270\321\211\320\265, \321\226\320\274\321\217, \320\277\320\276-\320\261\320\260\321\202\321\214\320\272\320\276\320\262\321\226:", 0));
        pushButton_Details->setText(QApplication::translate("dialogsearchpacient", "\320\224\320\265\321\202\320\260\320\273\321\214\320\275\321\226\321\210\320\265", 0));
        pushButton_Cancel->setText(QApplication::translate("dialogsearchpacient", "\320\241\320\272\320\260\321\201\321\203\320\262\320\260\321\202\320\270", 0));
    } // retranslateUi

};

namespace Ui {
    class dialogsearchpacient: public Ui_dialogsearchpacient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSEARCHPACIENT_H
