#include <QList>
#include <QString>
#include <QKeyEvent>
#include <QThread>
#include <QGraphicsTextItem>
#include "sprite.h"
#include "battlecitymap.h"
#include <QLabel>
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsGridLayout>
#include <QGraphicsLinearLayout>
#include "bonus.h"

BattleCityMap::BattleCityMap(int regimeGame, bool _friend, UdpClient *client, QObject* parent) : QGraphicsScene(parent)
{
    this->setBackgroundBrush(Qt::black);                        // Встановлення фонового кольору
    this->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);      // Встановлення розміру сцени з початковими координатами 0,0
                                                                // вверху лівої частини вікна
    timerForSendPosPlayer = new QTimer(this);
    shot = false;
    this->m_bIsGameOver = false;

    m_iGameMode = regimeGame;
    _increaseSpeedBots = CNT_SPEED_MOVE_BOTS;
    m_deleteBase = false;

    p_ReadFromFile = new CWorkWithFiles();
    p_ReadFromFile->ParsTextFile(":/log_parsing.txt", m_Map);               // Завантаження карти з файлу

    const QString fileConfig = "config.dat";
    QString namePlayer1 = "Player1",
            namePlayer2 = "Player2";
    bool    sound = true;
    p_ReadFromFile->readConfig(fileConfig, namePlayer1, namePlayer2, sound);// Читання імен танків та наявності звуку в ігрі

    QList<QString> fileNames;                                               // Фрейми для анімації танка
    fileNames << ":/Tanks/YellowTank/tank_Yellow_down_1.png"
              << ":/Tanks/YellowTank/tank_Yellow_down_2.png"
              << ":/Tanks/YellowTank/tank_Yellow_left_1.png"
              << ":/Tanks/YellowTank/tank_Yellow_left_2.png"
              << ":/Tanks/YellowTank/tank_Yellow_up_1.png"
              << ":/Tanks/YellowTank/tank_Yellow_up_2.png"
              << ":/Tanks/YellowTank/tank_Yellow_right_1.png"
              << ":/Tanks/YellowTank/tank_Yellow_right_2.png";

    QList<QString> botEasy;                                     // Фрейми для анімації танка
    botEasy << ":/tankBot_easy/Tanks/bot_easy/down_1.png"
              << ":/tankBot_easy/Tanks/bot_easy/down_2.png"
              << ":/tankBot_easy/Tanks/bot_easy/left_1.png"
              << ":/tankBot_easy/Tanks/bot_easy/left_2.png"
              << ":/tankBot_easy/Tanks/bot_easy/up_1.png"
              << ":/tankBot_easy/Tanks/bot_easy/up_2.png"
              << ":/tankBot_easy/Tanks/bot_easy/right_1.png"
              << ":/tankBot_easy/Tanks/bot_easy/right_2.png";

    QList<QString> botSpeed;                                     // Фрейми для анімації танка
    botSpeed  << ":/tankBot_speed/Tanks/bot_speed/down_1.png"
              << ":/tankBot_speed/Tanks/bot_speed/down_2.png"
              << ":/tankBot_speed/Tanks/bot_speed/left_1.png"
              << ":/tankBot_speed/Tanks/bot_speed/left_2.png"
              << ":/tankBot_speed/Tanks/bot_speed/up_1.png"
              << ":/tankBot_speed/Tanks/bot_speed/up_2.png"
              << ":/tankBot_speed/Tanks/bot_speed/right_1.png"
              << ":/tankBot_speed/Tanks/bot_speed/right_2.png";

    m_timerMoveTankPL1      = new QTimer(this);
    m_timerMoveTankPL2      = new QTimer(this);


//    timerRemoveProtectionBase  = new QTimer(this);

    m_timerMoveBot1   = new QTimer(this);
    m_timerMoveBot2   = new QTimer(this);
    m_timerMoveBot3   = new QTimer(this);
    m_timerMoveBot4   = new QTimer(this);
    m_timerMoveBots   = new QTimer(this);

    m_timerChangeSpeedBots = new QTimer(this);

    runOneBot   = false;
    runTwoBot   = false;
    runThreeBot = false;
    runFourBot  = false;

    updateOnlyTwoBots   = false;
    updateOnlyOneBots   = 0;

    if (regimeGame == 1)    // режым игры одного игрока
    {
        this->m_TankForPlay1 = new TankForPlayer(namePlayer1,fileNames, 1); // TankForPlayer приймає 2 параметри:
                                                                    // 1) фрейми для анімації
                                                                    // 2) Номер клавіш управління. Наприклад:
                                                                    //      1 - керування стрілками та вистріл через клавішу "space"
                                                                    //      2 - керування W,A,S,D та вистріл через клавішу "b"
        this->m_TankForPlay1->setZValue(0.5);
        this->m_TankForPlay1->setData(0, OBJ_NAME_PLAYER_1);                            // Ім’я об’єкта
        this->m_TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER, CNT_BEGIN_Y_ONE_PLAYER);   // Початкова позиція
        this->addItem(m_TankForPlay1);                                            // Добавлення на сцену

        this->m_timerMoveBot1->start(CNT_TIME_APPEARANCE_ONE_BOT);
        this->m_timerMoveBot1->setObjectName(OBJ_NAME_BOT_1);

        this->m_timerMoveBot2->start(CNT_TIME_APPEARANCE_TWO_BOT);
        this->m_timerMoveBot2->setObjectName(OBJ_NAME_BOT_2);

        this->m_timerMoveBot3->start(CNT_TIME_APPEARANCE_THREE_BOT);
        this->m_timerMoveBot3->setObjectName(OBJ_NAME_BOT_3);

        this->m_timerMoveBot4->start(CNT_TIME_APPEARANCE_FOUR_BOT);
        this->m_timerMoveBot4->setObjectName(OBJ_NAME_BOT_4);

        this->m_timerMoveBots->start(_increaseSpeedBots);

    }
    else if (regimeGame == 2)   // режым игры двоих игроков
    {
        m_TankForPlay1 = new TankForPlayer(namePlayer1, fileNames, 1);
        m_TankForPlay1->setZValue(0.5);
        m_TankForPlay1->setData(0, OBJ_NAME_PLAYER_1);                            // Ім’я об’єкта
        m_TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER, CNT_BEGIN_Y_ONE_PLAYER);   // Початкова позиція
        this->addItem(m_TankForPlay1);                                            // Добавлення на сцену

        m_TankForPlay2 = new TankForPlayer(namePlayer2, fileNames, 2);
        m_TankForPlay2->setData(0, OBJ_NAME_PLAYER_2);
        m_TankForPlay2->setPos(CNT_BEGIN_X_TWO_PLAYER, CNT_BEGIN_Y_TWO_PLAYER);
        m_TankForPlay2->setZValue(0.5);
        this->addItem(m_TankForPlay2);

        if (!_friend)
        {
            m_deleteBase = true;
            m_TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER_BATTLE, CNT_BEGIN_Y_ONE_PLAYER_BATTLE);
        }
        else
        {
            m_timerMoveBot1->start(CNT_TIME_APPEARANCE_ONE_BOT);
            m_timerMoveBot1->setObjectName(OBJ_NAME_BOT_1);

            m_timerMoveBot2->start(CNT_TIME_APPEARANCE_TWO_BOT);
            m_timerMoveBot2->setObjectName(OBJ_NAME_BOT_2);

            m_timerMoveBot3->start(CNT_TIME_APPEARANCE_THREE_BOT);
            m_timerMoveBot3->setObjectName(OBJ_NAME_BOT_3);

            m_timerMoveBot4->start(CNT_TIME_APPEARANCE_FOUR_BOT);
            m_timerMoveBot4->setObjectName(OBJ_NAME_BOT_4);

            m_timerMoveBots->start(_increaseSpeedBots);
        }

        QObject::connect( m_timerMoveTankPL2 , SIGNAL( timeout()           ), m_TankForPlay2  , SLOT( slotMoveTank()        ));
        QObject::connect( m_TankForPlay2   , SIGNAL( signalShot(QString) ), m_TankForPlay2  , SLOT( slotTankShot(QString) ));   // Постріл танком
        QObject::connect( m_TankForPlay2   , SIGNAL( signalShot(QString) ), this          , SLOT( slotShotTank(QString) ));   // Постріл танком

