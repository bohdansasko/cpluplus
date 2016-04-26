#include "tankforplayer.h"
#include "constants.h"
#include "bonus.h"
#include <ctime>
#include <iostream>
#include <QTime>

#include <QKeyEvent>
#include <QDebug>
#include <QException>

TankForPlayer::TankForPlayer(QString name, const QList<QString> fileNames, int numberOfPlayer):
    Tank(fileNames)
{
    this->m_uiNumberLife = 3;
    this->m_uiCntBonus   = 0;
    this->m_sName        = name;

    switch (numberOfPlayer) {
        case 1: {
            m_mapActions.insert( Qt::Key_Up   , Key_Up   );
            m_mapActions.insert( Qt::Key_Down , Key_Down );
            m_mapActions.insert( Qt::Key_Right, Key_Right);
            m_mapActions.insert( Qt::Key_Left , Key_Left );
            m_mapActions.insert( Qt::Key_Space, Key_Space);

            iArrowUp    = Qt::Key_Up;
            iArrowDown  = Qt::Key_Down;
            iArrowRight = Qt::Key_Right;
            iArrowLeft  = Qt::Key_Left;
            iKeySpace   = Qt::Key_Space;

            break;
        }
        case 2: {
            m_mapActions.insert( Qt::Key_W, Key_Up   );
            m_mapActions.insert( Qt::Key_S, Key_Down );
            m_mapActions.insert( Qt::Key_D, Key_Right);
            m_mapActions.insert( Qt::Key_A, Key_Left );
            m_mapActions.insert( Qt::Key_B, Key_Space);

            iArrowUp    = Qt::Key_W;
            iArrowDown  = Qt::Key_S;
            iArrowRight = Qt::Key_D;
            iArrowLeft  = Qt::Key_A;
            iKeySpace   = Qt::Key_B;

            break;
        }
    }

    QObject::connect(this, SIGNAL(signalAddKilledBotToStatistic(QString)), this, SLOT(slotAddDeadBotToStatistic(QString)));
}

TankForPlayer::~TankForPlayer() {}

/* virtual */void TankForPlayer::keyPressEvent(QKeyEvent *event) {
    int key = event->key();

    if (event->isAutoRepeat() || !m_mapActions.contains(key)) {
        event->ignore();
        return;
    }

    if (key != iKeySpace)
        m_listActiveKey.push_back(key);

    if (key == iArrowUp)
        rotateUp( true );
    else if (key == iArrowDown)
        rotateDown( true );
    else if (key == iArrowRight)
        rotateRight( true );
    else if (key == iArrowLeft)
        rotateLeft( true );
    else if (key == iKeySpace)
        emit signalShot(OBJ_NAME_PLAYER_1);

    event->accept();
}

/* virtual */void TankForPlayer::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();

    if (event->isAutoRepeat() || !m_mapActions.contains(key)) {
        event->ignore();
        return;
    }

    if (key == iArrowUp) {
        rotateUp( false );
        m_listActiveKey.removeOne(iArrowUp);
    }
    else if (key == iArrowDown) {
        rotateDown( false );
        m_listActiveKey.removeOne(iArrowDown);
    }
    else if (key == iArrowRight) {
        rotateRight( false );
        m_listActiveKey.removeOne(iArrowRight);
    }
    else if (key == iArrowLeft) {
        rotateLeft( false );
        m_listActiveKey.removeOne(iArrowLeft);
    }

    event->accept();
}

void TankForPlayer::slotTankShot(QString senderName) {
    if (this->m_bShot == false)
        return;

    try {
        Bullet *bullet = this->shot();
        bullet->nameObjectSender = senderName;
        bullet->setData(0, OBJ_NAME_BULLET);
        this->m_bShot = false;

        QObject::connect( bullet, SIGNAL( destroyed(QObject*) ), this, SLOT( slotAllowShot(QObject*)));
        QObject::connect( bullet, SIGNAL( signalGameOver() ), this, SLOT( slotGameOver()  ));
        QObject::connect( bullet, SIGNAL( signalSendTypeOfKilledBot(QString)), this, SLOT( slotReceiveTypeOfKilledBot(QString)));
        scene()->addItem(bullet);

    } catch (QException *e) {
//        qDebug() << e->what();
    }
}

