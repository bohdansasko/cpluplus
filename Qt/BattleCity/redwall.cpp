#include "redwall.h"

#include <QtDebug>

RedWall::RedWall(const QString &temp_pathToImage): QGraphicsItem()
{
    pathToImage = temp_pathToImage;
    directShot = -1;
    checkForRemove = false;
}

/* virtual*/ void RedWall::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem *option,
                                 QWidget *widget)
{
    switch (directShot) {
        case 0: {
                painter->drawPixmap(QPointF(0, 0), QPixmap(pathToImage), QRectF(0.0, 0.0, 16.0, 8.0));
                if (wallHealth[0][0] & wallHealth[0][1])
                    wallHealth[0][0] = wallHealth[0][1] = true;
                else
                    wallHealth[1][0] = wallHealth[1][1] = true;
            break;
        }
        case 90: {
                painter->drawPixmap(QPointF(8, 0), QPixmap(pathToImage), QRectF(0.0, 0.0, 8.0, 16.0));
                if (wallHealth[0][1] & wallHealth[1][0])
                    wallHealth[0][1] = wallHealth[1][0] = true;
                else
                    wallHealth[1][1] = wallHealth[0][0] = true;
            break;
        }
        case 180: {
                painter->drawPixmap(QPointF(0, 8), QPixmap(pathToImage), QRectF(0.0, 0.0, 16.0, 8.0));
                if (wallHealth[1][0] & wallHealth[1][1])
                    wallHealth[1][0] = wallHealth[1][1] = true;
                else
                    wallHealth[0][0] = wallHealth[0][1] = true;
            break;
        }
        case 270: {
                painter->drawPixmap(QPointF(0, 0), QPixmap(pathToImage), QRectF(0.0, 0.0, 8.0, 16.0));
                if (wallHealth[0][0] & wallHealth[1][1])
                    wallHealth[0][0] = wallHealth[1][1] = true;
                else
                    wallHealth[0][1] = wallHealth[1][1] = true;
            break;
        }
        default:
                painter->drawPixmap(0, 0, QPixmap(pathToImage));
            break;
    }

    checkForRemove = wallHealth[0][0] | wallHealth[0][1] |  // Додаємо біти стін. І якщо всі біти == 1,
                     wallHealth[1][0] | wallHealth[1][1];   // потрібно знищити об’єкт.

    scene()->update();                                      // Обновлення сцени, щоб було видно зміни.

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF RedWall::boundingRect() const {
    return QRectF(0, 0, SIZE_WALL, SIZE_WALL);
}


