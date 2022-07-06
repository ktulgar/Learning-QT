#ifndef CHATSCREEN_H
#define CHATSCREEN_H

#include <QMap>
#include <QWidget>
#include <QListWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include "privatechat.h"
#include "ui_privatechat.h"
#include <QSystemTrayIcon>
#include <QMenu>

namespace Ui {
class ChatScreen;
}

class ChatScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ChatScreen(QTcpSocket *,QTcpSocket *,QString);
    ~ChatScreen();
    Ui::ChatScreen *ui;
    QMap <QString , PrivateChat *> chatRooms;
    QSystemTrayIcon *systemTrayIcon;

private slots:
    void on_lineEdit_7_returnPressed();
    void on_pushButton_4_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_tabWidget_tabCloseRequested(int index);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void stateChanged(QAbstractSocket::SocketState);
    void quit(QAction *);
    void activated(QSystemTrayIcon::ActivationReason);
    void activate();

private:
    QTcpSocket *socket;
    QTcpSocket *imageSocket;
    QString userName;
    QMenu *menu;
    QJsonArray encrypt(QString);
    int q = 53 , p = 61 ;
    int n = p*q;


};

#endif // CHATSCREEN_H
