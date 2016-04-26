#include "tank.h"

#include <QPixmap>
#include <QBitmap>
#include <QDebug>
#include "constants.h"
#include <QMediaPlayer>

Tank::Tank(const QList<QString> fileNames, QObject *parent) : QObject(parent),
    QGraphicsItem()
{

    mpl = new QMediaPlayer(this);

    m_uiCurrentFrame = 0;
    m_uiSpeed       = 0;
    m_bShot         = true;
    m_uiPower       = 1;
//    _numberKills = 0;
    collision    = false;
    _friendOrBattle = false;

    int size = fileNames.size();
    for (int i = 0; i < size; ++i) {
        QPixmap pixmap;
            pixmap.load(fileNames.at(i));
        Frame frame;
            frame.pixmap = pixmap;
            frame.shape = QPainterPath();
            frame.boundingRect = pixmap.rect();
            m_listFrames << frame;
    }
    m_uiRotate = 180;

    iArrowUp    = Qt::Key_Up;
    iArrowDown  = Qt::Key_Down;
    iArrowRight = Qt::Key_Right;
    iArrowLeft  = Qt::Key_Left;
    iKeySpace   = Qt::Key_Space;
}

Tank::~Tank() {
    m_mapActions.clear();
    deleteLater();
}
void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0, 0, m_listFrames.at(m_uiCurrentFrame).pixmap);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Tank::setRotate2(int rotate)
{
    switch (rotate)
    {
        case 0:
            {
                this->m_uiCurrentFrame = 4;
         break;
            }
        case 90:
            {
                this->m_uiCurrentFrame = 6;
        break;
            }
        case 180:
            {
                this->m_uiCurrentFrame = 0;
        break;
            }
        case 270:
            {
                this->m_uiCurrentFrame = 2;
        break;
            }
    }
    this->m_uiRotate = rotate;

    scene()->update();
}

void Tank::setRotate(int r) {
    m_uiRotate = r;
}

QRectF Tank::boundingRect() const {
    return QRectF(0, 0, 30, 30);
}

QPainterPath Tank::shape() const {
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

Bullet *Tank::shot() {
    QPoint pointStart;

    int x = this->x();
    int y = this->y();

    switch (this->m_uiRotate) {
        case 0: {
            pointStart = QPoint(x+13, y-6);
            break;
        }
        case 90: {
            pointStart = QPoint(x+38, y+13);
            break;
        }
        case 180: {
            pointStart = QPoint(x+19, y+38);
            break;
        }
        case 270: {
            pointStart = QPoint(x-6, y+19);
            break;
        }
    }

//    mpl->setMedia(QUrl("qrc:/sounds/fire.ogg"));
//    mpl->play();
//    qDebug() << "shot()";
    return (new Bullet(this->m_uiPower, pointStart, m_uiRotate));
}

void Tank::slotAllowShot(QObject* obj) {
    qDebug() << "object destroyed " << sender()->objectName();
    this->m_bShot = true;
}

void Tank::slotGameOver() {
    emit signalGameOver();
}

QGraphicsItem *Tank::itemCollidesWith(QGraphicsItem *item) {
    QList<QGraphicsItem *> collisions = scene()->collidingItems(item);
    foreach (QGraphicsItem *it, collisions) {
        if (it == item)
            continue;
        return it;
    }

    return NULL;
}

void Tank::slotMoveTank() {
    moveTank();
}
