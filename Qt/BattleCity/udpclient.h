#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QDataStream>
#include <QByteArray>

class UdpClient : public QObject
{
    Q_OBJECT
public:
    QString _strIpForSend;  // ip противника
    QString _strNameServer; // имя сервера
    QString _strIpForBind;  // свой ip

    QUdpSocket  *_socket;
    bool server;            // является ли данный клиент сервером

public:
    UdpClient(UdpClient*& client);                     // конструктор копирования
    UdpClient(QString nameServer, QString strIpForBind, QString strIpForSend);
    void SendMessage(int x, int y, int rotate, bool shot);  // отправка сопротивнику координат, направления и был ли пострел
    void SendMessageForConnection();                        // (для сервера) отправка клиенту имени сервера при присоединении
    void SendIpClient();                                    // (для клиента) отправка серверу ip клиенту
    void ReadInformationOpponent(int x, int y, int rotate, bool shot);    // чтения полученных данных

signals:
    void signalConnectExecute(QString nameServer);                              // соединение установлено
    void signalReadInformationOpponent(int x, int y, int rotate, bool shot);    // чтения полученных данных

public slots:
    void slotReadMessageClient();
};

#endif // UDPCLIENT_H
