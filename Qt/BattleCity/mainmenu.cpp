#include "mainmenu.h"

#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QListWidget>
#include "udpclient.h"
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>
#include <QFontComboBox>
#include <QCheckBox>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QComboBox>
#include <QGraphicsGridLayout>
#include <QMediaPlayer>

mainMenu::mainMenu(): id_elementOfMenu(1) {
    scene         = new QGraphicsScene();
    m_gridLayout  = new QGraphicsGridLayout();
    form          = new QGraphicsWidget();
    lblImgTank = NULL;

    _friend = false;

    m_gridLayout->setSpacing(10);                                       // Отступ между объектами в layout
    form->setLayout(m_gridLayout);

    QMediaPlayer *mpl = new QMediaPlayer(this);
    mpl->setMedia(QUrl("qrc:/sounds/gamestart.ogg"));
    mpl->play();

//    player->setVolume(50);

    scene->addItem(form);
    scene->setBackgroundBrush(QBrush(QPixmap(":/img/background.png"))); // Фон сцены
    scene->setSceneRect(0, 0, 512, 512);

    showMainMenu();

    this->setFixedSize(512, 512);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setScene(scene);
    this->move(400,0);
    this->show();

    btnServer = new QPushButton("create server");
    btnClient = new QPushButton("create client");

    btnConnect   = new QPushButton("connect");
    btnStartGame = new QPushButton("start");
    btnUpdate    = new QPushButton("update");

    btnChooiseServer = new QPushButton("server");
    btnChooiseClient = new QPushButton("client");

    QObject::connect(btnChooiseServer, SIGNAL(clicked(bool)), this, SLOT(slotCreateServer()));
    QObject::connect(btnChooiseClient, SIGNAL(clicked(bool)), this, SLOT(slotCreateClient()));

    QObject::connect(btnServer   , SIGNAL(clicked(bool)), this, SLOT(slotRunServer()));
    QObject::connect(btnClient   , SIGNAL(clicked(bool)), this, SLOT(slotConnectToServer()));

    QObject::connect(btnUpdate   , SIGNAL(clicked(bool)), this, SLOT(slotSendMessageConnectToServer()));   // послать сообщения серверу

    QObject::connect(btnConnect  , SIGNAL(clicked(bool)), this, SLOT(slotStartGameClient()));
    QObject::connect(btnStartGame, SIGNAL(clicked(bool)), this, SLOT(slotStartGameServer()));
}

mainMenu::~mainMenu() {}

void mainMenu::showMainMenu() {
    clearGridLayout(m_gridLayout);
    id_elementOfMenu = 1;

    if (lblImgTank == NULL) {
        lblImgTank = new QLabel();
        lblImgTank->setPixmap(QPixmap(":/img/tank.png"));
    }
    // Пункты главного меню
    QGraphicsWidget *lblOnePlayer   = scene->addWidget(new QLabel("1 Player"));
    QGraphicsWidget *lblTwoPlayers  = scene->addWidget(new QLabel("2 Players"));
    QGraphicsWidget *lblNetwork     = scene->addWidget(new QLabel("LAN"));
    QGraphicsWidget *lblOptions     = scene->addWidget(new QLabel("Options"));
    QGraphicsWidget *lblAbout       = scene->addWidget(new QLabel("Authors"));
    QGraphicsWidget *lblExit        = scene->addWidget(new QLabel("Exit"));

    lblImgGraph = scene->addWidget(lblImgTank);         // Добавленния виджета на сцену
    lblImgGraph->setVisible(true);
    setPaletteAndFont(lblImgGraph, false);              // Установка чёрного фона картинки

    // 1 Players
    setPaletteAndFont(lblOnePlayer);
    // 2 Players
    setPaletteAndFont(lblTwoPlayers);
    // Network
    setPaletteAndFont(lblNetwork);
    // Options
    setPaletteAndFont(lblOptions);
    // About
    setPaletteAndFont(lblAbout);
    // Exit
    setPaletteAndFont(lblExit);

    m_gridLayout->addItem(lblOnePlayer , 0, 0);         // Добавление объектов в layout
    m_gridLayout->addItem(lblTwoPlayers, 1, 0);
    m_gridLayout->addItem(lblNetwork   , 2, 0);
    m_gridLayout->addItem(lblOptions   , 3, 0);
    m_gridLayout->addItem(lblAbout     , 4, 0);
    m_gridLayout->addItem(lblExit      , 5, 0);

    m_gridLayout->setContentsMargins(180, 270, 0, 0);   // Установка отступов
    lblImgGraph->setPos(130, 262);                      // Установка позиции желтого танка
}

