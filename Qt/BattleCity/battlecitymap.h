#ifndef BATTLECITYMAP_H
#define BATTLECITYMAP_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QThread>

#include "tankforplayer.h"
#include "parsing.h"
#include "redwall.h"
#include <tankbot.h>
#include "udpclient.h"

class CBonus;

class BattleCityMap: public QGraphicsScene {
    Q_OBJECT
public:
    BattleCityMap(int regimeGame, bool _friend,  UdpClient* client, QObject* parent = 0);
            ~BattleCityMap();

    int m_Map[CNT_ROWS_MAP][CNT_COLS_MAP];      // розмер карты
    QList <QGraphicsItem *> m_listObjAroundBase;   // Елементы что розмещены вокруг базы

    bool AuditPressKey(int key);

    quint8  m_iGameMode;
    bool    m_deleteBase;
    bool    m_bIsGameOver;

private:
    CBonus *m_bonusStar;
    CBonus *m_bonusGrenade;
    CBonus *m_bonusTime;
    CBonus *m_bonusShovel;

    QTimer *m_timerMoveTankPL1;                 // Таймер для переміщення танку плеєра 1
    QTimer *m_timerMoveTankPL2;                 // та плеєра 2

    QTimer *m_timerMoveBot1;
    QTimer *m_timerMoveBot2;
    QTimer *m_timerMoveBot3;
    QTimer *m_timerMoveBot4;

    QTimer *m_timerMoveBots;
    QTimer *m_timerAuditBots;

    QTimer *m_timerShowBonusStar;              // Таймер для відображення та знищення бонусів
    QTimer *m_timerShowBonusGrenade;
    QTimer *m_timerShowBonusTime;
    QTimer *m_timerShowProtectionBase;

    QTimer *m_timerChangeSpeedBots;

    TankForPlayer *m_TankForPlay1;            // танк первого и
    TankForPlayer *m_TankForPlay2;            // в второго игрока

    TankBot       *m_tankBot1;
    TankBot       *m_tankBot2;
    TankBot       *m_tankBot3;
    TankBot       *m_tankBot4;

    QGraphicsTextItem *m_textGameOver;

    bool runOneBot;     // розрешает добавление первого бота на карту
    bool runTwoBot;
    bool runThreeBot;
    bool runFourBot;
    bool updateOnlyTwoBots; // переместить в данный момент только 2 бота(что-бы все боти одновременно не обновлялисьs)
    int  updateOnlyOneBots; // переместить в данный момень только 1 бота(когда все боты уже на карте)

//    QGraphicsPixmapItem *pixmapForStar;     // Тут зберігається картинка бонуса
    QGraphicsPixmapItem *pixmapForBase;
    QGraphicsPixmapItem *pixmapForBuildBase;
    QGraphicsPixmapItem *pixmapForRemoveBase;
//    QGraphicsPixmapItem *pixmapForTime;
//    QGraphicsPixmapItem *pixmapForExplosion;

    QList <QGraphicsPixmapItem *> m_listItems;          // обьекты белой стенки для защиты базы(если взят бонус защитить базу)

    CWorkWithFiles *p_ReadFromFile;                    // Клас для парсингу карти

    UdpClient *_client;
    QTimer    *timerForSendPosPlayer;
    bool       shot;

    int _increaseSpeedBots;

protected:
    virtual void keyPressEvent(QKeyEvent *event);       // Обробка нажаття клавіші та
    virtual void keyReleaseEvent(QKeyEvent *event);     // відпущення


signals:
    void signalTimeoutForOneBot   (                        ); // вызывается когда нужно переместить бота
    void signalTimeoutForTwoBot   (                        );
    void signalTimeoutForOneBot   ( int xBase , int yBase  ); // уничтожение базы
    void signalTimeoutForTwoBot   ( int xBase , int yBase  );

    void signalTimeoutForThreeBot (int xPlayer, int yPlayer);
    void signalTimeoutForFourBot  (int xPlayer, int yPlayer);

    void signalMoveOneBot   ();
    void signalMoveTwoBot   ();
    void signalMoveThreeBot ();
    void signalMoveFourBot  ();

    void signalUpdateBase(QString typeWall);

    void signalGameOver(int numberKillsOnePlayer, int numberKillsTwoPlayer);

public slots:
    void slotAddBot_1 ();           // появление бота на карте после уничтожения
    void slotAddBot_2 ();
    void slotAddBot_3 ();
    void slotAddBot_4 ();

    void slotShowBonusStar   ();            // отображение бонуса "Звезда"
    void slotRemoveBonusStar ();            // удаление бонуса "Звезда"

    void slotShowBonusProtectionBase ();    // показать бонус защиты базы
    void slotBuildProtectionForBase  ();    // построить защуиту вокруг базы
    void slotRemoveBonusForBase      ();
    void slotRemoveProtectionBase    ();    // удалить защиту вокруг базы

    void slotShowTimeBonus           ();    // показать бонус остановки танков
    void slotRemoveBonusTime ();    // завести всех танков

    void slotShowExplosionBonus        ();
    void slotRemoveExplosionBonus      ();
    void slotRemoveBonusGrenade ();

    void slotTimeout     ();        // определяет какой бот должен быть перемещён
    void slotMoveBots    ();        // вызывает слот который вызывает слот который определяет какой бот должен быть перемещён
    void slotRunOneBot   ();        // первоначальное помещение бота на карту
    void slotRunTwoBot   ();
    void slotRunThreeBot ();
    void slotRunFourBot  ();

    void slotGameOver    ();

    void slotSetPosPlayerForSend();
    void slotMoveOpponent(int x, int y, int rotate, bool shot2);
    void slotShotTank(QString str);
    void slotIncreaseSpeedBots();
};

#endif // BATTLECITYMAP_H
