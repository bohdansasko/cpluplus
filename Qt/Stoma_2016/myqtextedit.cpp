#include "myqtextedit.h"

MyQTextEdit::MyQTextEdit(QWidget *p): QTextEdit(p) {
    m_bTextchanged = false;
    QObject::connect(this, SIGNAL(textChanged()), SLOT(slotSetTextChanged()));
}

bool MyQTextEdit::getBTextChanged() {
    return m_bTextchanged;
}

void MyQTextEdit::resetBTextChanged() {
    m_bTextchanged = false;
}

void MyQTextEdit::leaveEvent(QEvent *e) {
    emit signalLeave();
    Q_UNUSED(e);
}

void MyQTextEdit::slotSetTextChanged() {
    m_bTextchanged = true;
}
