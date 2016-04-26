#include "tankbot.h"
#include <QKeyEvent>
#include "constants.h"
#include <iostream>
#include <iomanip>
#include <QDebug>
#include <time.h>
#include <QTime>

using namespace std;

TankBot::TankBot(const QList<QString> fileNames): Tank(fileNames) {
    MODE_OF_ATACK = FREE;
//    MODE_OF_ATACK = KILL_FLAG;
    setRotate(270);
    searchWay   = false;
    indexWay    = CNT_NOT_FOUND_WAY;
    addTank     = false;
    changeRotate = false;
    numberDeaths = 0;
    _previousPoint.x = 0;
    _previousPoint.y = 0;
    timerFoundNewWay = new QTimer(this);
    timerFoundNewWay->setObjectName("timer");

    //timerFoundNewWay->start(CNT_SECOND_SEARCH_NEW_WAY);
    QObject::connect( timerFoundNewWay, SIGNAL(timeout())                          , this, SLOT(slotForStartSearchPath()            ));
    QObject::connect( this            , SIGNAL(signalOneSearchWay(int,int,int,int)), this, SLOT(slotSearchPath(int,int,int,int)     ));
    QObject::connect( this            , SIGNAL(signalSearchNewWay(bool))           , this, SLOT(slotSearchNewWayAfterCollision(bool)));
}

void TankBot::setModeOfAtack(TankBot::MODE_ATACK M_A) {
    MODE_OF_ATACK = M_A;
}

void TankBot::setType(const QString t) {
    m_sType = t;
}

QString TankBot::getType() const {
    return m_sType;
}

void TankBot::slotForStartSearchPath()
{
    if (this->objectName() == OBJ_NAME_PLAYER_1)
    {
        emit signalOneSearchWay(this->y()/SIZE_WALL, this->x()/SIZE_WALL, _yPlayer/SIZE_WALL, _xPlayer/SIZE_WALL);
    }
    else
    {
        emit signalSearchNewWay(false);
    }
}

void TankBot::slotSearchPath(int x_begin, int y_begin, int x_end, int y_end) {
    searchWay = true; // состоялся поиск пути
    indexWay = CNT_NOT_FOUND_WAY;
    algorithmSearchWay  = new algorithmLI(x_begin, y_begin, x_end, y_end);
}

