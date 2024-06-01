#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Disable maximizing
    setFixedSize(width(), height());

    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->comboBox->addItems(stringPorts);

    connect(&timer, SIGNAL(timeout()), this,SLOT(update()));
    time.setHMS(0,0,0);

    ui->buttonGroup->setId(ui->radioButton_9,8000);
    ui->buttonGroup->setId(ui->radioButton_7,16000);
    ui->buttonGroup->setId(ui->radioButton_10,32000);
    ui->buttonGroup->setId(ui->radioButton_8,44100);
    ui->buttonGroup->setId(ui->radioButton_6,48000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::update()
{
    time = time.addSecs(1);
    ui->lcdNumber->display(time.toString("mm:ss"));
    timer.start(1000);
}

void Widget::on_pushButton_clicked()
{
    QString SampleRate = QString::number( ui->buttonGroup->checkedId());
    QString FileName   = ui->lineEdit->text();
    QString command = SampleRate + " " + FileName + " START";
    ui->lineEdit->setText("");
    serialPort.write(command.toUtf8());
    ui->pushButton->setDisabled(true);
    ui->radioButton_6->setCheckable(false);
    ui->radioButton_7->setCheckable(false);
    ui->radioButton_8->setCheckable(false);
    ui->radioButton_9->setCheckable(false);
    ui->radioButton_10->setCheckable(false);
    timer.start(1000);

}


void Widget::on_pushButton_5_clicked()
{
    ui->comboBox->clear();
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->comboBox->addItems(stringPorts);
}


void Widget::on_pushButton_4_clicked()
{
    QString portName = ui->comboBox->currentText();
    serialPort.setPortName(portName);
    serialPort.setBaudRate(115200);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);
    serialPort.open(QIODevice::ReadWrite);

    if(serialPort.isOpen())
    {
        ui->pushButton_4->setStyleSheet("background-color : green");
    }
    else
    {
        ui->pushButton_4->setStyleSheet("background-color : red");
    }
}




void Widget::on_pushButton_3_clicked()
{
    timer.stop();
    time.setHMS(0,0,0);
    ui->lcdNumber->display("");
    serialPort.write(QString("STOP").toUtf8());
    ui->pushButton->setDisabled(false);

    if(QString::compare(ui->pushButton_2->text(),"RESUME",Qt::CaseSensitive) == 0)
    {
        ui->pushButton_2->setText("PAUSE");
    }

    ui->radioButton_6->setCheckable(true);
    ui->radioButton_7->setCheckable(true);
    ui->radioButton_8->setCheckable(true);
    ui->radioButton_9->setCheckable(true);
    ui->radioButton_10->setCheckable(true);
}


void Widget::on_pushButton_2_clicked()
{
    if(QString::compare(ui->pushButton_2->text(),"PAUSE",Qt::CaseSensitive) == 0)
    {
        timer.stop();
        ui->pushButton_2->setText("RESUME");
        serialPort.write(QString("PAUSE").toUtf8());
    }
    else if(QString::compare(ui->pushButton_2->text(),"RESUME",Qt::CaseSensitive) == 0)
    {
        timer.start(1000);
        ui->pushButton_2->setText("PAUSE");
        serialPort.write(QString("RESUME").toUtf8());
    }

}