void mainMenu::showOptions() {
    delete lblImgTank;
    lblImgTank = NULL;

    id_elementOfMenu = 41;
    clearGridLayout(m_gridLayout);

    m_pLineEditPl1 = new QLineEdit("Player1");
    m_pLineEditPl2 = new QLineEdit("Player2");

    m_pChkBoxSound = new QCheckBox();
    m_pChkBoxSound->setChecked(true);

    QGraphicsWidget *lblPlayer1 = scene->addWidget(new QLabel("Tank1-"));
    QGraphicsWidget *lblPlayer2 = scene->addWidget(new QLabel("Tank2-"));
    QGraphicsWidget *lblNamePlayer1 = scene->addWidget(m_pLineEditPl1);
    QGraphicsWidget *lblNamePlayer2 = scene->addWidget(m_pLineEditPl2);

    QGraphicsWidget *lblSound    = scene->addWidget(new QLabel("Sound-"));
    QGraphicsWidget *chkBoxSound = scene->addWidget(m_pChkBoxSound);

    lblNamePlayer1->setMinimumWidth(130);
    lblNamePlayer2->setMinimumWidth(130);

    lblPlayer1->setMaximumHeight(25);
    lblPlayer2->setMaximumHeight(25);

    lblSound->setMaximumHeight(25);

    chkBoxSound->setMinimumWidth(25);
    chkBoxSound->setMinimumHeight(25);

    const int fontSize = 12;
    lblNamePlayer1->setFont(QFont("M10_BATTLE CITIES", fontSize));
    lblNamePlayer2->setFont(QFont("M10_BATTLE CITIES", fontSize));

    setPaletteAndFont(lblPlayer1);
    setPaletteAndFont(lblPlayer2);
    setPaletteAndFont(lblSound);
    setPaletteAndFont(chkBoxSound, false);

    m_gridLayout->addItem(lblPlayer1    , 0, 0);
    m_gridLayout->addItem(lblNamePlayer1, 0, 1);
    m_gridLayout->addItem(lblPlayer2    , 1, 0);
    m_gridLayout->addItem(lblNamePlayer2, 1, 1);
    m_gridLayout->addItem(lblSound      , 2, 0);
    m_gridLayout->addItem(chkBoxSound   , 2, 1);
}

void mainMenu::showAbout() {
    delete lblImgTank;
    lblImgTank = NULL;

    id_elementOfMenu = 51;
    clearGridLayout(m_gridLayout);

    QGraphicsWidget *lblNickNameG = scene->addWidget(new QLabel("OwL"));
    QGraphicsWidget *lblAuthorG   = scene->addWidget(new QLabel("- Gavrysyuk O."));

    QGraphicsWidget *lblNickNameD = scene->addWidget(new QLabel("NN"));
    QGraphicsWidget *lblAuthorD   = scene->addWidget(new QLabel("- Dzhus S."));

    QGraphicsWidget *lblNickNameS = scene->addWidget(new QLabel("TQOS"));
    QGraphicsWidget *lblAuthorS   = scene->addWidget(new QLabel("- Sasko B."));

    lblNickNameG->setMaximumHeight(25);
    lblNickNameD->setMaximumHeight(25);
    lblNickNameS->setMaximumHeight(25);

    lblAuthorG->setMaximumHeight(25);
    lblAuthorD->setMaximumHeight(25);
    lblAuthorS->setMaximumHeight(25);

    //
    setPaletteAndFont(lblNickNameG);
    setPaletteAndFont(lblNickNameD);
    setPaletteAndFont(lblNickNameS);

    setPaletteAndFont(lblAuthorG);
    setPaletteAndFont(lblAuthorD);
    setPaletteAndFont(lblAuthorS);

    //
    m_gridLayout->addItem(lblNickNameG, 0, 0);
    m_gridLayout->addItem(lblAuthorG  , 0, 1);

    m_gridLayout->addItem(lblNickNameD, 1, 0);
    m_gridLayout->addItem(lblAuthorD  , 1, 1);

    m_gridLayout->addItem(lblNickNameS, 2, 0);
    m_gridLayout->addItem(lblAuthorS  , 2, 1);
}

void mainMenu::keyPressEvent(QKeyEvent *event) {
    if (id_elementOfMenu == 41) {
        QGraphicsView::keyPressEvent(event);
    }

    switch (event->key()) {
        case Qt::Key_Up: {
                if (id_elementOfMenu == 1 || id_elementOfMenu == 41)
                    return;
                --id_elementOfMenu;
                lblImgGraph->setY(lblImgGraph->y() - 26);
            break;
        }

        case Qt::Key_Down: {
            if (id_elementOfMenu == 6 || id_elementOfMenu == 41)
                return;
            ++id_elementOfMenu;
            lblImgGraph->setY(lblImgGraph->y() + 26);
            break;
        }

        case Qt::Key_Space: {
                switch (id_elementOfMenu) {
                    case 1:
                            playOnePlayer();    // 1 Player
                        break;
                    case 2:
                            playTwoPlayers();   // 2 Player
                        break;
                    case 3:
                            Lan();              // Multiply
                        break;
                    case 4:
                            showOptions();      // Options
                        break;
                    case 5:
                           showAbout();         // About
                        break;
                    case 6:
                           this->close();       // Exit
                        break;
                }
            break;
        }
        case Qt::Key_Escape:
                showMainMenu();
            break;
    }
}

