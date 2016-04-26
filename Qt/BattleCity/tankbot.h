#ifndef TANKBOT_H
#define TANKBOT_H

#include "tank.h"
#include "constants.h"
#include <vector>       // vector<T>
#include "algorithmli.h"

using std::vector;

class TankBot: public Tank {
    Q_OBJECT
public:
    explicit TankBot(const QList<QString> fileNames);
    ~TankBot();

private:
    struct QPoint2D {
        int x;
        int y;

        QPoint2D() {
            x = y = 0;
        }

        QPoint2D(int x, int y) {
            this->x = x;
            this->y = y;
        }
    };

    enum MODE_ATACK {FREE, KILL_PLAYER, KILL_FLAG};
    MODE_ATACK MODE_OF_ATACK;

    vector<QPoint2D> path;
    vector<QPoint2D> shortPath;
    QVector<point> _previousStep;
    QVector<point> vectorFoundWay;
    algorithmLI    *algorithmSearchWay;
    QTimer *timerFoundNewWay;
    QTimer* timerSetAtackRegime;
    point _previousPoint;
    QString m_sType;
    bool searchWay;                         // был ли поиск пути
    bool changeRotate;
    int  map[CNT_ROWS_MAP][CNT_COLS_MAP];
    int  mapSearchWay[CNT_ROWS_MAP][CNT_COLS_MAP];
    int  indexWay;                          // в какой точке сейчас находимся

    void outMap();
    void setModeOfAtack(MODE_ATACK M_A);

public:
    int x_end;
    int y_end;
    int _xPlayer;
    int _yPlayer;

    bool addTank;       // розрешение добавлени бота на карту
    int numberDeaths;   // количевство смертей

    void setMap(int map[CNT_ROWS_MAP][CNT_COLS_MAP]);

    QString getType() const;        // Отримання типу танка
    void setType(const QString t);  // Встановлення типу танка

protected:
    virtual void moveTank();

signals:
    void signalOneSearchWay(int x_begin, int y_begin, int x_end, int y_end);

public slots:
    void slotTankShot(QString senderName);
    void slotForStartSearchPath();
    void slotSearchPath(int x_begin, int y_begin, int x_end, int y_end);
    void Atack(int xPlayer, int yPlayer);   // поиск пути для игроков
    void Atack();                           // поиск пути для ботов

    void slotSearchNewWayAfterCollision(bool useRotate);
};

#endif // TANKBOT_H
