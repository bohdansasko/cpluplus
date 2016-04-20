#ifndef MYQLABEL_H
#define MYQLABEL_H

#include <QLabel>
#include <QMouseEvent>

class MyQLabel : public QLabel {
    Q_OBJECT
public:
    MyQLabel(QWidget *par = 0);
    int x, y;

protected:
    virtual void mousePressEvent(QMouseEvent *e);

signals:
    void mouseClicked();
};

#endif // MYQLABEL_H
