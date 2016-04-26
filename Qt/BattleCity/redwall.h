#ifndef REDWALL_H
#define REDWALL_H

#include <QGraphicsItem>
#include <QDebug>
#include <QImage>
#include <QObject>

#include "constants.h"
#include "battlecitymap.h"

const int PARTS_OF_BLOCK = 2;

class RedWall : public QGraphicsItem {
public:
    RedWall(const QString &temp_pathToImage);


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;        // Повернення розміру у вигляді прямокутника

    bool checkForRemove;
    int directShot;

private:
    /*
        BLOCK 16x16
        -------------
        |false|false|
        |     |     |
        |-----------|
        |false|false|
        |     |     |
        -------------
    */
    bool wallHealth[PARTS_OF_BLOCK][PARTS_OF_BLOCK];

    QString pathToImage;

};

#endif // REDWALL_H