// Поиск пути для игроков
void TankBot::Atack(int xPlayer, int yPlayer) {

   _xPlayer = xPlayer;
   _yPlayer = yPlayer;

    if (indexWay <= 1) // если достигли финиша
    {
//        qDebug() << "finish";
        searchWay = false;
        indexWay = CNT_NOT_FOUND_WAY;
    }
    if (searchWay)                         // был найден путь
    {
        if (indexWay == CNT_NOT_FOUND_WAY) // и бот находится вконце пути
        {
            if (
                (algorithmSearchWay->vectorFoundWay.size() == 0) ||
                (algorithmSearchWay->vectorFoundWay.size() == 1)
               )
            {
                emit signalSearchNewWay(false);
              //  emit signalOneSearchWay(this->y()/SIZE_WALL, this->x()/SIZE_WALL, _yPlayer/SIZE_WALL, _xPlayer/SIZE_WALL);
                return;
            }

            vectorFoundWay.resize(algorithmSearchWay->vectorFoundWay.size());
            copy(algorithmSearchWay->vectorFoundWay.begin(), algorithmSearchWay->vectorFoundWay.end(),
                 vectorFoundWay.begin()); // копирование пути в вектор этого класса с класса нахождения пути

            indexWay = vectorFoundWay.size() - 2;           // получаем предпоследний елемент пути
//            qDebug() << "index :" << indexWay;
            x_end = vectorFoundWay[indexWay].y * SIZE_WALL; // получаем x и y предпоследнего
            y_end = vectorFoundWay[indexWay].x * SIZE_WALL; // елемента пути

            if (x_end == this->x())      // когда текущий x и x - следующего елемента пути ровны
            {
                if (y_end < this->y())   // если текущий y больше y - следующего шага пути
                {
                    this->m_uiRotate = 0;   // едем вверх
                }
                else
                {
                    this->m_uiRotate = 180; // едем вниз
                }
            }
            else
            {
                if (x_end > this->x())   // если тaекущий x менше x следующего елемента пути
                {
                    this->m_uiRotate = 90;  // едем вправо
                }
                else
                {
                    this->m_uiRotate = 270; // едем влево
                }
            }

        }

        if (indexWay == 0)
        {
            if (_xPlayer % 2 != 0)
            {
                ++_xPlayer;
            }
            if (_yPlayer % 2 != 0)
            {
                ++_yPlayer;
            }

            emit signalOneSearchWay(this->y()/SIZE_WALL, this->x()/SIZE_WALL, _yPlayer/SIZE_WALL, _xPlayer/SIZE_WALL); // поиск пути
            return;
        }

        if (this->x() == x_end && this->y() == y_end) // когда текущие x і y ровны елементу пути
        {
            --indexWay;                                   // переходим к следующему елементу пути
            x_end = vectorFoundWay[indexWay].y * SIZE_WALL;
            y_end = vectorFoundWay[indexWay].x * SIZE_WALL;

            if (x_end == this->x())
            {
                if (y_end < this->y())
                {
                    this->m_uiRotate = 0;
                }
                else
                {
                    this->m_uiRotate = 180;
                }
            }
            else if (y_end == this->y())
            {
                if (x_end > this->x())
                {
                    this->m_uiRotate = 90;
                }
                else
                {
                    this->m_uiRotate = 270;
                }
            }
       }
    }
    else
    {
        if (_xPlayer % 2 != 0)
        {
            ++_xPlayer;
        }
        if (_yPlayer % 2 != 0)
        {
            ++_yPlayer;
        }

        emit signalOneSearchWay(this->y()/SIZE_WALL, this->x()/SIZE_WALL, _yPlayer/SIZE_WALL, _xPlayer/SIZE_WALL); // поиск пути
        return;
    }

//    qDebug() << this->objectName() << " " << vectorFoundWay[indexWay].y*SIZE_WALL << " v " << vectorFoundWay[indexWay].x*SIZE_WALL;
//    qDebug() << "index:" << indexWay;
//    qDebug() << this->objectName() << " " << vectorFoundWay[2].y*SIZE_WALL << " v " << vectorFoundWay[2].x*SIZE_WALL;

    m_listActiveKey.clear();
    switch (MODE_OF_ATACK) {
        case FREE: {
            switch (this->m_uiRotate) {
            case 0:
                    m_listActiveKey.push_back(Qt::Key_Up);
                break;
            case 90:
                    m_listActiveKey.push_back(Qt::Key_Right);
                break;
            case 180:
                    m_listActiveKey.push_back(Qt::Key_Down);
                break;
            case 270:
                    m_listActiveKey.push_back(Qt::Key_Left);
                break;
        }
        break;
        }
        case KILL_PLAYER: {
            break;
        }
        case KILL_FLAG: {
            break;
        }
    }
    emit slotMoveTank();
    emit slotTankShot(this->objectName());
}

void TankBot::slotTankShot(QString senderName) {
    if (this->m_bShot == false)
        return;

    try
    {
        Bullet *bullet = this->shot();
        bullet->nameObjectSender = senderName;
        bullet->setData(0, OBJ_NAME_BULLET);
        this->m_bShot = false;

        connect( bullet, SIGNAL( destroyed(QObject*)), this, SLOT( slotAllowShot(QObject*) ));
        connect( bullet, SIGNAL( signalGameOver()), this, SLOT( slotGameOver()  ));
        scene()->addItem(bullet);
    } catch (exception *e) {
//        qDebug() << e->what();
    }
}

