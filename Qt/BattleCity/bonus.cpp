#include "bonus.h"
#include "QDebug"
#include <QGraphicsScene>
#include <QMediaPlayer>

CBonus::CBonus(const QPixmap pixmapOfBonus,
               const QPixmap pixmapOfScore,
               QObject *parent) : QObject(parent)
{
    mpl = new QMediaPlayer();

    this->m_pixmapOfBonus = new QPixmap(pixmapOfBonus);
    this->m_pixmapOfScore = new QPixmap(pixmapOfScore);
    this->m_showBonus = true;

    m_timerRemoveBonus = new QTimer(this);

    QObject::connect( m_timerRemoveBonus, SIGNAL( timeout() ), this, SLOT( slotSendRemoveBonus() ));
}

CBonus::~CBonus() {}

void CBonus::showBonus() {
    m_showBonus = true;
}

bool CBonus::isTookBonus() {
    return !m_showBonus;
}

void CBonus::setTimeForRemove(const quint16 msec) {
    m_timerRemoveBonus->setInterval(msec);
}

QRectF CBonus::boundingRect() const {
    return QRectF(0, 0, 14, 7);
}

void CBonus::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    if (m_showBonus)
        painter->drawPixmap(0, 0, *this->m_pixmapOfBonus);
    else
        painter->drawPixmap(0, 0, *this->m_pixmapOfScore);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void CBonus::slotShowScore() {
    mpl->setMedia(QUrl("qrc:/sounds/bonus.ogg"));
    mpl->play();
    this->setData(0, "NULL");
    m_showBonus = false;
    m_timerRemoveBonus->stop();
    m_timerShowScore = new QTimer(this);
    m_timerShowScore->start(250);
    connect(m_timerShowScore, SIGNAL(timeout()), this, SLOT(slotSendRemoveBonus()));
    connect(m_timerShowScore, SIGNAL(timeout()), m_timerShowScore, SLOT(deleteLater()));
}

void CBonus::slotSendShowBonus() {
    m_timerRemoveBonus->start();
}


void CBonus::slotSendRemoveBonus() {
    m_timerRemoveBonus->stop();
    emit signalSendRemoveBonus();
}
