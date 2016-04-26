#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QRectF>

class Sprite : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Sprite(QPointF point, QString typeWall, QRectF tempSizeExplosion, QObject *parent = 0);

    enum { Type = UserType + 1};

    int type() const;

signals:

public slots:

private slots:
    void nextFrame();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QRectF sizeExplosion;
    QTimer *timer;
    QPixmap *spriteImage;
    int currentFrame;

};

#endif // SPRITE_H