/* virtual */void TankBot::moveTank() {
    if (this->m_listActiveKey.isEmpty()) {                    // Если нету нажатых клавиш, тогда
        return;                                         // выход из процедуры
    }

    int x = this->x();
    int y = this->y();

    int lastKey = this->m_listActiveKey.last();               // Получение кода последней нажатой клавиши

    if (this->_friendOrBattle) {
       if (lastKey == this->iArrowDown) {
           lastKey = this->iArrowUp;
       }
       else if (lastKey == this->iArrowUp) {
           lastKey = this->iArrowDown;
       }
       else if (lastKey == iArrowLeft) {
           lastKey = this->iArrowRight;
       }
       else {
           lastKey = this->iArrowLeft;
       }
    }

    QPointF np;
    np.setX(0);
    np.setY(0);

    m_uiSpeed = 2;                                             // Скорость передвижения
    QGraphicsItem *obstacleWithIce = itemCollidesWith(this);
    if (obstacleWithIce->data(0) == OBJ_NAME_ICE)           // Если танк на льду, делаем эфект
        this->m_uiSpeed = 4;                                   // "скользания", за счёт увелечения скорости

//    qDebug() << "lastKey = " << lastKey;
    if (lastKey == this->iArrowUp) {                            // В зависимости от нажатой клавиши,
        this->setY(y - this->m_uiSpeed);                           // смещаем танк в необходиму сторону,
        this->m_uiCurrentFrame = (this->m_uiCurrentFrame != 4) ? 4 : 5; // загружаем фрейм(картинку танка),
        this->m_uiRotate = 0;                                      // устанавливаем направление танка и
        np.setY(-this->m_uiSpeed);                                 // на сколько он должен переместиться и по какой оси.
    }
    else if (lastKey == this->iArrowDown) {
        this->setY(y + this->m_uiSpeed);
        this->m_uiCurrentFrame = (this->m_uiCurrentFrame != 0) ? 0 : 1;
        this->m_uiRotate = 180;
        np.setY(this->m_uiSpeed);
    }
    else if (lastKey == this->iArrowRight) {
        this->setX(x + this->m_uiSpeed);
        this->m_uiCurrentFrame = (this->m_uiCurrentFrame != 6) ? 6 : 7;
        this->m_uiRotate = 90;
        np.setX(this->m_uiSpeed);
    }
    else if (lastKey == this->iArrowLeft) {
        this->setX(x - this->m_uiSpeed);
        this->m_uiCurrentFrame = (this->m_uiCurrentFrame != 2) ? 2 : 3;
        this->m_uiRotate = 270;
        np.setX(-this->m_uiSpeed);
    }

    x = this->x();
    y = this->y();

    if (
         (x+33)  > WINDOW_WIDTH   ||    // Проверка на выход за границы карты.
         (y+33)  >= WINDOW_HEIGHT ||
         (x < 0) || (y < 0)
        )
    {                                   // Если было спроба переместиться за границу
        this->moveBy(-np.x(), -np.y()); // смещаем назад, делая эфект стены,
        emit signalSearchNewWay(true);  // и сразу ищим другой путь.

    }

    QList<QGraphicsItem *> obstacle = scene()->collidingItems(this); // С какими обьектами столкнулся танк.
    foreach (QGraphicsItem *it, obstacle) {
        if (it == this)                         // Если с самим собой,
            continue;                           // пропускаем.

        if (
            it->data(0)  == OBJ_NAME_BOT_1 ||   // Проверка столкновения танка(игрока или бота) с ботами.
            it->data(0)  == OBJ_NAME_BOT_2 ||
            it->data(0)  == OBJ_NAME_BOT_3 ||
            it->data(0)  == OBJ_NAME_BOT_4
           )
        {                                       // Если столкнулся, тогда
            this->moveBy(-np.x(), -np.y());     // смещаем танк назад на np.x() та np.y()
            emit signalSearchNewWay(true);      // и ищим другой путь.
            return;
        }

        if (
            it->data(0) == OBJ_NAME_WATER      || // Если танк столкнулся с водой,
            it->data(0) == OBJ_NAME_WHITE_WALL || // белой стеной,
            it->data(0) == OBJ_NAME_PLAYER_1   || // игроком1 или
            it->data(0) == OBJ_NAME_PLAYER_2      // 2
           )
        {
            this->moveBy(-np.x(), -np.y());       // смещаем и ищим другой путь.
            emit signalSearchNewWay(true);
            return;
        }
        else if (it->data(0) == OBJ_NAME_RED_WALL) {
            this->moveBy(-np.x(), -np.y());
        }

        QString senderName = sender()->objectName();
        if (
             senderName == OBJ_NAME_BOT_1 ||
             senderName == OBJ_NAME_BOT_2 ||
             senderName == OBJ_NAME_BOT_3 ||
             senderName == OBJ_NAME_BOT_4
           )
        {
            emit signalShot(this->objectName());
        }
    }
    scene()->update();
}

