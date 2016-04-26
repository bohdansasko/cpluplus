#ifndef BONUS_H
#define BONUS_H

#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QGraphicsItem>

class QMediaPlayer;
class CBonus : public QObject, public QGraphicsItem {
        Q_OBJECT
    public:
        explicit CBonus(const QPixmap pixmapOfBonus,
                        const QPixmap pixmapOfScore, QObject *parent = 0);
        ~CBonus();

        void setTimeForRemove(const quint16 msec);
        void showBonus();
        void showScore();
        bool isTookBonus();

    protected:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private:
        QTimer *m_timerRemoveBonus;
        QTimer *m_timerShowScore;

        QPixmap *m_pixmapOfBonus;       // Бонус в виде картинки
        QPixmap *m_pixmapOfScore;       // Очки бонуса в виде картинки

        bool    m_showBonus;            // Показать бонус или очки бонуса
        QMediaPlayer *mpl;
    signals:
        void signalSendRemoveBonus();

    public slots:
        void slotShowScore();
        void slotSendShowBonus();
        void slotSendRemoveBonus();
};

#endif // BONUS_H