void mainMenu::clearGridLayout(QGraphicsGridLayout *gl) {
    if (gl->count() == 0)
        return;

    int countRows = gl->rowCount();
    int countColumns = gl->columnCount();
    for (int i = 0; i < countRows; ++i) {
        for (int j = 0; j < countColumns; ++j) {
            QGraphicsLayoutItem* it = m_gridLayout->itemAt(i, j);
            m_gridLayout->removeItem(it);
            delete it;
            it = NULL;
        }
    }
}


void mainMenu::setPaletteAndFont(QGraphicsWidget *gw, bool useFont) {
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(Qt::black));
    palette.setColor(QPalette::Foreground, QColor(Qt::white));

    int id = QFontDatabase::addApplicationFont(":/fonts/ufonts.com_m10-battle-cities.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    gw->setPalette(palette);
    if (useFont)
        gw->setFont(QFont(family, 12));
}

//
void mainMenu::Lan() {
    chooiseClientOrServer = new QGraphicsView;
    QVBoxLayout   *vLayout = new QVBoxLayout;

    vLayout->addWidget(btnChooiseServer);
    vLayout->addWidget(btnChooiseClient);
    chooiseClientOrServer->setLayout(vLayout);

    this->close();
    chooiseClientOrServer->setFixedSize(150, 100);
    chooiseClientOrServer->setWindowTitle("chooise");
    chooiseClientOrServer->show();
}

void mainMenu::playOnePlayer() {
    // Передать количества игроков
    ShowGame(1);
}

void mainMenu::ShowGame(int regimeGame)
{
    UdpClient *udp = new UdpClient("", "", "");

    view = new BattleCityView(regimeGame, true, udp);
    this->close();
    view->move(400,0);
    view->show();
}

void mainMenu::playTwoPlayers()
{    // Передать количества игроков
    viewRunTwoPlayer = new QGraphicsView;

    QPushButton* btnFriend  = new QPushButton("friend");
    QPushButton* btnBattle  = new QPushButton("battle");
    QVBoxLayout* headLayout = new QVBoxLayout;

    headLayout->addWidget(btnFriend);
    headLayout->addWidget(btnBattle);

    viewRunTwoPlayer->setLayout(headLayout);

    viewRunTwoPlayer->setFixedSize(200, 100);
    viewRunTwoPlayer->show();

    QObject::connect( btnFriend, SIGNAL( clicked(bool) ), this, SLOT( slotRunGameFriend() ));
    QObject::connect( btnBattle, SIGNAL( clicked(bool) ), this, SLOT( slotRunGameBattle() ));
    // ShowGame(2);
}

void mainMenu::slotCreateServer()
{
    viewServer = new QGraphicsView;
    QLabel *lblNameServer = new QLabel("name server");
    QLabel *lblIpServer   = new QLabel("ip server");
    cmbFriendGame = new QComboBox;
    cmbFriendGame->addItem("friend");
    cmbFriendGame->addItem("battle");

    editNameServer = new QLineEdit;

    QRegExp rex("[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}");
    QValidator *validator = new QRegExpValidator(rex, this);
    editIpServer   = new QLineEdit;
    editIpServer->setValidator(validator);

    QVBoxLayout *headLayout        = new QVBoxLayout;
    QHBoxLayout *hLayoutNameServer = new QHBoxLayout;
    QHBoxLayout *hLayoutIpServer   = new QHBoxLayout;

    hLayoutNameServer->addWidget(lblNameServer);
    hLayoutNameServer->addWidget(editNameServer);

    hLayoutIpServer->addWidget(lblIpServer);
    hLayoutIpServer->addSpacing(25);
    hLayoutIpServer->addWidget(editIpServer);

    headLayout->addLayout(hLayoutNameServer);
    headLayout->addLayout(hLayoutIpServer);
    headLayout->addWidget(cmbFriendGame);
    headLayout->addWidget(btnServer);

    viewServer->setWindowTitle("creating server");
    viewServer->setLayout(headLayout);

    chooiseClientOrServer->close();
    viewServer->show();
}

