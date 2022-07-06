#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDate>
#include <QTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMap>
#include <QPair>
#include <QFile>
#include <QPixmap>
#include <QIcon>
#include <QFileDialog>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QSystemTrayIcon>
#include <QMenu>

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

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    struct Client{
        QString name;
        QString surname;
        QString mail;
        QString department;
        QString  loginDate;
        QString  loginTime;
    };

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void newClient();
    void quit(QAction *);
    void activated(QSystemTrayIcon::ActivationReason);
    void sendImage();
    void imageClient();
    void receiveMessage();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void changeColor();
    void on_pushButton_3_pressed();
    void on_pushButton_3_released();
    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QTcpServer server;
    QMap<QTcpSocket *,struct Client> connectedClients;
    QSqlDatabase db;
    QByteArray   activityDuration;
    QByteArray   groupChat;
    QByteArray   image;
    QTcpServer imageServer;
    QTimer     timer;
    QString color;
    int activeUsers;
    QMap<QPair<QString,QString>,QByteArray> chatRooms;
    QSystemTrayIcon *systemTrayIcon;
    QMenu *menu;
    QPixmap pixmapApp;
    QIcon iconApp;
    QJsonArray encrypt(QString);
    QString decrypt(QJsonArray);
    int q = 53 , p = 61 ;
    int n = p*q;

};
#endif // WIDGET_H
