#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QIcon>
#include <QListWidgetItem>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMenu>
#include "privatechat.h"
#include "ui_privatechat.h"
#include "chatscreen.h"
#include "ui_chatscreen.h"





QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void receiveMessage();
    void receiveImage();
    void on_pushButton_2_clicked();
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_6_clicked();




private:
    Ui::Widget *ui;
     QTcpSocket socket;
     QTcpSocket imageSocket;
     QString userName;
     QByteArray image;
     ChatScreen *chatScreen;
     QJsonArray encrypt(QString);
     QString decrypt(QJsonArray);
     int q = 53 , p = 61 ;
     int n = p*q;


};
#endif // WIDGET_H
