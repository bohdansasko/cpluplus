#ifndef DIALOGADDDATEVIEW_H
#define DIALOGADDDATEVIEW_H

#include <QDialog>
#include <QDate>

namespace Ui {
class dialogAddDateView;
}

class dialogAddDateView : public QDialog
{
    Q_OBJECT

public:
    explicit dialogAddDateView(QWidget *parent = 0);
    ~dialogAddDateView();

private:
    Ui::dialogAddDateView *ui;

    void clearFormAdd();

signals:
    void sendData(QDate, QString);

public slots:
    void add();
    void cancel();
};

#endif // DIALOGADDDATEVIEW_H
