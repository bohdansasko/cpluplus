#ifndef TANK_H
#define TANK_H

#include "bullet.h"

class TankForPlayer;
class QMediaPlayer;

class Tank: public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    explicit Tank(const QList<QString> fileNames,
                  QObject *parent = 0); // fileNames - пути к картинкам танка. Используются для анимации.
    ~Tank();

    QRectF boundingRect() const;        // Возвращет размеры танка в виде прямоугольника
    QPainterPath shape() const;         // Возвращет размеры танка в виде эллипса
    void paint(
               QPainter *painter,                       // Отрисовует танк и
               const QStyleOptionGraphicsItem *option,  // меняет его фреймы
               QWidget *widget
    );
    void setRotate2(int rotate); // поворачивание танка супротивника(при игре по сети)

public:
    int _friendOrBattle;

protected:
    QMediaPlayer *mpl;

    bool ArrowUp;
    bool ArrowDown;
    bool ArrowRight;
    bool ArrowLeft;
    bool KeySpace;

    bool collision;

    int iArrowUp;
    int iArrowDown;
    int iArrowRight;
    int iArrowLeft;
    int iKeySpace;

    struct Frame {
        QPixmap pixmap;
        QPainterPath shape;
        QRectF boundingRect;
    };

    enum Action {
        Key_Up = 0,
        Key_Down,
        Key_Right,
        Key_Left,
        Key_Space
    };


    void rotateUp   (bool c) { ArrowUp    = c;  }
    void rotateDown (bool c) { ArrowDown  = c;  }
    void rotateRight(bool c) { ArrowRight = c;  }
    void rotateLeft (bool c) { ArrowLeft  = c;  }

    void setRotate(int r);

    virtual void moveTank() {}

public:
    Bullet *shot();                             // Возвращает объект пули
    QList<Frame> m_listFrames;                  // Список фреймов, для танка.
                                                // Картинки, с которых делается анимация
    quint8  m_uiCurrentFrame;                   // Значение текущего фрейма
    quint8  m_uiSpeed;                          // Скорость танка
    quint16 m_uiRotate;                         // Текущее направление танка
    bool    m_bShot;                            // Разрешение на стрельбу. Если пуля ещё летит,
                                                // значит нельзя стрелять опять.
    QMap<int, Action> m_mapActions;             // Клавиши, которые "привязаны" к танку
    QList<int> m_listActiveKey;                 // Контейнер, в котором сохраняется последовательность,
                                                // зажатия несколько клавиш.
    QGraphicsItem *itemCollidesWith(QGraphicsItem *item);

protected:
    quint8  m_uiPower;                          // Сила танка

public slots:
    void slotMoveTank();
    void slotAllowShot(QObject *obj);
    void slotGameOver();

signals:
    void signalShot(QString typeObject);        // Сигнал стрельбы танка. Когда он поступает,
                                                // генерируется пуля и летит в своём направлении.
    void signalGameOver();
    void signalSearchNewWay(bool useRotate);
};

#endif // TANK_H