//        QObject::connect( TankForPlay2, SIGNAL( signalTankTookStar() ), this, SLOT( slotRemoveBonus() ));

        m_timerMoveTankPL2->start(CNT_SPEED_MOVE_ONE_PLAYER);
        m_timerMoveTankPL2->setObjectName(OBJ_NAME_PLAYER_2);
    }
    else if (regimeGame == 3)                        // игра по сети
    {
        m_TankForPlay1 = new TankForPlayer(namePlayer1, fileNames, 1);
        m_TankForPlay1->setZValue(0.5);
        m_TankForPlay1->setData(0, OBJ_NAME_PLAYER_1);                            // Ім’я об’єкта
        m_TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER, CNT_BEGIN_Y_ONE_PLAYER);   // Початкова позиція
        this->addItem(m_TankForPlay1);                                            // Добавлення на сцену

        m_TankForPlay2 = new TankForPlayer(namePlayer2,fileNames, 2);
        m_TankForPlay2->setData(0, OBJ_NAME_PLAYER_2);
        m_TankForPlay2->setPos(-40, 0);
        m_TankForPlay2->setZValue(0.5);
        this->addItem(m_TankForPlay2);

        if (!_friend)
        {
            m_deleteBase = true;
            m_TankForPlay1->setPos(CNT_BEGIN_X_ONE_PLAYER_BATTLE, CNT_BEGIN_Y_ONE_PLAYER_BATTLE);
            m_TankForPlay1->_friendOrBattle = true;
        }
        else
        {

            m_timerMoveBot1->start(CNT_TIME_APPEARANCE_ONE_BOT);
            m_timerMoveBot1->setObjectName(OBJ_NAME_BOT_1);

            m_timerMoveBot2->start(CNT_TIME_APPEARANCE_TWO_BOT);
            m_timerMoveBot2->setObjectName(OBJ_NAME_BOT_2);

            m_timerMoveBot3->start(CNT_TIME_APPEARANCE_THREE_BOT);
            m_timerMoveBot3->setObjectName(OBJ_NAME_BOT_3);

            m_timerMoveBot4->start(CNT_TIME_APPEARANCE_FOUR_BOT);
            m_timerMoveBot4->setObjectName(OBJ_NAME_BOT_4);

            m_timerMoveBots->start(_increaseSpeedBots);
        }

        _client = new UdpClient(client);
        timerForSendPosPlayer->start(CNT_TIMER_FOR_SEND_POS_PLAYER);

        QObject::connect( m_timerMoveTankPL2 , SIGNAL( timeout()           ), m_TankForPlay2  , SLOT( slotMoveTank()        ));
        QObject::connect( m_TankForPlay2   , SIGNAL( signalShot(QString) ), m_TankForPlay2  , SLOT( slotTankShot(QString) ));   // Постріл танком
        QObject::connect( m_TankForPlay2   , SIGNAL( signalShot(QString) ), this          , SLOT( slotShotTank()        ));   // Постріл танком

        QObject::connect( client , SIGNAL( signalReadInformationOpponent(int,int, int, bool)), this, SLOT( slotMoveOpponent(int,int, int, bool) ));

    }
    else
    {
        m_TankForPlay1 = new TankForPlayer(namePlayer1, fileNames, 1);
        m_TankForPlay1->setZValue(0.5);
        m_TankForPlay1->setData(0, OBJ_NAME_PLAYER_1);                            // Ім’я об’єкта
        m_TankForPlay1->setPos(CNT_BEGIN_X_TWO_PLAYER, CNT_BEGIN_Y_TWO_PLAYER);   // Початкова позиція
        this->addItem(m_TankForPlay1);                                            // Добавлення на сцену

        m_TankForPlay2 = new TankForPlayer(namePlayer2, fileNames, 2);
        m_TankForPlay2->setData(0, OBJ_NAME_PLAYER_2);
        m_TankForPlay2->setPos(-40, 0);
        m_TankForPlay2->setZValue(0.5);
        this->addItem(m_TankForPlay2);

        if (!_friend)
        {
            m_deleteBase = true;
        }
        else
        {
            m_timerMoveBot1->start(CNT_TIME_APPEARANCE_ONE_BOT);
            m_timerMoveBot1->setObjectName(OBJ_NAME_BOT_1);

            m_timerMoveBot2->start(CNT_TIME_APPEARANCE_TWO_BOT);
            m_timerMoveBot2->setObjectName(OBJ_NAME_BOT_2);

            m_timerMoveBot3->start(CNT_TIME_APPEARANCE_THREE_BOT);
            m_timerMoveBot3->setObjectName(OBJ_NAME_BOT_3);

            m_timerMoveBot4->start(CNT_TIME_APPEARANCE_FOUR_BOT);
            m_timerMoveBot4->setObjectName(OBJ_NAME_BOT_4);

            m_timerMoveBots->start(_increaseSpeedBots);
        }

        _client = new UdpClient(client);
        timerForSendPosPlayer->start(CNT_TIMER_FOR_SEND_POS_PLAYER);

        QObject::connect( m_timerMoveTankPL2 , SIGNAL( timeout()           ), m_TankForPlay2  , SLOT( slotMoveTank()        ));
        QObject::connect( m_TankForPlay2   , SIGNAL( signalShot(QString) ), m_TankForPlay2  , SLOT( slotTankShot(QString) ));   // Постріл танком
        QObject::connect( m_TankForPlay2   , SIGNAL( signalShot(QString) ), this          , SLOT( slotShotTank(QString) ));   // Постріл танком
        QObject::connect( client , SIGNAL( signalReadInformationOpponent(int,int, int, bool)), this, SLOT( slotMoveOpponent(int,int, int, bool) ));
    }

    const QString botType = "easy";
    m_tankBot1 = new TankBot(botEasy);
    m_tankBot1->setType(botType);
    m_tankBot1->addTank = false;
    m_tankBot1->setData(0, OBJ_NAME_BOT_1);
    m_tankBot1->setObjectName(OBJ_NAME_BOT_1);
    m_tankBot1->setPos(-32, 0);
    m_tankBot1->setZValue(0.5);
    this->addItem(m_tankBot1);

    m_tankBot2 = new TankBot(botSpeed);
    m_tankBot2->setType(botType);
    m_tankBot2->addTank = false;
    m_tankBot2->setData(0, OBJ_NAME_BOT_2);
    m_tankBot2->setObjectName(OBJ_NAME_BOT_2);
    m_tankBot2->setPos(-32, 0);
    m_tankBot2->setZValue(0.5);
    this->addItem(m_tankBot2);

    m_tankBot3 = new TankBot(botEasy);
    m_tankBot3->setType(botType);
    m_tankBot3->addTank = false;
    m_tankBot3->setData(0, OBJ_NAME_BOT_3);
    m_tankBot3->setObjectName(OBJ_NAME_BOT_3);
    m_tankBot3->setPos(-32, 0);
    m_tankBot3->setZValue(0.5);
    this->addItem(m_tankBot3);

    m_tankBot4 = new TankBot(botSpeed);
    m_tankBot4->setType(botType);
    m_tankBot4->addTank = false;
    m_tankBot4->setData(0, OBJ_NAME_BOT_4);
    m_tankBot4->setObjectName(OBJ_NAME_BOT_4);
    m_tankBot4->setPos(-32, 0);
    m_tankBot4->setZValue(0.5);
    this->addItem(m_tankBot4);

    m_timerMoveTankPL1->start(CNT_SPEED_MOVE_ONE_PLAYER);
    m_timerMoveTankPL1->setObjectName(OBJ_NAME_PLAYER_1);

    m_timerChangeSpeedBots->start(CNT_CHANGE_SPEED_BOTS);

    //
    m_timerShowBonusStar = new QTimer(this);
    m_timerShowBonusStar->start(CNT_SECOND_SHOW_STAR);

    m_timerShowBonusGrenade = new QTimer(this);
    m_timerShowBonusGrenade->start(CNT_SECOND_EXPLOSION_ALL_BOTS);

    m_timerShowBonusTime = new QTimer(this);
    m_timerShowBonusTime->start(CNT_SECOND_STOP_ALL_BOT);

    m_timerShowProtectionBase = new QTimer(this);
    m_timerShowProtectionBase->start(2500);


    QObject::connect( m_timerMoveTankPL1 , SIGNAL( timeout()           ) , m_TankForPlay1 , SLOT( slotMoveTank()        ));   // Переміщення танка
    QObject::connect( m_TankForPlay1   , SIGNAL( signalShot(QString) ) , m_TankForPlay1 , SLOT( slotTankShot(QString) ));   // Постріл танком
    QObject::connect( m_TankForPlay1   , SIGNAL( signalShot(QString) ) , this         , SLOT( slotShotTank(QString) ));   // Постріл танком

    QObject::connect( m_timerMoveBots , SIGNAL( timeout() )  , this, SLOT( slotMoveBots() ));

    QObject::connect( m_tankBot1   , SIGNAL( destroyed(QObject*) ), this , SLOT( slotAddBot_1() )); // убили первого бота - вернуть на карту
    QObject::connect( m_tankBot2 , SIGNAL( destroyed(QObject*) ), this , SLOT( slotAddBot_2() ));
    QObject::connect( m_tankBot3 , SIGNAL( destroyed(QObject*) ), this , SLOT( slotAddBot_3() ));
    QObject::connect( m_tankBot4 , SIGNAL( destroyed(QObject*) ), this , SLOT( slotAddBot_4() ));


    QObject::connect( m_timerMoveBot1   , SIGNAL( timeout()                       )   , this  , SLOT( slotRunOneBot() ));        // добавить первого бота на карту
    QObject::connect( this           , SIGNAL( signalMoveOneBot()              )   , this  , SLOT( slotTimeout()   ));        // обновить первого бота
    QObject::connect( this           , SIGNAL( signalTimeoutForOneBot()        )   , m_tankBot1   , SLOT( Atack(        ) ));        // найти путь к цели и переместить бота
    QObject::connect( this           , SIGNAL( signalTimeoutForOneBot(int,int) )   , m_tankBot1   , SLOT( Atack(int, int) ));        // найти путь к цели и переместить бота
    QObject::connect( m_tankBot1            , SIGNAL( signalShot(QString)             )   , m_tankBot1   , SLOT( slotTankShot(QString)  )); // стрелять

    QObject::connect( m_timerMoveBot2 , SIGNAL( timeout()                       )   , this  , SLOT( slotRunTwoBot() ));
    QObject::connect( this           , SIGNAL( signalMoveTwoBot()              )   , this  , SLOT( slotTimeout()   ));
    QObject::connect( this           , SIGNAL( signalTimeoutForTwoBot()        )   , m_tankBot2 , SLOT( Atack(        ) ));
    QObject::connect( m_tankBot2          , SIGNAL( signalShot(QString)             )   , m_tankBot2 , SLOT( slotTankShot(QString)  ));

    QObject::connect( m_timerMoveBot3 , SIGNAL ( timeout()                          ) , this  , SLOT( slotRunThreeBot()  ));
    QObject::connect( this           , SIGNAL ( signalMoveThreeBot()               ) , this  , SLOT( slotTimeout()      ));
    QObject::connect( this           , SIGNAL ( signalTimeoutForThreeBot(int,int)  ) , m_tankBot3 , SLOT( Atack(int, int)    ));
    QObject::connect( m_tankBot3     , SIGNAL ( signalShot(QString)                ) , m_tankBot3 , SLOT( slotTankShot(QString)     ));

    QObject::connect( m_timerMoveBot4 , SIGNAL( timeout()                        ) , this   , SLOT( slotRunFourBot()   ));
    QObject::connect( this           , SIGNAL( signalMoveFourBot()              ) , this   , SLOT( slotTimeout()                ));
    QObject::connect( this           , SIGNAL( signalTimeoutForFourBot(int,int) ) , m_tankBot4  , SLOT( Atack(int, int )             ));
    QObject::connect( m_tankBot4          , SIGNAL( signalShot(QString)              ) , m_tankBot4  , SLOT( slotTankShot(QString)        ));

    QObject::connect( m_timerShowBonusStar   , SIGNAL( timeout()), SLOT( slotShowBonusStar()              ));                 // Додавання бонусів на карту
    QObject::connect( m_timerShowBonusGrenade, SIGNAL( timeout()), SLOT( slotShowExplosionBonus()              ));

    QObject::connect( m_timerShowProtectionBase , SIGNAL( timeout()                      ), SLOT( slotShowBonusProtectionBase()     ));
    QObject::connect( m_timerShowBonusTime    , SIGNAL( timeout()           ), SLOT( slotShowTimeBonus()           ));

    QObject::connect( m_TankForPlay1, SIGNAL( signalGameOver()     ), this, SLOT( slotGameOver()    ));   // 3 убийствах танка
    QObject::connect( m_TankForPlay1, SIGNAL( signalGameOver()    ), this, SLOT( slotGameOver()    ));   // уничтожение базы
    QObject::connect( m_tankBot1         , SIGNAL( signalGameOver()    ), this, SLOT( slotGameOver()    ));   // уничтожение базы
    QObject::connect( m_tankBot2       , SIGNAL( signalGameOver()    ), this, SLOT( slotGameOver()    ));   // уничтожение базы
    QObject::connect( m_tankBot3       , SIGNAL( signalGameOver()    ), this, SLOT( slotGameOver()    ));   // уничтожение базы
    QObject::connect( m_tankBot4       , SIGNAL( signalGameOver()    ), this, SLOT( slotGameOver()    ));   // уничтожение базы


    QObject::connect( timerForSendPosPlayer , SIGNAL( timeout()), this, SLOT( slotSetPosPlayerForSend() ));

    QObject::connect( m_timerChangeSpeedBots  , SIGNAL( timeout()), this, SLOT( slotIncreaseSpeedBots()   ));

    delete p_ReadFromFile;
}

