#include <mytcpserver.h>

MyTcpServer::~MyTcpServer() {
  this->close();
  server_status = false;
}

MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer(parent) {
  connect(this, &QTcpServer::newConnection, this,
          &MyTcpServer::slotNewConnection);

  if (!this->listen(QHostAddress::Any, 33333)) {
    qDebug() << "Server is not started";
  } else {
    server_status = true;
    qDebug() << "Server is started";
  }
}

void MyTcpServer::slotNewConnection() {
  if (server_status == 1) {
    QTcpSocket *currTcpSocket;
    currTcpSocket = this->nextPendingConnection();
    currTcpSocket->write("Hello, World!!! I am echo server!\r\n");
    connect(currTcpSocket, &QTcpSocket::readyRead, this,
            &MyTcpServer::slotServerRead);
    connect(currTcpSocket, &QTcpSocket::disconnected, this,
            &MyTcpServer::slotClientDisconnected);
    tcpSockets.push_back(currTcpSocket);
  }
}

void MyTcpServer::slotServerRead() {
  QByteArray array;
  QTcpSocket *currTcpSocket = (QTcpSocket *)sender();
  while (currTcpSocket->bytesAvailable() > 0) {
    array.append(currTcpSocket->readAll());
  }
  if (array.right(1) == "\n") {
    currTcpSocket->write(parse(array.trimmed()));
  }
}

void MyTcpServer::slotClientDisconnected() {
  QTcpSocket *currTcpSocket = (QTcpSocket *)sender();
  currTcpSocket->close();
}

QByteArray MyTcpServer::parse(QByteArray array) {
  QString data = QString::fromUtf8(array).trimmed();
  QStringList commandParts = QString::fromUtf8(array).trimmed().split('&');

  if (commandParts.isEmpty()) {
    return "Неверная команда\n";
  }

  QString command = commandParts.first();

  if (command == "start" && commandParts.size() == 3) {
    QString login = commandParts.at(1);
    QString roomname = commandParts.at(2);
    return "Команда начала\n";
  } else if (command == "break" && commandParts.size() == 1) {
    return "Выход из комнаты\n";
  } else if (command == "stats" && commandParts.size() == 1) {
    return "Получить статистику\n";
  } else if (command == "rooms" && commandParts.size() == 1) {
    return "Получить список комнат\n";
  } else if (command == "newroom" && commandParts.size() == 2) {
    QString roomname = commandParts.at(1);
    return "Создать комнату\n";
  } else {
    return "Неверная команда\n";
  }
}