// Поиск пути для ботов
void TankBot::Atack() {
    if (indexWay <= 3 )// если достигли финиша
    {
//        qDebug() << "finish";
        searchWay = false;
        indexWay = CNT_NOT_FOUND_WAY;
    }
    if (searchWay)                         // был найден путь
    {
        if (indexWay == CNT_NOT_FOUND_WAY) // и бот находится вконце пути
        {
            if (
                (algorithmSearchWay->vectorFoundWay.size() == 0) ||
                (algorithmSearchWay->vectorFoundWay.size() == 1)
               )
            {
                emit signalSearchNewWay(false);
                return;
            }

            vectorFoundWay.resize(algorithmSearchWay->vectorFoundWay.size());
            copy(algorithmSearchWay->vectorFoundWay.begin(), algorithmSearchWay->vectorFoundWay.end(),
                 vectorFoundWay.begin()); // копирование пути в вектор этого класса с класса нахождения пути

            indexWay = vectorFoundWay.size() - 2;           // получаем предпоследний елемент пути
            x_end = vectorFoundWay[indexWay].y * SIZE_WALL; // получаем x и y предпоследнего
            y_end = vectorFoundWay[indexWay].x * SIZE_WALL; // елемента пути

            if (x_end == this->x())      // когда текущий x и x - следующего елемента пути ровны
            {
                if (y_end < this->y())   // если текущий y больше y - следующего шага пути
                {
                    this->m_uiRotate = 0;   // едем вверх
                }
                else
                {
                    this->m_uiRotate = 180; // едем вниз
                }
            }
            else
            {
                if (x_end > this->x())   // если тaекущий x менше x следующего елемента пути
                {
                    this->m_uiRotate = 90;  // едем вправо
                }
                else
                {
                    this->m_uiRotate = 270; // едем влево
                }
            }
        }

        if (indexWay == 0)
        {
            emit signalSearchNewWay(false);
            return;
        }

        if (this->x() == x_end && this->y() == y_end) // когда текущие x і y ровны елементу пути
        {
            --indexWay;                                   // переходим к следующему елементу пути
            x_end = vectorFoundWay[indexWay].y * SIZE_WALL;
            y_end = vectorFoundWay[indexWay].x * SIZE_WALL;

            if (x_end == this->x())
            {
                if (y_end < this->y())
                {
                    this->m_uiRotate = 0;
                }
                else
                {
                    this->m_uiRotate = 180;
                }
            }
            else if (y_end == this->y())
            {
                if (x_end > this->x())
                {
                    this->m_uiRotate = 90;
                }
                else
                {
                    this->m_uiRotate = 270;
                }
            }
        }
    }
    else
    {
        emit signalSearchNewWay(true);
        return;
    }

//    qDebug() << this->objectName() << " " << vectorFoundWay[indexWay].y*SIZE_WALL << " v " << vectorFoundWay[indexWay].x*SIZE_WALL;
//    qDebug() << "index:" << indexWay;
//    qDebug() << this->objectName() << " " << vectorFoundWay[2].y*SIZE_WALL << " v " << vectorFoundWay[2].x*SIZE_WALL;

    m_listActiveKey.clear();
    switch (MODE_OF_ATACK) {
    case FREE: {
        switch (this->m_uiRotate) {
            case 0:
                m_listActiveKey.push_back(Qt::Key_Up);
                break;
            case 90:
                m_listActiveKey.push_back(Qt::Key_Right);
                break;
            case 180:
                m_listActiveKey.push_back(Qt::Key_Down);
                break;
            case 270:
                m_listActiveKey.push_back(Qt::Key_Left);
                break;
        }
        break;
    }
    case KILL_PLAYER: {
        break;
    }
    case KILL_FLAG: {
        break;
    }
    }

    emit slotMoveTank();
    emit slotTankShot(this->objectName());
}