BattleCityMap::~BattleCityMap() {
    delete m_timerMoveTankPL1;
    delete m_timerMoveTankPL2;

    delete _client;

    delete m_TankForPlay1;
    if (m_iGameMode == 2 || m_iGameMode == 4) {
        delete m_TankForPlay2;
    }

    delete m_tankBot1;
    delete m_tankBot2;
    delete m_tankBot3;
    delete m_tankBot4;

    delete timerForSendPosPlayer;
    delete m_timerShowProtectionBase;
    delete m_timerMoveBot1;
    delete m_timerMoveBots;
    delete m_timerMoveBot2;
    delete m_timerMoveBot3;
    delete m_timerMoveBot4;
//    delete timerRemoveProtectionBase;
}

bool BattleCityMap::AuditPressKey(int key)
{
    Q_UNUSED(key);
    // LOL
//    if (!m_iGameMode == 2)   // если один игрок или сервер
//    {
//        if (
//            key != Qt::Key_Space &&
//            key != Qt::Key_Up    &&
//            key != Qt::Key_Down  &&
//            key != Qt::Key_Left  &&
//            key != Qt::Key_Right
//           )
//        {
//            return false;
//        }
//    }
//    else                     // два игрока
//    {
//        if (
//            key != Qt::Key_Space &&
//            key != Qt::Key_Up    &&
//            key != Qt::Key_Down  &&
//            key != Qt::Key_Left  &&
//            key != Qt::Key_Right &&
//            key != Qt::Key_B     &&
//            key != Qt::Key_W     &&
//            key != Qt::Key_S     &&
//            key != Qt::Key_A     &&
//            key != Qt::Key_D
//          )
//        {
//            return false;
//        }
//    }
    return true;
}

