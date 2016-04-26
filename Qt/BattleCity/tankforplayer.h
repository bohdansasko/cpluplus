#ifndef TANKFORPLAYER_H
#define TANKFORPLAYER_H

#include "tank.h"
#include <QMap>
#include "constants.h"
#include "redwall.h"

class TankForPlayer: public Tank {
    Q_OBJECT
public:
    explicit TankForPlayer(QString name, const QList<QString> fileNames, int numberOfPlayer);
    ~TankForPlayer();

    int  getNumberLife();
    void setNumberLife();
    void setInBeginPosition();

    QMap<QString,quint8> getKilledTanks() const { return m_mapKilledTanks; }
    QString getName() { return m_sName; }
    quint16 getBonus() { return m_uiCntBonus; }
    void addBonusScore(quint16 score);

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

protected:
    virtual void moveTank();

private:
    QMap<QString, quint8> m_mapKilledTanks; // Убитые танки
    quint16               m_uiCntBonus;
    QString               m_sName;
    quint16               m_uiNumberLife;

public slots:
    void slotTankShot(QString senderName);
    void slotAddDeadBotToStatistic(const QString typeOfBot);
    void slotReceiveTypeOfKilledBot(const QString name);

signals:
    void signalAddKilledBotToStatistic(QString);    // Сигнал для добавления
                                                    // +1 в таблицу статистики танка, который убил бота
                                                    // Параметр служит для расспознавания типа убитого танка.
                                                    // easy, speed, middle, hard. Если убили танка easy,
                                                    // тогда в таблице убитых танков +1. Потом, количество
                                                    // убитых танков переводится в баллы.
};

#endif // TANKFORPLAYER_H


