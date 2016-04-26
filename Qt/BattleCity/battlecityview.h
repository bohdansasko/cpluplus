#ifndef BATTLECITYVIEW_H
#define BATTLECITYVIEW_H

#include <QGraphicsView>
#include <QObject>

#include "battlecitymap.h"
#include "constants.h"

class BattleCityView : public QGraphicsView
{
    Q_OBJECT
public:
    BattleCityView(int regimeGame, bool _friend, UdpClient* client);
    ~BattleCityView();

    void ShowWalls(const QString &strTypeWall, int numberTypeWall, const QString &pathToImage);

    int _map[WINDOW_WIDTH][WINDOW_HEIGHT];

private:
    BattleCityMap* map;

public slots:
};

#endif // BATTLECITYVIEW_H
