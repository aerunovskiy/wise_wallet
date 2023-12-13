#include "main_backend.h"

MainBackend::MainBackend(QObject *parent)
    : QObject{parent}
{
    socket = QSharedPointer<QTcpSocket>(new QTcpSocket(this));

    connect(socket.get(), &QTcpSocket::connected, this, &MainBackend::onConnected);
    connect(socket.get(), &QTcpSocket::disconnected, this, &MainBackend::onDisconnected);
    connect(socket.get(), &QTcpSocket::readyRead, this, &MainBackend::onReadyRead);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainBackend::checkConnection);
    timer->start(1000);
}

QString MainBackend::getResponse() const
{
    return response;
}

void MainBackend::processData(const QString &data)
{
    qDebug() << "Received data from QML:" << data;

    emit dataChanged("Processed: " + data);
}

void MainBackend::sendMessage(const QString &message)
{
     if (socket->state() == QAbstractSocket::ConnectedState)
    {
        qDebug() << "Sending message:" << message;
        socket->write(message.toUtf8());
    }
    else
    {
        qDebug() << "Error?";
    }
}

void MainBackend::onReadyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << "Received message:" << data;

    response = QString(data);
    emit responseChanged();
}

void MainBackend::onConnected()
{
    qDebug() << "Connected to server";
}

void MainBackend::onDisconnected()
{
    qDebug() << "Disconnected from server";
}

void MainBackend::checkConnection()
{
    if (socket->state() != QAbstractSocket::ConnectedState)
    {
        socket->connectToHost(serverHost, serverPort);
    }
}
