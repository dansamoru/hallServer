#pragma once
#include <QByteArray>
#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>

class MyTcpServer : public QTcpServer {
  Q_OBJECT
 public:
  explicit MyTcpServer(QObject *parent = nullptr);
  ~MyTcpServer();
  QByteArray parse(QByteArray array);
 public slots:
  void slotNewConnection();
  void slotClientDisconnected();

  void slotServerRead();
  // void slotReadClient();
 private:
  QTcpServer *tcpServer;
  QVector<QTcpSocket *> tcpSockets;
  int server_status;
};