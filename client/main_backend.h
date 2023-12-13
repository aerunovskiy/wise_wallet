#ifndef MAIN_BACKEND_H
#define MAIN_BACKEND_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QTimer>

class MainBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString response READ getResponse NOTIFY responseChanged)

public:
    explicit MainBackend(QObject *parent = nullptr);

    QString getResponse() const;

signals:
    void dataChanged(const QString &newData);

    void responseChanged();

public slots:
    void processData(const QString &data);

    void sendMessage(const QString &message);

private slots:

    void onReadyRead();

    void onConnected();

    void onDisconnected();

    void checkConnection();

private:
    QSharedPointer<QTcpSocket> socket;

    QString response;

    QString serverHost { "127.0.0.1" };

    quint16 serverPort { 8888 };

};

#endif // MAIN_BACKEND_H