void BattleCityMap::slotSetPosPlayerForSend()
{
    int x = m_TankForPlay1->x();
    int y = m_TankForPlay1->y();
    int rotate = m_TankForPlay1->m_uiRotate;

    _client->SendMessage(x, y, rotate, shot);

    shot = false;
}

void BattleCityMap::slotMoveOpponent(int x, int y, int rotate, bool shot2)
{
    m_TankForPlay2->setPos(x, y);
    m_TankForPlay2->setRotate2(rotate);

    if (shot2)
    {
        emit m_TankForPlay2->signalShot(m_TankForPlay2->objectName());
//        qDebug() << "tank2 shot";
    }
}

void BattleCityMap::slotShotTank(QString str)
{
    shot = true;
    Q_UNUSED(str);
}

void BattleCityMap::slotIncreaseSpeedBots() {
    if (_increaseSpeedBots >= 40)
    {
        _increaseSpeedBots -= 10;
        m_timerMoveBots->start(_increaseSpeedBots);
    }
    else
    {
        m_timerMoveBots->start(_increaseSpeedBots);
    }
}

void BattleCityMap::slotTimeout() {
    if (runFourBot) // если все 4 бота на карте
    {
        switch (updateOnlyOneBots) {
        case 0: {
                if (_increaseSpeedBots == 40) {
                    emit signalTimeoutForOneBot(m_TankForPlay1->x(),  m_TankForPlay1->y());
                }
                else {
                    emit signalTimeoutForOneBot();
                }
                ++updateOnlyOneBots;
            break;
        }
        case 1:
            {
               emit signalTimeoutForTwoBot() ;
               ++updateOnlyOneBots;
            break;
            }
        case 2:
            {
                emit signalTimeoutForThreeBot ( m_TankForPlay1->x(), m_TankForPlay1->y() );
                ++updateOnlyOneBots;
            break;
            }
        case 3:
            {
                emit signalTimeoutForFourBot  ( m_TankForPlay1->x(), m_TankForPlay1->y() );
                updateOnlyOneBots = 0;
            break;
            }
        }
    }
    else if (runThreeBot)
    {
        if (updateOnlyTwoBots)
        {
            emit signalTimeoutForOneBot   ();
            emit signalTimeoutForThreeBot ( m_TankForPlay1->x(), m_TankForPlay1->y() );

            updateOnlyTwoBots = false;
        }
        else
        {
            emit signalTimeoutForTwoBot ();

            updateOnlyTwoBots = true;
        }
    }
    else if (runTwoBot)
    {
        if (updateOnlyTwoBots)
        {
            emit signalTimeoutForOneBot ();

            updateOnlyTwoBots = false;
        }
        else
        {
            emit signalTimeoutForTwoBot ();
            updateOnlyTwoBots = true;
        }
    }
    else if (runOneBot)
    {
        emit signalTimeoutForOneBot     ();
    }

}

void BattleCityMap::slotMoveBots()
{
    if (runFourBot) {            // когда все боты на карте послать сигналы для их перемещения
        emit signalMoveOneBot();
        emit signalMoveTwoBot();
        emit signalMoveThreeBot();
        emit signalMoveFourBot();
    }
    else if (runThreeBot) {
        emit signalMoveOneBot();
        emit signalMoveTwoBot();
        emit signalMoveThreeBot();
    }
    else if (runTwoBot) {
        emit signalMoveOneBot();
        emit signalMoveTwoBot();
    }
    else if (runOneBot) {
//        qDebug() << "signalMoveOneBot";
        emit signalMoveOneBot();
    }

}

void BattleCityMap::slotRunOneBot()
{
    m_timerMoveBot1->stop(); // останавливаем таймер для бота
    m_tankBot1->setPos(CNT_BEGIN_X_ONE_BOT, CNT_BEGIN_Y_ONE_BOT);    // помещяем на карту
    runOneBot = true;     // розрешаем боту двигатся
}

void BattleCityMap::slotRunTwoBot()
{
    m_timerMoveBot2->stop();
    m_tankBot2->setPos(CNT_BEGIN_X_TWO_BOT, CNT_BEGIN_Y_TWO_BOT);
    runTwoBot = true;
}

void BattleCityMap::slotRunThreeBot()
{
    m_timerMoveBot3->stop();
    m_tankBot3->setPos(CNT_BEGIN_X_THREE_BOT, CNT_BEGIN_Y_THREE_BOT);
    runThreeBot = true;
}

void BattleCityMap::slotRunFourBot()
{
    m_timerMoveBot4->stop();
    m_tankBot4->setPos(CNT_BEGIN_X_FOUR_BOT, CNT_BEGIN_Y_FOUR_BOT);
    runFourBot = true;
}

void BattleCityMap::slotShowBonusStar() {
    int x = ( rand() % WINDOW_WIDTH  ) - 30;
    int y = ( rand() % WINDOW_HEIGHT ) - 30;

    m_bonusStar = new CBonus(QPixmap(PATH_TO_STAR), QPixmap(IMG_STAR_SCORE), this);
    m_bonusStar->setPos(x, y);
    m_bonusStar->setVisible(true);
    m_bonusStar->setData(0, OBJ_NAME_STAR);
    m_bonusStar->setTimeForRemove(CNT_TIME_SHOW_BONUS);
    m_bonusStar->slotSendShowBonus();
    m_timerShowBonusStar->stop();

    this->addItem(m_bonusStar);
    QObject::connect(m_bonusStar, SIGNAL(signalSendRemoveBonus()), this, SLOT(slotRemoveBonusStar()));
}

void BattleCityMap::slotRemoveBonusStar() {
//    qDebug() << "delete bonus!";
//    m_bonusStar->deleteLater();
    this->removeItem(m_bonusStar);
    m_timerShowBonusStar->start();
}

void BattleCityMap::slotShowBonusProtectionBase() {
    uint x = ( rand() % WINDOW_WIDTH  ) - 30;
    uint y = ( rand() % WINDOW_HEIGHT ) - 30;
    x = y = 450;
    m_bonusShovel = new CBonus(QPixmap(PATH_TO_BONUS_BASE), QPixmap(IMG_TIME_SCORE), this);
    m_bonusShovel->setPos(x, y);
    m_bonusShovel->setVisible(true);
    m_bonusShovel->setData(0, OBJ_NAME_BASE_BONUS);
    m_bonusShovel->setTimeForRemove(CNT_TIME_SHOW_BONUS);
    m_bonusShovel->slotSendShowBonus();
    this->addItem(m_bonusShovel);

    m_timerShowProtectionBase->stop();
    QObject::connect(m_bonusShovel, SIGNAL(signalSendRemoveBonus()), this, SLOT(slotRemoveBonusForBase()));
}

