#include "privatechat.h"
#include "ui_privatechat.h"

PrivateChat::PrivateChat(QTcpSocket *senderSocket,QString sender,QString receiver) :
    ui(new Ui::PrivateChat)
{
    ui->setupUi(this);
    this->socket = senderSocket;
    this->receiver = receiver;
    this->sender = sender;
}


PrivateChat::~PrivateChat()
{
    delete ui;
}


QJsonArray PrivateChat::encrypt(QString message)
{
    QJsonArray cipher;
    for(int j = 0 ; j < message.length() ; j++) {
        int result = 1;
        int letter = message.at(j).toLatin1();
        for(int i = 0 ; i < 17 ; i++) {
          result = (result*letter)%n;
        }
        cipher.push_back(result);
    }
    return cipher;
}


void PrivateChat::on_lineEdit_returnPressed()
{
    QString message = ui->lineEdit->text();

    if(!message.isEmpty()) {

        ui->textBrowser->append("You : " + message);

        QJsonArray cipherSender = encrypt(sender);
        QJsonArray cipherReceiver = encrypt(receiver);
        QJsonArray cipherMessage = encrypt(message);


        QJsonObject jsonObject;
        jsonObject.insert("Type", Private);
        jsonObject.insert("Sender",cipherSender);
        jsonObject.insert("Receiver",cipherReceiver);
        jsonObject.insert("Message",cipherMessage);

        QJsonDocument jsonDoc;
        jsonDoc.setObject(jsonObject);
        QByteArray data = jsonDoc.toJson();

        ui->lineEdit->clear();
        if(this->socket->state() == QTcpSocket::ConnectedState){
            socket->write(data);
        }

    }

}
