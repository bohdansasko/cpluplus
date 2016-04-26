#include <QTextEdit>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <QGraphicsGridLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include "battlecityview.h"

BattleCityView::BattleCityView(int regimeGame, bool _friend, UdpClient *client): QGraphicsView() {

    map = new BattleCityMap(regimeGame,_friend, client);
    this->setScene(map);
    map->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ShowWalls(OBJ_NAME_WATER     , OBJ_TYPE_WATER     , ":/walls/1.jpg");
    ShowWalls(OBJ_NAME_ICE       , OBJ_TYPE_ICE       , ":/walls/2.jpg");
    ShowWalls(OBJ_NAME_RED_WALL  , OBJ_TYPE_RED_WALL  , ":/walls/3.jpg");
    ShowWalls(OBJ_NAME_GRASS     , OBJ_TYPE_GRASS     , ":/walls/4.png");
    ShowWalls(OBJ_NAME_WHITE_WALL, OBJ_TYPE_WHITE_WALL, ":/walls/5.jpg");
    ShowWalls(OBJ_NAME_BASE      , OBJ_TYPE_BASE      , ":/Explosion/base.png");
}

BattleCityView::~BattleCityView() {
    map->~BattleCityMap();
}

void BattleCityView::ShowWalls(const QString &strTypeWall,
                               int numberTypeWall,
                               const QString &pathToImage)
{
    if ( map->m_deleteBase && numberTypeWall == OBJ_TYPE_BASE ) {
        return;
    }

    for (int i = 0; i < CNT_ROWS_MAP; i++)
        for (int j = 0; j < CNT_COLS_MAP; j++)
            if (map->m_Map[i][j] == numberTypeWall) {
                QGraphicsItem *p_graphItem = new RedWall(pathToImage);

                p_graphItem->setPos(SIZE_WALL*j, SIZE_WALL*i);
                p_graphItem->setData(0, strTypeWall);

                if (strTypeWall == OBJ_NAME_GRASS)
                    p_graphItem->setZValue(1.0);

//                if (
//                    (   i >= 28  )  && ( i < 32  ) &&   // строки
//                    ( ( j == 14  )  || ( j == 19 ) )    // столбцы
//                   ) {
//                    if (!map->m_deleteBase)
//                    {
////                        map->m_listObjectAtBase.push_back(p_graphItem);
//                    }
//                    else
//                    {
//                        continue;
//                    }
//                } // dddeeeleeette
//                if (
//                     ( j >= 14 ) && ( j < 19 ) &&      // столбцы
//                     ( i == 28 )                       // строки
//                   )
//                {
//                    if (!map->m_deleteBase)
//                    {
////                        map->m_listObjectAtBase.push_back(p_graphItem);
//                    }
//                    else
//                    {
//                        continue;
//                    }
//                }
//                if (OBJ_TYPE_BASE == numberTypeWall)
//                    qDebug() << "x = " << i * 16 << "; y = " << j * 16;
                map->addItem(p_graphItem);
            }
}