void BattleCityMap::slotBuildProtectionForBase() {
    m_listObjAroundBase.clear();

    uint posX = 0;
    uint posY = 0;
    QGraphicsItem *item;
    // Левая сторона защиты базы

    posX = 14 * SIZE_WALL;
    for (uint i = 29; i < 32; i++) {
        posY =  i * SIZE_WALL;

        QTransform tr;
        item = this->itemAt( posX, posY, tr );
        if (item) {
            m_listObjAroundBase.push_back(item);
        }

        pixmapForBuildBase = addPixmap(QPixmap(PATH_TO_WHITE_WALL));
        pixmapForBuildBase->setPos( posX, posY );
        pixmapForBuildBase->setData(0, OBJ_NAME_WHITE_WALL);

        m_listItems.push_back(pixmapForBuildBase);
    }

    // Центр защиты базы
    posY = 28 * SIZE_WALL;
    for (uint i = 14; i < 19; i++) {
        posX =  i * SIZE_WALL;

        QTransform tr;
        item = this->itemAt( posX, posY, tr );
        if (item) {
            m_listObjAroundBase.push_back(item);
        }
        pixmapForBuildBase = addPixmap(QPixmap(PATH_TO_WHITE_WALL));
        pixmapForBuildBase->setPos( posX, posY );
        pixmapForBuildBase->setData(0, OBJ_NAME_WHITE_WALL);

        m_listItems.push_back(pixmapForBuildBase);
    }

    // Правая сторона защиты базы
    posX = 19 * SIZE_WALL;
    for (uint i = 28; i < 32; i++) {
        posY =  i * SIZE_WALL;

        QTransform tr;
        item = this->itemAt( posX, posY, tr );
        if (item) {
            m_listObjAroundBase.push_back(item);
        }

        pixmapForBuildBase = addPixmap(QPixmap(PATH_TO_WHITE_WALL));
        pixmapForBuildBase->setPos( posX, posY );
        pixmapForBuildBase->setData(0, OBJ_NAME_WHITE_WALL);

        m_listItems.push_back(pixmapForBuildBase);
    }
    item = NULL;
}

void BattleCityMap::slotRemoveBonusForBase() {
    if (m_bonusShovel->isTookBonus()) {
        m_timerShowProtectionBase->stop();
        emit slotBuildProtectionForBase();
        QTimer *timer = new QTimer(this);
        timer->start(CNT_SECOND_PROTECTION_BASE);
        QObject::connect(timer, SIGNAL(timeout()), m_timerShowProtectionBase , SLOT(start()));
        QObject::connect(timer, SIGNAL(timeout()), this , SLOT(slotRemoveProtectionBase()));
        QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(deleteLater()));
    } else {
        m_timerShowProtectionBase->start(CNT_SECOND_PROTECTION_BASE);
    }
    this->removeItem(m_bonusShovel);
}

void BattleCityMap::slotRemoveProtectionBase() {
    for (int i(0); i < m_listItems.size(); ++i) {          // удаляем временную белую стену
        removeItem(m_listItems[i]);
    }
    m_listItems.clear();

    for (int i(0); i < m_listObjAroundBase.size(); ++i) {   // помещяем елементы вокруг базы(что были с самого начала)
        addItem(m_listObjAroundBase[i]);
    }
}

void BattleCityMap::slotShowTimeBonus() {
    int x = ( rand() % WINDOW_WIDTH  ) - 30;
    int y = ( rand() % WINDOW_HEIGHT ) - 30;

    m_bonusTime = new CBonus(QPixmap(PATH_TO_BONUS_TIME), QPixmap(IMG_TIME_SCORE), this);
    m_bonusTime->setPos(x, y);
    m_bonusTime->setVisible(true);
    m_bonusTime->setData(0, OBJ_NAME_TIME_BONUS);
    m_bonusTime->setTimeForRemove(CNT_TIME_SHOW_BONUS);
    m_bonusTime->slotSendShowBonus();

    m_timerShowBonusTime->stop();
    this->addItem(m_bonusTime);
    QObject::connect(m_bonusTime, SIGNAL(signalSendRemoveBonus()), this, SLOT(slotRemoveBonusTime()));
}

void BattleCityMap::slotRemoveBonusTime() {
    if (m_bonusTime->isTookBonus()) {
        m_timerMoveBots->stop();
        QTimer *timer = new QTimer(this);
        timer->start(CNT_TIME_STOP_BOTS);
        QObject::connect(timer, SIGNAL(timeout()), m_timerShowBonusTime , SLOT(start()));
        QObject::connect(timer, SIGNAL(timeout()), m_timerMoveBots , SLOT(start()));
        QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(deleteLater()));
    } else {
        m_timerShowBonusTime->start();
    }
    this->removeItem(m_bonusTime);
}

void BattleCityMap::slotShowExplosionBonus() {
    int x = ( rand() % WINDOW_WIDTH  ) - 30;
    int y = ( rand() % WINDOW_HEIGHT ) - 30;

    m_bonusGrenade = new CBonus(QPixmap(PATH_TO_BONUS_EXPLOSION), QPixmap(IMG_GRANADE_SCORE), this);
    m_bonusGrenade->setPos(x, y);
    m_bonusGrenade->setVisible(true);
    m_bonusGrenade->setData(0, OBJ_NAME_EXPLOSION_BONUS);
    m_bonusGrenade->setTimeForRemove(CNT_TIME_SHOW_BONUS);
    m_bonusGrenade->slotSendShowBonus();

    m_timerShowBonusGrenade->stop();

    this->addItem(m_bonusGrenade);
    QObject::connect(m_bonusGrenade, SIGNAL(signalSendRemoveBonus()), this, SLOT(slotRemoveBonusGrenade()));
//    pixmapForExplosion->setPos(175, 440);
}

void BattleCityMap::slotRemoveExplosionBonus() {
//    this->removeItem(m_bonusGrenade);
//    m_timerForShowExplosionBonus->start(CNT_SECOND_EXPLOSION_ALL_BOTS);
//    m_timerRemoveExplosionBonus->stop();

    Sprite *explosion;
    QRectF  tankExplosionF  (-25, -25, 50, 50);
    explosion = new Sprite(QPoint(m_tankBot1->x(), m_tankBot1->y()), PATH_TO_TANK_EXPLOSION, tankExplosionF);
    addItem(explosion);
    emit slotAddBot_1();

    explosion = new Sprite(QPoint(m_tankBot2->x(), m_tankBot2->y()), PATH_TO_TANK_EXPLOSION, tankExplosionF);
    addItem(explosion);
    emit slotAddBot_2();

    explosion = new Sprite(QPoint(m_tankBot3->x(), m_tankBot3->y()), PATH_TO_TANK_EXPLOSION, tankExplosionF);
    addItem(explosion);
    emit slotAddBot_3();

    explosion = new Sprite(QPoint(m_tankBot4->x(), m_tankBot4->y()), PATH_TO_TANK_EXPLOSION, tankExplosionF);
    addItem(explosion);
    emit slotAddBot_4();
}

void BattleCityMap::slotRemoveBonusGrenade() {
    if (m_bonusGrenade->isTookBonus()) {
        emit slotRemoveExplosionBonus();
    }

    m_timerShowBonusGrenade->start();
    this->removeItem(m_bonusGrenade);
}


/* virtual*/ void BattleCityMap::keyPressEvent(QKeyEvent *event) {
    if (this->m_bIsGameOver) {
        return;
    }

    int key = event->key();
//    qDebug() << "key = " << key;
    if (m_TankForPlay1->m_mapActions.contains(key)) {
        emit m_TankForPlay1->keyPressEvent(event);
    }
    else if (m_iGameMode == 2 && m_TankForPlay2->m_mapActions.contains(key)) {
        emit m_TankForPlay2->keyPressEvent(event);
    }
}

