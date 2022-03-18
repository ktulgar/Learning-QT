#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    nextPixmap.load(":/resources/images/next.png");
    nextIcon.addPixmap(nextPixmap);
    ui->pushButton_4->setIcon(nextIcon);
    ui->pushButton_4->setIconSize(ui->pushButton_4->size());

    dateTimePixmap.load(":/resources/images/dateTime.png");
    dateTimeIcon.addPixmap(dateTimePixmap);
    ui->pushButton->setIcon(dateTimeIcon);
    ui->pushButton->setIconSize(ui->pushButton->size());

    bluetoothPixmap.load(":/resources/images/bluetooth.png");
    bluetoothButtonIcon.addPixmap(bluetoothPixmap);
    ui->pushButton_3->setIcon(bluetoothButtonIcon);
    ui->pushButton_3->setIconSize(ui->pushButton_3->size());

    searchPixmap.load(":/resources/images/search.png");
    searchButtonIcon.addPixmap(searchPixmap);
  //  ui->pushButton->setIcon(searchButtonIcon);
   // ui->pushButton->setIconSize(ui->pushButton->size());

    tickPixmap.load(":/resources/images/tick.png");
    tickButtonIcon.addPixmap(tickPixmap);
    crossPixmap.load(":/resources/images/carpi.png");
    crossButtonIcon.addPixmap(crossPixmap);
    ui->pushButton_2->setIcon(crossButtonIcon);
    ui->pushButton_2->setIconSize(ui->pushButton_2->size());

    sendPixmap.load(":/resources/images/send.png");
    sendButtonIcon.addPixmap(sendPixmap);
    ui->pushButton_5->setIcon(sendButtonIcon);
    ui->pushButton_5->setIconSize(ui->pushButton_5->size());
    ui->pushButton_7->setIcon(sendButtonIcon);
    ui->pushButton_7->setIconSize(ui->pushButton_7->size());

    resetPixmap.load(":/resources/images/reset.png");
    resetButtonIcon.addPixmap(resetPixmap);
    ui->pushButton_6->setIcon(resetButtonIcon);
    ui->pushButton_6->setIconSize(ui->pushButton_6->size());

    previousPixmap.load(":/resources/images/previous.png");
    previousButtonIcon.addPixmap(previousPixmap);
    ui->pushButton_11->setIcon(previousButtonIcon);
    ui->pushButton_11->setIconSize(ui->pushButton_11->size());

    addPixmap.load(":/resources/images/add.png");
    addButtonIcon.addPixmap(addPixmap);
    ui->pushButton_9->setIcon(addButtonIcon);
    ui->pushButton_9->setIconSize(ui->pushButton_9->size());

    undoPixmap.load(":/resources/images/undo.png");
    undoButtonIcon.addPixmap(undoPixmap);
    ui->pushButton_10->setIcon(undoButtonIcon);
    ui->pushButton_10->setIconSize(ui->pushButton_10->size());


    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    connect(discoveryAgent,SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo &)),this,SLOT(deviceDiscovered(const QBluetoothDeviceInfo &)));
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));


}

Widget::~Widget()
{
    delete ui;
}


// When new bluetooth device discovered nearby it displays information of name and address on list widget
void Widget::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
   QString message = device.name() + " " + device.address().toString();
 //  ui->listWidget->addItem(message);
}


// When app is connected to bluetooth module icon that is on the button of connect changes to tick
void Widget::connected()
{
    ui->pushButton_2->setIcon(tickButtonIcon);
    ui->pushButton_2->setIconSize(ui->pushButton_2->size());
}


// It tries establish connection with HC-05
void Widget::on_pushButton_2_clicked()
{
     addressToConnect = QBluetoothAddress(QString("98:D3:51:F5:C1:95")); // HC05 Bluetooth Address
     static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
     socket->connectToService(addressToConnect,QBluetoothUuid(serviceUuid),QIODevice::ReadWrite);
}


// The Button Of Next
void Widget::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}


// (Second Mode) It sends information of date, time and amount that user wants to feed pet.
void Widget::on_pushButton_5_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget_2->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        socket->write(item->text().toUtf8());
        delete ui->listWidget_2->takeItem(ui->listWidget_2->row(item));
    }

}


// (First Mode) It sends information of amount that user wants to feed pet.
void Widget::on_pushButton_7_clicked()
{
    QString grams = ui->spinBox_2->text();
    QString message = "A " + grams;
    socket->write(message.toUtf8());

}


// The Button Of Reset System
// It sends instruction of Reset to development board
void Widget::on_pushButton_6_clicked()
{
    QString reset = "Reset";
    socket->write(reset.toUtf8());
}


// It adds selected information of date, time and amount to list widget
void Widget::on_pushButton_9_clicked()
{
    QString date = ui->calendarWidget->selectedDate().toString("dd.MM.yy") ;
    QString time = ui->timeEdit->time().toString("hh:mm:ss");
    QString grams = ui->spinBox->text();

    QString message = "B " + date + " " + time + " " + grams;
    ui->listWidget_2->addItem(message);
}


// It removes selected items from list widget
void Widget::on_pushButton_10_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget_2->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget_2->takeItem(ui->listWidget_2->row(item));
    }
}


// The Button "Previous"
void Widget::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


// It sends current time and date to development board
void Widget::on_pushButton_clicked()
{
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    QString currentDate = QDate::currentDate().toString("dd.MM.yy");
    QString message = "Adjustment " + currentDate + " " + currentTime;
    socket->write(message.toUtf8());
}


// The Button Of Bluetooth On/Off
// It toggles bluetooth
void Widget::on_pushButton_3_clicked()
{
    if(localDevice.hostMode() == QBluetoothLocalDevice::HostPoweredOff) {
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    }
    else localDevice.setHostMode(QBluetoothLocalDevice::HostPoweredOff);
}
