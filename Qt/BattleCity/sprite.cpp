#include "sprite.h"

Sprite::Sprite(QPointF point, QString typeWall, QRectF tempSizeExplosion, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(point);
    this->setZValue(1);
    currentFrame = 0;
    sizeExplosion = tempSizeExplosion;
    spriteImage = new QPixmap(typeWall);

    timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(70);
}

QRectF Sprite::boundingRect() const
{
    return sizeExplosion;
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(sizeExplosion.x(), sizeExplosion.y(), *spriteImage, currentFrame, 0, sizeExplosion.width(), sizeExplosion.height());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Sprite::nextFrame()
{
    currentFrame += sizeExplosion.width();

    if (currentFrame >= 512)
    {
        this->deleteLater();

    } else
    {
        this->update(sizeExplosion);
    }

    this->update(sizeExplosion);
}

int Sprite::type() const
{
    return Type;
}