/* virtual */void BattleCityMap::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();
    if (m_TankForPlay1->m_mapActions.contains(key)) {
        emit m_TankForPlay1->keyReleaseEvent(event);
    }
    else if (m_iGameMode == 2 && m_TankForPlay2->m_mapActions.contains(key)) {
        emit m_TankForPlay2->keyReleaseEvent(event);
    }
}

void BattleCityMap::slotAddBot_2()
{
    ++m_tankBot2->numberDeaths;

    QList <QGraphicsItem *> listItems;
    int _x = 128;
    QRectF myRect;
    myRect.setX(_x);
    myRect.setY(0);
    myRect.setWidth(128);
    myRect.setHeight(30);

    do
    {
        listItems.clear();
        myRect.setX(_x);
        _x += 128;
        listItems = this->items(myRect, Qt::IntersectsItemShape, Qt::AscendingOrder);

        if (_x > 500)
        {
            _x = 0;
        }
//        qDebug() << "bot_2";
    } while(listItems.size() != 0);

    _x -= 32;
    m_tankBot2->setPos(_x, 0);
    m_tankBot2->setData(0, OBJ_NAME_BOT_2);
    m_tankBot2->setObjectName(OBJ_NAME_BOT_2);
    m_tankBot2->setZValue(0.5);
    this->addItem(m_tankBot2);
}

void BattleCityMap::slotAddBot_3()
{
    ++m_tankBot3->numberDeaths;

    QList <QGraphicsItem *> listItems;
    int _x = 0;
    QRectF myRect;
    myRect.setX(_x);
    myRect.setY(0);
    myRect.setWidth(128);
    myRect.setHeight(30);

    do
    {
        listItems.clear();
        myRect.setX(_x);
        _x += 128;
        listItems = this->items(myRect, Qt::IntersectsItemShape, Qt::AscendingOrder);

        if (_x > 500)
        {
            _x = 0;
        }
//        qDebug() << "bot_3";
    } while(listItems.size() != 0);

    _x -= 32;
    m_tankBot3->setPos(_x, 0);
    m_tankBot3->setData(0, OBJ_NAME_BOT_3);
    m_tankBot3->setObjectName(OBJ_NAME_BOT_3);
    m_tankBot3->setZValue(0.5);
    this->addItem(m_tankBot3);
}

void BattleCityMap::slotAddBot_4()
{
    ++m_tankBot4->numberDeaths;

    QList <QGraphicsItem *> listItems;
    int _x = 0;
    QRectF myRect;
    myRect.setX(_x);
    myRect.setY(0);
    myRect.setWidth(64);
    myRect.setHeight(30);

    do
    {
        listItems.clear();
        myRect.setX(_x);
        _x += 64;
        listItems = this->items(myRect, Qt::IntersectsItemShape, Qt::AscendingOrder);

        if (_x > 500)
        {
            _x = 0;
        }

//        qDebug() << "bot_2";
    } while(listItems.size() != 0);

    _x += 32;
    m_tankBot4->setPos(_x, 0);
    m_tankBot4->setData(0, OBJ_NAME_BOT_4);
    m_tankBot4->setObjectName(OBJ_NAME_BOT_4);
    m_tankBot4->setZValue(0.5);
    this->addItem(m_tankBot4);
}

void BattleCityMap::slotAddBot_1()
{
    ++m_tankBot1->numberDeaths;
    QList <QGraphicsItem *> listItems;
    int _x = 0;
    QRectF myRect;
    myRect.setX(_x);
    myRect.setY(0);
    myRect.setWidth(128);
    myRect.setHeight(30);

    do
    {
        listItems.clear();
        myRect.setX(_x);
        _x += 128;
        listItems = this->items(myRect, Qt::IntersectsItemShape, Qt::AscendingOrder);

        if (_x > 500)
        {
            _x = 0;
        }
//        qDebug() << "bot_1";

    } while(listItems.size() != 0);

    _x -= 32;
    m_tankBot1->setPos(_x, 0);
    m_tankBot1->setData(0, OBJ_NAME_BOT_1);
    m_tankBot1->setObjectName(OBJ_NAME_BOT_1);
    m_tankBot1->setZValue(0.5);
    this->addItem(m_tankBot1);
}

