#include "myqlabel.h"

MyQLabel::MyQLabel(QWidget *par): QLabel(par) {}

void MyQLabel::mousePressEvent(QMouseEvent *e) {
    x = e->x();
    y = e->y();
    mouseClicked();
}
