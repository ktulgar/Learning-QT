#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H

#include <QDialog>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#define NoRegistration 0
#define NoEmploymentFound 1
#define SUCCESS_LOGIN 2
#define SUCCESS_SIGNUP 3
#define WrongPassword 4
#define All 5
#define ActiveClients 6
#define Info 7
#define Private 8
#define SignIn 9
#define SignUp 10
#define Exit 11

namespace Ui {
class PrivateChat;
}

class PrivateChat : public QDialog
{
    Q_OBJECT

public:
    explicit PrivateChat(QTcpSocket *senderSocket,QString sender,QString receiver);
    ~PrivateChat();
    Ui::PrivateChat *ui;
    QTcpSocket *socket;
    QString receiver;
    QString sender;


private slots:
    void on_lineEdit_returnPressed();


private:
    QJsonArray encrypt(QString);
    int q = 53 , p = 61 ;
    int n = p*q;

};

#endif // PRIVATECHAT_H