void TankForPlayer::slotReceiveTypeOfKilledBot(const QString name) {
    signalAddKilledBotToStatistic(name);
}

void TankForPlayer::moveTank() {
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
//   qDebug() << "dd = " << CLOCKS_PER_SEC * 0.2;
//   QTime timeL = 2 * CLOCKS_PER_SEC;
   m_uiSpeed = 2;                                             // Скорость передвижения
   QGraphicsItem *obstacleWithIce = itemCollidesWith(this);
   if (obstacleWithIce->data(0) == OBJ_NAME_ICE)              // Если танк на льду, делаем эфект
       this->m_uiSpeed = 2;                                   // "скользания", за счёт увелечения скорости

   qDebug() << "timeN - timeL = " << m_uiSpeed;
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
        (x+30)  > WINDOW_WIDTH  ||    // Проверка на выход за границы карты.
        (y+30)  > WINDOW_HEIGHT ||
        (x < 0) || (y < 0)
       )
   {                                   // Если было спроба переместиться за границу
       this->moveBy(-np.x(), -np.y()); // смещаем назад, делая эфект стены.
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
           this->moveBy(-np.x(), -np.y());     // смещаем танк назад на np.x() та np.y().
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
           return;
       }
       else if (it->data(0)  == OBJ_NAME_RED_WALL) {
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

       if (it->data(0) == OBJ_NAME_STAR) {
           CBonus *b = dynamic_cast<CBonus *>(it);
           emit b->slotShowScore();
           this->addBonusScore(300);
           ++this->m_uiPower;
       }
       else if (it->data(0) == OBJ_NAME_BASE_BONUS) {
           CBonus *b = dynamic_cast<CBonus *>(it);
           this->addBonusScore(400);
           emit b->slotShowScore();
       }
       else if (it->data(0) == OBJ_NAME_TIME_BONUS) {
           CBonus *b = dynamic_cast<CBonus *>(it);
           this->addBonusScore(200);
           emit b->slotShowScore();
       }
       else if (it->data(0) == OBJ_NAME_EXPLOSION_BONUS) {
           CBonus *b = dynamic_cast<CBonus *>(it);
           this->addBonusScore(100);
           emit b->slotShowScore();
       }
   }
   scene()->update();
}

int TankForPlayer::getNumberLife() {
    return m_uiNumberLife;
}

void TankForPlayer::setNumberLife() {
    --m_uiNumberLife;
}

void TankForPlayer::setInBeginPosition() {
    if (this->_friendOrBattle) {
        this->setPos(CNT_BEGIN_X_ONE_PLAYER_BATTLE, CNT_BEGIN_Y_ONE_PLAYER_BATTLE);
    }
    else {
        this->setPos(CNT_BEGIN_X_ONE_PLAYER, CNT_BEGIN_Y_ONE_PLAYER);
    }
}
// Збільшити кількість набраних бонусних очків на "score".
// Бонуси: піднята лопатка, граната і т.д.
void TankForPlayer::addBonusScore(quint16 score) {
    this->m_uiCntBonus += score;
}

// Підрахунок вбитих ботів гравцем. Коли бот знищується, він висилає тип танка.
void TankForPlayer::slotAddDeadBotToStatistic(const QString typeOfBot) {
    if (m_mapKilledTanks.contains(typeOfBot))                  // Якщо присутній такий тип,
        ++m_mapKilledTanks[typeOfBot];                         // збільшується кількість вбитих ботів даного типу на 1.
    else                                                       // Якщо немає такого типу,
        m_mapKilledTanks[typeOfBot] = 1;                       // тоді створюється
}
