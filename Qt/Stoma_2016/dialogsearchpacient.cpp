#include "dialogsearchpacient.h"
#include "ui_dialogsearchpacient.h"
#include <QDebug>

dialogsearchpacient::dialogsearchpacient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogsearchpacient)
{
    ui->setupUi(this);
    ui->pushButton_Details->setEnabled(false);

    ui->tableView->setModel(&findModel);
    findModel.setQuery("SELECT id,pib,DOB,contactInfo FROM clients;");

    setDefaultView();

    QObject::connect(ui->pushButton_Details, SIGNAL(clicked(bool))       , SLOT(getDetails()));
    QObject::connect(ui->pushButton_Cancel , SIGNAL(clicked(bool))       , SLOT(CancelFind()));
    QObject::connect(ui->lineEdit_sName_2  , SIGNAL(textChanged(QString)), SLOT(findPacient(QString)));
    QObject::connect(ui->tableView         , SIGNAL(clicked(QModelIndex)), SLOT(getIndex(QModelIndex)));
    QObject::connect(ui->tableView         , SIGNAL(clicked(QModelIndex)), SLOT(switchOnBtn(QModelIndex)));
}

void dialogsearchpacient::setDefaultView() {
    ui->tableView->hideColumn(0); // hide id

    findModel.setHeaderData(1, Qt::Horizontal, tr("ПІБ"));
    findModel.setHeaderData(2, Qt::Horizontal, tr("Дата народження"));
    findModel.setHeaderData(3, Qt::Horizontal, tr("Контактна інформація"));

    emit ui->tableView->resizeColumnsToContents();
    emit ui->tableView->resizeRowsToContents();

}

dialogsearchpacient::~dialogsearchpacient() {
    delete ui;
}

void dialogsearchpacient::switchOnBtn(QModelIndex) {
    ui->pushButton_Details->setEnabled(true);
}

void dialogsearchpacient::getIndex(QModelIndex ind) {
    id_details = findModel.data(findModel.index(ind.row(), 0)).toInt();
    qDebug() << id_details;
}

void dialogsearchpacient::getDetails() {
    emit sendData(id_details);
    clearFormSearch();

    this->close();
}

void dialogsearchpacient::findPacient(QString s) {
    findModel.setQuery("SELECT id,pib,DOB,contactInfo FROM clients WHERE (pib LIKE \"%" + s + "%\");");
}

void dialogsearchpacient::clearFormSearch() {
    ui->lineEdit_sName_2->clear();
}

void dialogsearchpacient::CancelFind() {
    clearFormSearch();
    this->close();
}
