#ifndef DIALOGSEARCHPACIENT_H
#define DIALOGSEARCHPACIENT_H

#include <QDialog>
#include <QDate>
#include <QSqlQueryModel>

namespace Ui {
class dialogsearchpacient;
}

class dialogsearchpacient : public QDialog {
    Q_OBJECT

public:
    explicit dialogsearchpacient(QWidget *parent = 0);
    ~dialogsearchpacient();

private:
    Ui::dialogsearchpacient *ui;

    QString sPIBOfPacient;
    int iTypeOfPacient;
    int id_details;

    QDate dOfBornPacient;
    QSqlQueryModel findModel;

    void clearFormSearch();
    void setDefaultView();
private slots:
    void findPacient(QString s);
    void CancelFind();
    void getDetails();
    void getIndex(QModelIndex ind);
    void switchOnBtn(QModelIndex);

signals:
    void sendData(int id);
};
#endif // DIALOGSEARCHPACIENT_H
