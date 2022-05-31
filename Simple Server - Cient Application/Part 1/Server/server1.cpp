#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QDate>
#include <QTime>

QTcpServer server;
QTcpSocket *incomingSocket;

const QString userName = "CMPE322";
const QString password = "bilgiuni";
const QString date = "date";
const QString Time = "time";
const QString capTurkey = "capTurkey";
const QString quit = "quit";

bool firstStep = false;
bool secondStep = false;
bool loginPassed = false;

void receiveMessage();
void newConnection();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    server.listen(QHostAddress::LocalHost,555);
   if(server.isListening()) {
       qDebug() << "Server is running ";
       qDebug() << "Address is " << server.serverAddress().toString();
       qDebug() << "Port is " << server.serverPort();
       QObject::connect(&server,&QTcpServer::newConnection,newConnection);

   }
    return a.exec();
}

void receiveMessage() {
    QString message = incomingSocket->readAll().data();

    if(!firstStep) {
          if(message == userName) {
              incomingSocket->write("Please enter the password.");
              firstStep = true;
              secondStep = true;
          }
          else{
              incomingSocket->write("Please enter the user name...");
          }
    }

    else if(secondStep) {
        if(message == password) {
            incomingSocket->write("you are OK, for adking me 'date, time, capTurkey, quit'");
            secondStep = false;
            loginPassed = true;
        }
        else {
            incomingSocket->write("Please enter the password.");
        }
    }

    else if (loginPassed){
        if(message == date) {
            QString answer = QDate::currentDate().toString("dd.MM.yyyy");
            incomingSocket->write(answer.toUtf8());
        }

       else if(message == Time) {
            QString answer = QTime::currentTime().toString("hh:mm");
            incomingSocket->write(answer.toUtf8());
        }

       else if(message == capTurkey) {
            incomingSocket->write("Ankara");
        }

       else if(message == quit) {
            incomingSocket->write("bye bye");
            while(!incomingSocket->waitForBytesWritten(3000));
            server.close();
            QCoreApplication::exit();
        }
        else {
            incomingSocket->write("Your command was not defined.Please try again...");
        }
    }
}


void newConnection() {
   incomingSocket = server.nextPendingConnection();
   incomingSocket->write("Welcome To The Server.");
   incomingSocket->write("Please enter the user name...");
   QObject::connect(incomingSocket,&QTcpSocket::readyRead,receiveMessage);
}