void TankBot::slotSearchNewWayAfterCollision(bool useRotate)
{
    int xPlayer = 0;
    int yPlayer = 0;

    if (useRotate)
    {
        if (this->y() <= 250)
        {
            switch (this->m_uiRotate)
            {
                case 0:
                {/*qDebug() << "0";*/
                    if (this->x() >= 250)
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = rand() % 128 + 64;
                        yPlayer = this->y();
                    }
                    else
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = rand() % 440 + 380;
                        yPlayer = this->y();
                    }
                    break;
                }
                case 90:
                {/*qDebug() << "90";*/
                    if (this->y() >= 250)
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = this->x();
                        yPlayer = rand() % 128 + 64;
                    }
                    else
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = this->x();
                        yPlayer = rand() % 440 + 380;
                    }
                    break;
                }
                case 180:
                {/*qDebug() << "180";*/
                    if (this->x() >= 250)
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = rand() % 128 + 64;
                        yPlayer = this->y();
                    }
                    else
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = rand() % 440 + 380;
                        yPlayer = this->y();
                    }
                    break;
                }
                case 270:
                {/*qDebug() << "270";*/
                    if (this->y() >= 250)
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = this->x();
                        yPlayer = rand() % 128 + 64;
                    }
                    else
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = this->x();
                        yPlayer = rand() % 440 + 380;
                    }
                    break;
                }
                default:
                {
                    qsrand(QTime::currentTime().msec());
                    xPlayer = rand() % 450 + 100;
                    yPlayer = rand() % 450 + 100;
                    break;
                }
            }
         }
        else
        {
            switch (this->m_uiRotate)
            {
                case 0:
                {/*qDebug() << "90";*/
                    if (this->y() >= 250)
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = this->x();
                        yPlayer = rand() % 128 + 64;
                    }
                    else
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = this->x();
                        yPlayer = rand() % 440 + 380;
                    }
                    break;
                }
                    case 90:
                    {/*qDebug() << "0";*/
                        if (this->x() >= 250)
                        {
                            qsrand(QTime::currentTime().msec());
                            xPlayer = rand() % 128 + 64;
                            yPlayer = this->y();
                        }
                        else
                        {
                            qsrand(QTime::currentTime().msec());
                            xPlayer = rand() % 440 + 380;
                            yPlayer = this->y();
                        }
                        break;
                    }


                    case 180:
                    {/*qDebug() << "270";*/
                        if (this->y() >= 250)
                        {
                            qsrand(QTime::currentTime().msec());
                            xPlayer = this->x();
                            yPlayer = rand() % 128 + 64;
                        }
                        else
                        {
                            qsrand(QTime::currentTime().msec());
                            xPlayer = this->x();
                            yPlayer = rand() % 440 + 380;
                        }
                        break;
                    }
                case 270:
                {/*qDebug() << "180";*/
                    if (this->x() >= 250)
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = rand() % 128 + 64;
                        yPlayer = this->y();
                    }
                    else
                    {
                        qsrand(QTime::currentTime().msec());
                        xPlayer = rand() % 440 + 380;
                        yPlayer = this->y();
                    }
                    break;
                }
            }
        }
    }
    else
    {
        qsrand(QTime::currentTime().msec());
        xPlayer = rand() % 450 + 100;
        yPlayer = rand() % 450 + 100;
    }

    _xPlayer = xPlayer;
    _yPlayer = yPlayer;

    if (_xPlayer % 2 != 0)
    {
        ++_xPlayer;
    }
    if (_yPlayer % 2 != 0)
    {
        ++_yPlayer;
    }

//    qDebug() << this->objectName();
//    qDebug() << "player: " << this->x() << " " << this->y();
//    qDebug() << "position: " << _xPlayer << " " << yPlayer;

    emit signalOneSearchWay(this->y()/SIZE_WALL, this->x()/SIZE_WALL, _yPlayer/SIZE_WALL, _xPlayer/SIZE_WALL);
    changeRotate = true;
}

void TankBot::outMap(/*const int map[CNT_ROWS_MAP][CNT_COLS_MAP]*/) {
//    for (int i = 0; i < CNT_ROWS_MAP; ++i) {
//        for (int j = 0; j < CNT_COLS_MAP; ++j) {
//            qDebug() << map[i][j];
//        }
//        qDebug() << endl;
//    }
}

TankBot::~TankBot()
{
    deleteLater();
}
