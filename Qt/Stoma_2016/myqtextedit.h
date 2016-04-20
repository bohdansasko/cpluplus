#ifndef MYQTEXTEDIT_H
#define MYQTEXTEDIT_H

#include <QTextEdit>

class MyQTextEdit: public QTextEdit {
    Q_OBJECT
public:
    MyQTextEdit(QWidget* p = 0);

    bool getBTextChanged();
    void resetBTextChanged();

private:
    bool m_bTextchanged;

protected:
    virtual void leaveEvent(QEvent *e);

public slots:
    void slotSetTextChanged();

signals:
    void signalLeave();
};

#endif // MYQTEXTEDIT_H
