#include <QCoreApplication>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTextStream>
#include <QDebug>


QTcpSocket socket;

void close();
void receiveMessage();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    socket.connectToHost(QHostAddress::LocalHost,555,QIODevice::ReadWrite);
    while(!socket.waitForConnected(30000));
    QObject::connect(&socket,&QTcpSocket::readyRead,receiveMessage);

    return a.exec();
}

void close() {
    QCoreApplication::exit();

}

void receiveMessage() {

    QString message =  socket.readAll().data();
    qDebug() << message;

    if(message == "bye bye") {
        QObject::connect(&socket,&QTcpSocket::disconnected,close);
        socket.disconnectFromHost();
    }

    else {
        QTextStream in(stdin);
        QString test = in.readLine(0);
        socket.write(test.toUtf8());
    }

}
