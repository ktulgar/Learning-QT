#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServer>
#include <QBluetoothSocket>
#include <QBluetoothUuid>
#include <QDateTime>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QDate>
#include <QTime>







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
     void deviceDiscovered(const QBluetoothDeviceInfo &);
     void connected();
     void on_pushButton_2_clicked();
     void on_pushButton_4_clicked();
     void on_pushButton_5_clicked();
     void on_pushButton_7_clicked();
     void on_pushButton_9_clicked();
     void on_pushButton_10_clicked();
     void on_pushButton_11_clicked();
     void on_pushButton_6_clicked();
     void on_pushButton_clicked();

     void on_pushButton_3_clicked();

private:

    Ui::Widget *ui;
    QBluetoothLocalDevice localDevice;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothAddress addressToConnect;
    QBluetoothSocket *socket;

    QPixmap sendPixmap;
    QPixmap previousPixmap;
    QPixmap addPixmap;
    QPixmap undoPixmap;
    QPixmap resetPixmap;
    QPixmap tickPixmap;
    QPixmap crossPixmap;
    QPixmap searchPixmap;
    QPixmap bluetoothPixmap;
    QPixmap nextPixmap;
    QPixmap dateTimePixmap;

    QIcon sendButtonIcon;
    QIcon previousButtonIcon;
    QIcon addButtonIcon;
    QIcon undoButtonIcon;
    QIcon resetButtonIcon;
    QIcon tickButtonIcon;
    QIcon crossButtonIcon;
    QIcon searchButtonIcon;
    QIcon bluetoothButtonIcon;
    QIcon nextIcon;
    QIcon dateTimeIcon;


};
#endif // WIDGET_H