void BattleCityMap::slotGameOver() {


    //
    QString playerName1 = m_TankForPlay1->getName();
    QString playerName2 = "Player2";

    int fontSize = 12;                                             // Размер шрифта для надписей(Player, PTS, etc);
    quint8 cntKilledTanksEasyPl1   = 0;
    quint8 cntKilledTanksSpeedPl1  = 0;
    quint8 cntKilledTanksMiddlePl1 = 0;
    quint8 cntKilledTanksHardPl1   = 0;

    quint8 cntKilledTanksEasyPl2   = 0;
    quint8 cntKilledTanksSpeedPl2  = 0;
    quint8 cntKilledTanksMiddlePl2 = 0;
    quint8 cntKilledTanksHardPl2   = 0;
    quint16 bonuses = 0;

    bonuses += m_TankForPlay1->getBonus();
    if (m_TankForPlay1->getKilledTanks().count() > 0) {
        QMap<QString,quint8> kt1 = m_TankForPlay1->getKilledTanks();
        if (kt1.contains("easy"))
            cntKilledTanksEasyPl1 = kt1["easy"];

        if (kt1.contains("easy"))
            cntKilledTanksSpeedPl1 = kt1["speed"];

        if (kt1.contains("easy"))
            cntKilledTanksMiddlePl1 = kt1["middle"];

        if (kt1.contains("easy"))
            cntKilledTanksHardPl1 = kt1["hard"];
    }

    if (m_iGameMode == 2) {
        playerName2 = m_TankForPlay2->getName();
        bonuses += m_TankForPlay2->getBonus();
        if (m_TankForPlay2->getKilledTanks().count() > 0) {
            QMap<QString,quint8> kt2 = m_TankForPlay2->getKilledTanks();
            if (kt2.contains("easy"))
                cntKilledTanksEasyPl2 = kt2["easy"];

            if (kt2.contains("easy"))
                cntKilledTanksSpeedPl2 = kt2["speed"];

            if (kt2.contains("easy"))
                cntKilledTanksMiddlePl2 = kt2["middle"];

            if (kt2.contains("easy"))
                cntKilledTanksHardPl2 = kt2["hard"];
        }
    }

    quint16 scoreForKilledEasyPl1   = cntKilledTanksEasyPl1   * 100;
    quint16 scoreForKilledSpeedPl1  = cntKilledTanksSpeedPl1  * 200;
    quint16 scoreForKilledMiddlePl1 = cntKilledTanksMiddlePl1 * 300;
    quint16 scoreForKilledHardPl1   = cntKilledTanksHardPl1   * 400;

    quint16 scoreForKilledEasyPl2   = cntKilledTanksEasyPl2   * 100;
    quint16 scoreForKilledSpeedPl2  = cntKilledTanksSpeedPl2  * 200;
    quint16 scoreForKilledMiddlePl2 = cntKilledTanksMiddlePl2 * 300;
    quint16 scoreForKilledHardPl2   = cntKilledTanksHardPl2   * 400;

    quint16 splayer1 = scoreForKilledEasyPl1 + scoreForKilledSpeedPl1 + scoreForKilledMiddlePl1 + scoreForKilledHardPl1;
    quint16 splayer2 = scoreForKilledEasyPl2 + scoreForKilledSpeedPl2 + scoreForKilledMiddlePl2 + scoreForKilledHardPl2;
    quint16 splayers = splayer1 + splayer2;    // suma player 1;

    this->m_bIsGameOver = true;
    foreach (QGraphicsItem *it, this->items()) {
        it->hide();
    }
//    this->clear();

    this->m_timerMoveTankPL1->deleteLater();
    this->m_timerMoveTankPL2->deleteLater();

    this->m_timerMoveBot1->deleteLater();
    this->m_timerMoveBot2->deleteLater();
    this->m_timerMoveBot3->deleteLater();
    this->m_timerMoveBot4->deleteLater();

    this->m_timerMoveBots->deleteLater();
//    timerForShowBonus->deleteLater();
//    m_timerForShowExplosionBonus->deleteLater();
    m_timerShowProtectionBase->deleteLater();
//    m_timerRemoveExplosionBonus->deleteLater();
//    timerRemoveProtectionBase->deleteLater();
//    timerRemoveStar->deleteLater();
//    m_timerRemoveTimerBonus->deleteLater();
//    bot->deleteLater();
//    bot_2->deleteLater();
//    bot_3->deleteLater();
//    bot_4->deleteLater();

//    timerAuditBots->deleteLater();

    QString hiscoreValue = QString::number(bonuses + splayers);

    QGraphicsWidget *lblScore = this->addWidget(new QLabel("<center>HI-SCORE " + hiscoreValue + "</center>"));

    QPalette palette = lblScore->palette();                        // Палитра которую применим к надписи
    palette.setColor(QPalette::Background, QColor(Qt::black));      // Задний фон палитри - черного цвета, а
    palette.setColor(QPalette::Foreground, QColor(Qt::red));        // передний красного
    lblScore->setPalette(palette);                                  // Установка палитры
    lblScore->setFont(QFont("M10_BATTLE CITIES", fontSize));        // Установка шрифта фона и размера

    QString stageValue = QString::number(1);
    QGraphicsWidget *lblStage = this->addWidget(new QLabel("<center>STAGE " + stageValue + "</center>"));
    palette = lblStage->palette();
    palette.setColor(QPalette::Background, QColor(Qt::black));
    palette.setColor(QPalette::Foreground, QColor(Qt::white));
    lblStage->setPalette(palette);
    lblStage->setFont(lblScore->font());

    // Player 1
    QGraphicsWidget *lblPlayer1 = this->addWidget(new QLabel(playerName1));
    lblPlayer1->setPalette(lblScore->palette());
    lblPlayer1->setFont(lblScore->font());

    QGraphicsWidget *lblPlayer2 = this->addWidget(new QLabel("<p align='left'>"+playerName2+"</p>"));
    lblPlayer2->setPalette(lblScore->palette());
    lblPlayer2->setFont(lblScore->font());

    // Количество очков Player1 за убитые танки easy
    QGraphicsWidget *lblCntScore = this->addWidget(new QLabel(QString::number(splayer1)));
    lblCntScore->setPalette(lblScore->palette());
    lblCntScore->setFont(lblScore->font());

    QGraphicsWidget *lblCntScore2 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(splayer2) +"</p>"));
    lblCntScore2->setPalette(lblScore->palette());
    lblCntScore2->setFont(lblScore->font());

    // PTS 1
    // Для Player 1
    QGraphicsWidget *lblPTS1 = this->addWidget(new QLabel("<p align='left'>PTS</p>"));
    lblPTS1->setPalette(palette);
    lblPTS1->setFont(lblScore->font());

    // Количество очков за убитые танки "простой танк":
    QGraphicsWidget *iPTS1 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(scoreForKilledEasyPl1) +"</p>"));
    iPTS1->setPalette(palette);
    iPTS1->setFont(lblScore->font());
    iPTS1->setMaximumWidth(75);

    // Количество убитых танков типа "простой танк":
    QGraphicsWidget *iCntKilledTanks1 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(cntKilledTanksEasyPl1 + cntKilledTanksSpeedPl1 + cntKilledTanksMiddlePl1 + cntKilledTanksHardPl1) +"</p>"));
    iCntKilledTanks1->setPalette(palette);
    iCntKilledTanks1->setFont(lblScore->font());

    // Player 2
    QGraphicsWidget *lblPTS12 = this->addWidget(new QLabel("<p align='right'>PTS</p>"));
    lblPTS12->setPalette(palette);
    lblPTS12->setFont(lblScore->font());

    QGraphicsWidget *iPTS12 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(scoreForKilledEasyPl2) +"</p>"));
    iPTS12->setPalette(palette);
    iPTS12->setFont(lblScore->font());
    iPTS12->setMaximumWidth(75);

    QGraphicsWidget *iCntKilledTanks12 = this->addWidget(new QLabel(QString::number(cntKilledTanksEasyPl2 + cntKilledTanksSpeedPl2 + cntKilledTanksMiddlePl2 + cntKilledTanksHardPl2)));
    iCntKilledTanks12->setPalette(palette);
    iCntKilledTanks12->setFont(lblScore->font());

    // PTS 2
    QGraphicsWidget *iPTS2 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(scoreForKilledSpeedPl1) +"</p>"));
    iPTS2->setPalette(palette);
    iPTS2->setFont(lblScore->font());
    iPTS2->setMaximumWidth(75);

    QGraphicsWidget *lblPTS2 = this->addWidget(new QLabel("<p align='left'>PTS</p>"));
    lblPTS2->setPalette(palette);
    lblPTS2->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks2 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(cntKilledTanksSpeedPl1) +"</p>"));
    iCntKilledTanks2->setPalette(palette);
    iCntKilledTanks2->setFont(lblScore->font());
    // Player 2
    QGraphicsWidget *iPTS22 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(scoreForKilledSpeedPl2) +"</p>"));
    iPTS22->setPalette(palette);
    iPTS22->setFont(lblScore->font());
    iPTS22->setMaximumWidth(75);

    QGraphicsWidget *lblPTS22 = this->addWidget(new QLabel("<p align='right'>PTS</p>"));
    lblPTS22->setPalette(palette);
    lblPTS22->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks22 = this->addWidget(new QLabel(QString::number(cntKilledTanksSpeedPl2)));
    iCntKilledTanks22->setPalette(palette);
    iCntKilledTanks22->setFont(lblScore->font());

    // PTS 3
    // Player 1
    QGraphicsWidget *iPTS3 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(scoreForKilledMiddlePl1) +"</p>"));
    iPTS3->setPalette(palette);
    iPTS3->setFont(lblScore->font());
    iPTS3->setMaximumWidth(75);

    QGraphicsWidget *lblPTS3 = this->addWidget(new QLabel("<p align='left'>PTS</p>"));
    lblPTS3->setPalette(palette);
    lblPTS3->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks3 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(cntKilledTanksMiddlePl1) +"</p>"));
    iCntKilledTanks3->setPalette(palette);
    iCntKilledTanks3->setFont(lblScore->font());

    // Player 2
    QGraphicsWidget *iPTS32 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(scoreForKilledMiddlePl2) +"</p>"));
    iPTS32->setPalette(palette);
    iPTS32->setFont(lblScore->font());
    iPTS32->setMaximumWidth(75);

    QGraphicsWidget *lblPTS32 = this->addWidget(new QLabel("<p align='right'>PTS</p>"));
    lblPTS32->setPalette(palette);
    lblPTS32->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks32 = this->addWidget(new QLabel(QString::number(cntKilledTanksMiddlePl2)));
    iCntKilledTanks32->setPalette(palette);
    iCntKilledTanks32->setFont(lblScore->font());

    // PTS 4
    // Player 1
    QGraphicsWidget *iPTS4 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(scoreForKilledHardPl1) +"</p>"));
    iPTS4->setPalette(palette);
    iPTS4->setFont(lblScore->font());
    iPTS4->setMaximumWidth(75);
    QGraphicsWidget *lblPTS4 = this->addWidget(new QLabel("<p align='left'>PTS</p>"));
    lblPTS4->setPalette(palette);
    lblPTS4->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks4 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(cntKilledTanksHardPl1) +"</p>"));
    iCntKilledTanks4->setPalette(palette);
    iCntKilledTanks4->setFont(lblScore->font());

    // Player 2
    QGraphicsWidget *iPTS42 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(scoreForKilledHardPl2) +"</p>"));
    iPTS42->setPalette(palette);
    iPTS42->setFont(lblScore->font());
    iPTS42->setMaximumWidth(75);
    // PTS 4
    QGraphicsWidget *lblPTS42 = this->addWidget(new QLabel("<p align='right'>PTS</p>"));
    lblPTS42->setPalette(palette);
    lblPTS42->setFont(lblScore->font());

    QGraphicsWidget *iCntKilledTanks42 = this->addWidget(new QLabel(QString::number(cntKilledTanksHardPl2)));
    iCntKilledTanks42->setPalette(palette);
    iCntKilledTanks42->setFont(lblScore->font());

    QGraphicsWidget *lblTotal = this->addWidget(new QLabel("<p align='right'>Total</p>"));
    lblTotal->setPalette(palette);
    lblTotal->setFont(lblScore->font());

    QGraphicsWidget *lblTotalVal1 = this->addWidget(new QLabel("<p align='right'>"+ QString::number(cntKilledTanksEasyPl1 + cntKilledTanksSpeedPl1 + cntKilledTanksMiddlePl1 + cntKilledTanksHardPl1) +"</p>"));
    lblTotalVal1->setPalette(palette);
    lblTotalVal1->setFont(lblScore->font());

    QGraphicsWidget *lblTotalVal2 = this->addWidget(new QLabel("<p align='left'>"+ QString::number(cntKilledTanksEasyPl2 + cntKilledTanksSpeedPl2 + cntKilledTanksMiddlePl2 + cntKilledTanksHardPl2) +"</p>"));
    lblTotalVal2->setPalette(palette);
    lblTotalVal2->setFont(lblScore->font());

    // Виды танков
    QLabel *lbl = new QLabel();
    lbl->setPixmap(QPixmap(":/imgsForGameOver/easy.png"));
    QGraphicsWidget *imgTankEasy = this->addWidget(lbl);       // "простой танк"

    lbl = new QLabel();
    lbl->setPixmap(QPixmap(":/imgsForGameOver/speed.png"));
    QGraphicsWidget *imgTankSpeed = this->addWidget(lbl);      // "быстрый танк"

    lbl = new QLabel();
    lbl->setPixmap(QPixmap(":/imgsForGameOver/middle.png"));
    QGraphicsWidget *imgTankMiddle = this->addWidget(lbl);     // "средний танк"

    lbl = new QLabel();
    lbl->setPixmap(QPixmap(":/imgsForGameOver/hard.png"));
    QGraphicsWidget *imgTankHard = this->addWidget(lbl);       // "тяжелый танк"

    lbl = new QLabel();
    lbl->setPixmap(QPixmap(":/imgsForGameOver/whiteLine.png"));
    QGraphicsWidget *imgWhiteLine = this->addWidget(lbl);       // Белая линия которая
                                                                // отображается в конце таблицы

    QGraphicsGridLayout *layoutGrid = new QGraphicsGridLayout();
    for (int i = 0; i < 5; i++) {
        layoutGrid->setRowSpacing(i, 15);                       // Отступ между строкой
    }
    layoutGrid->setRowSpacing(5, 5);

    layoutGrid->setContentsMargins(0, 0, 10, 0);
    // Player 1
    layoutGrid->addItem(lblPlayer1 , 0, 0, 1, 2);               // Добавляем объект lblPlayer1 в 0 строку, 0 столбец,
                                                                // и соеденяем столбец 0 и 1 в единое целое
    layoutGrid->addItem(lblCntScore, 1, 1);

    layoutGrid->addItem(iPTS1  , 2, 0);
    layoutGrid->addItem(lblPTS1, 2, 1);
    layoutGrid->addItem(iCntKilledTanks1, 2, 2);

    layoutGrid->addItem(iPTS2  , 3, 0);
    layoutGrid->addItem(lblPTS2, 3, 1);
    layoutGrid->addItem(iCntKilledTanks2, 3, 2);

    layoutGrid->addItem(iPTS3  , 4, 0);
    layoutGrid->addItem(lblPTS3, 4, 1);
    layoutGrid->addItem(iCntKilledTanks3, 4, 2);

    layoutGrid->addItem(iPTS4  , 5, 0);
    layoutGrid->addItem(lblPTS4, 5, 1);
    layoutGrid->addItem(iCntKilledTanks4, 5, 2);

    // imgs
    layoutGrid->addItem(imgTankEasy  , 2, 3);
    layoutGrid->addItem(imgTankMiddle, 3, 3);
    layoutGrid->addItem(imgTankSpeed , 4, 3);
    layoutGrid->addItem(imgTankHard  , 5, 3);

    // Player 2
    layoutGrid->addItem(lblPlayer2,   0, 5, 1, 2);
    layoutGrid->addItem(lblCntScore2, 1, 6);
    layoutGrid->addItem(iCntKilledTanks12, 2, 4);

    layoutGrid->addItem(iPTS12,   2, 5);
    layoutGrid->addItem(lblPTS12, 2, 6);
    layoutGrid->addItem(iCntKilledTanks22, 3, 4);

    layoutGrid->addItem(iPTS22,   3, 5);
    layoutGrid->addItem(lblPTS22, 3, 6);
    layoutGrid->addItem(iCntKilledTanks32, 4, 4);

    layoutGrid->addItem(iPTS32,   4, 5);
    layoutGrid->addItem(lblPTS32, 4, 6);
    layoutGrid->addItem(iCntKilledTanks42, 5, 4);

    layoutGrid->addItem(iPTS42,   5, 5);
    layoutGrid->addItem(lblPTS42, 5, 6);

    layoutGrid->addItem(imgWhiteLine, 6, 2, 1, 2);  // Белая линия

    layoutGrid->addItem(lblTotal, 7, 0, 1, 2);      // Надпись "Тотал"
    layoutGrid->addItem(lblTotalVal1, 7, 2);        // Общее количество убитых танков для Игрока 1
    layoutGrid->addItem(lblTotalVal2, 7, 4);        // Общее количество убитых танков для Игрока 2

    layoutGrid->setColumnFixedWidth(0, 70);         // Установка ширины равной 70 пикс для колонки с номером 0
    layoutGrid->setColumnFixedWidth(1, 30);
    layoutGrid->setColumnFixedWidth(2, 40);
    layoutGrid->setColumnFixedWidth(3, 40);
    layoutGrid->setColumnFixedWidth(4, 30);
    layoutGrid->setColumnFixedWidth(5, 60);
    layoutGrid->setColumnFixedWidth(6, 60);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);
    layout->setSpacing(15);                         // Установка отступов между объектами
                                                    // в вертикальном компоновщике
    layout->setMinimumWidth(400);                   // Минимальная ширина компоновщика
    layout->setContentsMargins(40, 100, 0, 0);      // Отступы от границы
    layout->addItem(lblScore);                      // Добавление обьекта
    layout->addItem(lblStage);
    layout->addItem(layoutGrid);

    QGraphicsWidget *form = new QGraphicsWidget();
    form->setLayout(layout);
    this->addItem(form);

    this->setBackgroundBrush(QBrush("Black"));     // Закраска сцены в чёрный цвет
}
