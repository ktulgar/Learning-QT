#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QTextStream>

QTcpServer server;
QTcpSocket *incomingSocket;

void newConnection();
void receiveMessage();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QObject::connect(&server,&QTcpServer::newConnection,newConnection);
    server.listen(QHostAddress::LocalHost,555);
    return a.exec();
}

void receiveMessage() {

    QString message =  incomingSocket->readAll().data();
    qDebug() << message;

    if(message == "bye bye") {
        server.close();
        QCoreApplication::exit();
    }

    else {
        QTextStream in(stdin);
        QString test = in.readLine(0);
        incomingSocket->write(test.toUtf8());
    }
}

void newConnection() {
     incomingSocket = server.nextPendingConnection();
     QObject::connect(incomingSocket,&QTcpSocket::readyRead,receiveMessage);
}
