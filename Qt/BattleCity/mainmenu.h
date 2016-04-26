#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QObject>
#include <QLineEdit>
#include <QListWidget>
#include <QComboBox>

#include <QGraphicsGridLayout>

#include "battlecityview.h"
#include "udpclient.h"

class QLabel;
class QCheckBox;

class mainMenu: public QGraphicsView {
    Q_OBJECT
public:
    mainMenu();
    void ShowGame(int regimeGame);  // создание обьекта карты
    void Lan();                     // игра по сети
    ~mainMenu();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsScene      *scene;
    QGraphicsWidget     *lblImgGraph;
    QGraphicsGridLayout *m_gridLayout;

    QGraphicsWidget *form;
    QLabel          *lblImgTank;
    QLineEdit       *m_pLineEditPl1;
    QLineEdit       *m_pLineEditPl2;
    QCheckBox       *m_pChkBoxSound;

    BattleCityView  *view;                  // карта игры
    QGraphicsView   *chooiseClientOrServer; // меню выбора создание клиента или сервера
    QGraphicsView   *viewServer;            // создание сервера
    QGraphicsView   *viewClient;            // создание клиента
    QGraphicsView   *viewConnectToServer;
    QGraphicsView   *viewRunServer;
    QGraphicsView   *viewRunTwoPlayer;

    QPushButton   *btnChooiseServer;
    QPushButton   *btnChooiseClient;

    QPushButton   *btnServer;
    QPushButton   *btnClient;

    QPushButton   *btnStartGame;
    QPushButton   *btnUpdate;
    QPushButton   *btnConnect;

    QLineEdit *editNameServer;
    QLineEdit *editIpServer;
    QLineEdit *editIpClient;

    QLineEdit *editIpClient2;

    QListWidget *list;                      // отображение именни сервера

    UdpClient *client;
    UdpClient *server;

    QComboBox *cmbFriendGame;
    bool _friend;

    int id_elementOfMenu;

    void playOnePlayer();
    void playTwoPlayers();
    void showAbout();
    void showOptions();
    void showMainMenu();
    void setPaletteAndFont(QGraphicsWidget *gw,     // Установка цвета и шрифта
                           bool useFont = true);    // для объекта QGraphicsWidget

    void clearGridLayout(QGraphicsGridLayout *gl);  // Очистка от объектов GridLayout

public slots:
    void slotCreateServer();                        // создание сервера
    void slotCreateClient();                        // создание клиента

    void slotRunServer();                           // запуск сервера
    void slotConnectToServer();                     // соединение с сервером

    void slotSendMessageConnectToServer();          // отправка первого сообщения клиентом
    void slotReadNameServer(QString nameServer);    // чтение именни сервера

    void slotStartGameServer();                     // старт игры как сервер
    void slotStartGameClient();                     // старт игры как клиент
    void slotRunGameFriend();
    void slotRunGameBattle();
};

#endif // MAINMENU_H