void mainMenu::slotCreateClient()
{
    viewClient = new QGraphicsView;
    QLabel *lblIpServer = new QLabel("ip server");
    QLabel *lblIpClient = new QLabel("ip client");

    QRegExp rex("[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}");
    QValidator *validator = new QRegExpValidator(rex, this);

    editIpServer = new QLineEdit;
    editIpServer->setValidator(validator);

    editIpClient = new QLineEdit;
    editIpClient->setValidator(validator);

    QVBoxLayout *headLayout = new QVBoxLayout;
    QHBoxLayout *hLayoutIpServer = new QHBoxLayout;
    QHBoxLayout *hLayoutIpClient   = new QHBoxLayout;

    hLayoutIpServer->addWidget(lblIpServer);
    hLayoutIpServer->addSpacing(20);
    hLayoutIpServer->addWidget(editIpServer);

    hLayoutIpClient->addWidget(lblIpClient);
    hLayoutIpClient->addSpacing(25);
    hLayoutIpClient->addWidget(editIpClient);

    headLayout->addLayout(hLayoutIpServer);
    headLayout->addLayout(hLayoutIpClient);
    headLayout->addWidget(btnClient);

    viewClient->setWindowTitle("creating client");
    viewClient->setLayout(headLayout);

    chooiseClientOrServer->close();
    viewClient->show();
}

void mainMenu::slotRunServer()
{
    if (editIpServer->text() == "" || editNameServer->text() == "")
    {
        QMessageBox::critical(0, "error", "not correct value");
        return;
    }

    if (cmbFriendGame->currentText() == "friend")
    {
        _friend = true;
    }

    QString ipServer;
    QString nameServer;

    ipServer = editIpServer->text();
    nameServer = editNameServer->text();

    server = new UdpClient(nameServer, ipServer, "");
    server->server = true;

    list   = new QListWidget;

    viewRunServer = new QGraphicsView;
    QHBoxLayout   *headLayout    = new QHBoxLayout;

    list->addItem(nameServer);
    list->setFixedSize(100, 100);
    headLayout->addWidget(list);
    headLayout->addWidget(btnStartGame);

    viewRunServer->setLayout(headLayout);
    viewRunServer->setFixedSize(250, 120);
    viewRunServer->setWindowTitle("server");

    viewServer->close();
    viewRunServer->show();
}

void mainMenu::slotConnectToServer()
{
    if (editIpServer->text() == "" || editIpClient->text() == "")
    {
        QMessageBox::critical(0, "error", "not correct value");
        return;
    }

    QString strIpServer;
    QString strIpClient;

    strIpServer = editIpServer->text();
    strIpClient = editIpClient->text();

    client = new UdpClient("", strIpClient, strIpServer);
    client->server = false;

    list = new QListWidget;

    viewConnectToServer = new QGraphicsView;
    QHBoxLayout   *headLayout          = new QHBoxLayout;
    QVBoxLayout   *vLayout             = new QVBoxLayout;

    list->setFixedSize(100, 100);
    headLayout->addWidget(list);

    vLayout->addWidget(btnUpdate);
    vLayout->addWidget(btnConnect);

    headLayout->addLayout(vLayout);

    viewConnectToServer->setLayout(headLayout);
    viewConnectToServer->setFixedSize(250, 120);
    viewConnectToServer->setWindowTitle("client");

    viewClient->close();
    viewConnectToServer->show();

    QObject::connect(client, SIGNAL(signalConnectExecute(QString)), this, SLOT(slotReadNameServer(QString)));
}

void mainMenu::slotSendMessageConnectToServer()
{
    client->SendIpClient();
}

void mainMenu::slotReadNameServer(QString nameServer)
{
    list->addItem(nameServer);
}

void mainMenu::slotStartGameClient()
{
    if (list->count() == 0)
    {
        QMessageBox::critical(0, "error", "server not found");
        return;
    }

    view = new BattleCityView(4, _friend, client);
    viewConnectToServer->close();
    view->move(400,0);

    view->show();
}

void mainMenu::slotRunGameBattle()
{
    UdpClient *udp = new UdpClient("", "", "");

    view = new BattleCityView(2, false, udp);
    this->close();
    view->move(400,0);
    viewRunTwoPlayer->close();
    view->show();
}

void mainMenu::slotRunGameFriend()
{
    ShowGame(2);
    viewRunTwoPlayer->close();
}

void mainMenu::slotStartGameServer()
{
    if (server->_strIpForSend == "")
    {
        QMessageBox::critical(this, "error", "not found client \n"
                                             "please connect and again");
        return;
    }

    view = new BattleCityView(3, _friend, server);
    viewRunServer->close();
    view->move(400,0);

    if (!_friend)
    {
        view->rotate(180);
    }

    view->show();
}
