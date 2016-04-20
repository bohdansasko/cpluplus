#include "dialogadddateview.h"
#include "ui_dialogadddateview.h"

dialogAddDateView::dialogAddDateView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAddDateView)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton_Add, SIGNAL(clicked(bool)), SLOT(add()) );
    QObject::connect(ui->pushButton_Cancel, SIGNAL(clicked(bool)), SLOT(cancel()) );
    ui->dateEdit_DataViewForChange->setDate(QDate::currentDate());
}

dialogAddDateView::~dialogAddDateView() {
    delete ui;
}

void dialogAddDateView::clearFormAdd() {
    ui->dateEdit_DataViewForChange->setDate(QDate::currentDate());
    ui->dateEdit_DataViewForChange->clear();
    ui->textEdit_DateViewMore->clear();
}

void dialogAddDateView::add() {
    QDate date = ui->dateEdit_DataViewForChange->date();
    QString status = ui->textEdit_DateViewMore->toPlainText();

    clearFormAdd();
    emit sendData(date, status);

    close();
}

void dialogAddDateView::cancel() {
    clearFormAdd();
    close();
}
