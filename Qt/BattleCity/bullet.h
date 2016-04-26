#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTime>

class QMediaPlayer;

class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bullet(int tempPowerTank, QPointF start, int angle, QObject *parent = 0);
    ~Bullet();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QTimer *timerBullet;
    int _speed;
    int powerTank;
    QMediaPlayer *mpl;

public:
    QString nameObjectSender;

private slots:
    void slotTimerBullet(); // Слот для обработки полёта пули

signals:
    void signalDestroy();
    void signalGameOver();
    void signalSendTypeOfKilledBot(QString);

};

#endif // BULLET_H

