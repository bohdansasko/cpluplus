#include "udpclient.h"
#include "constants.h"

UdpClient::UdpClient(UdpClient*& client)
{
    this->_socket        = client->_socket;
    this->_strIpForBind  = client->_strIpForBind;
    this->_strIpForSend  = client->_strIpForSend;
    this->_strNameServer = client->_strNameServer;
    this->server         = client->server;
}

UdpClient::UdpClient(QString nameServer, QString strIpForBind, QString strIpForSend)
{
    if (strIpForSend == "") // создание сервера
    {
        _strNameServer = nameServer;
        _strIpForBind  = strIpForBind;
        server = true;
    }
    else                    // создание клиента
    {
        _strIpForSend = strIpForSend;
        _strNameServer = "";
        _strIpForBind = strIpForBind;
        server = false;
    }

    _socket = new QUdpSocket(this);
    _socket->bind(QHostAddress(_strIpForBind), CNT_PORT_FOR_CONNECT);       // привязка к данному ip i порту

    QObject::connect(_socket, SIGNAL( readyRead()), this, SLOT( slotReadMessageClient() ));
}

void UdpClient::slotReadMessageClient()
{
    QByteArray baDatagram;

    do
    {
        baDatagram.resize(_socket->pendingDatagramSize());
        _socket->readDatagram(baDatagram.data(), baDatagram.size());
    }
    while(_socket->hasPendingDatagrams());

    int  x;
    int  y;
    int  rotate;
    bool shot;

    QDataStream in(&baDatagram, QIODevice::ReadOnly);

    in.setVersion(QDataStream::Qt_5_5);

    if (_strNameServer == "") // при первом чтении сообщения клиентом
    {
        in >>_strNameServer;

        emit signalConnectExecute(_strNameServer); // послать сигнал про успешное подсоединения
        return;
    }

    if (server) // первое чтения сообщения сервером
    {
        in >> _strIpForSend;
        server = false;
        SendMessageForConnection(); // отсылка именни сервера клиенту
    }
    else
    {
        in >> x;
        in >> y;
        in >> rotate;
        in >> shot;

        ReadInformationOpponent(x, y,rotate, shot);
    }
}

void UdpClient::SendMessage(int x, int y, int rotate, bool shot)
{
    QByteArray baDatagram;

    QDataStream out(&baDatagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << x << y << rotate << shot;

    _socket->writeDatagram(baDatagram, QHostAddress(_strIpForSend), CNT_PORT_FOR_CONNECT);
}

void UdpClient::SendMessageForConnection()
{
    QByteArray baDatagram;

    QDataStream out(&baDatagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << _strNameServer;

    _socket->writeDatagram(baDatagram, QHostAddress(_strIpForSend), CNT_PORT_FOR_CONNECT);
}

void UdpClient::SendIpClient()
{
    QByteArray baDatagram;

    QDataStream out(&baDatagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << _strIpForBind;

    _socket->writeDatagram(baDatagram, QHostAddress(_strIpForSend), CNT_PORT_FOR_CONNECT);
}

void UdpClient::ReadInformationOpponent(int x, int y, int rotate, bool shot)
{
    emit signalReadInformationOpponent(x, y, rotate, shot);
}
