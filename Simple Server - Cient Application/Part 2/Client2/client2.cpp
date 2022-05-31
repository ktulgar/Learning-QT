#include <QCoreApplication>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QDate>
#include <QTime>


QTcpSocket socket;

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
void connected();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject::connect(&socket,&QTcpSocket::connected,connected);
    socket.connectToHost(QHostAddress::LocalHost,555,QIODevice::ReadWrite);
    while(!socket.waitForConnected(30000));
    return a.exec();
}

void receiveMessage() {
    QString message = socket.readAll().data();

    if(!firstStep) {
          if(message == userName) {
              socket.write("Please enter the password...");
              firstStep = true;
              secondStep = true;
          }
          else{
              socket.write("Please enter the user name...");
          }
    }

    else if(secondStep) {
        if(message == password) {
            socket.write("you are OK, for adking me 'date, time, capTurkey, quit'");
            secondStep = false;
            loginPassed = true;
        }
        else {
            socket.write("Please enter the password.");
        }
    }

    else if (loginPassed){
        if(message == date) {
            QString answer = QDate::currentDate().toString("dd.MM.yyyy");
            socket.write(answer.toUtf8());
        }

       else if(message == Time) {
            QString answer = QTime::currentTime().toString("hh:mm");
            socket.write(answer.toUtf8());
        }

       else if(message == capTurkey) {
            socket.write("Ankara");
        }

       else if(message == quit) {
            socket.write("bye bye");
            while(!socket.waitForBytesWritten(3000));
            socket.disconnectFromHost();
            QCoreApplication::exit();
        }
        else {
            socket.write("Your command was not defined.Please try again");
        }
    }
}

void connected() {
   socket.write("Please enter your user name...");
   QObject::connect(&socket,&QTcpSocket::readyRead,receiveMessage);
}
