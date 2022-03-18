#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    serialPort = new QSerialPort(this);
    QWidget::setWindowTitle(" Serial Communication (ReadOnly) ");
    buffer = "";

    // Ports
    ports = info.availablePorts();
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->portsBox->addItems(stringPorts);


    // Baud Rate Ratios
    ui->brateBox->addItem("1200");
    ui->brateBox->addItem("2400");
    ui->brateBox->addItem("4800");
    ui->brateBox->addItem("9600");
    ui->brateBox->addItem("19200");
    ui->brateBox->addItem("38400");
    ui->brateBox->addItem("57600");
    ui->brateBox->addItem("115200");

    // Parities
    ui->parityBox->addItem("No Parity");
    ui->parityBox->addItem("Even Parity");
    ui->parityBox->addItem("Odd Parity");
    ui->parityBox->addItem("Mark Parity");
    ui->parityBox->addItem("Space Parity");

    // Data Bits
    ui->dataBitsBox->addItem("5");
    ui->dataBitsBox->addItem("6");
    ui->dataBitsBox->addItem("7");
    ui->dataBitsBox->addItem("8");

    //Flow Controls
    ui->flowControlBox->addItem("No Flow Control");
    ui->flowControlBox->addItem("Hardware Flow Control");
    ui->flowControlBox->addItem("Software Flow Control");

    // Stop Bits
    ui->stopBitsBox->addItem("1 Bit");
    ui->stopBitsBox->addItem("1,5 Bits");
    ui->stopBitsBox->addItem("2 Bits");

}

Widget::~Widget()
{
    delete ui;
}


void Widget::configure(){

  QString stringbaudRate = ui->brateBox->currentText();
  int   intbaudRate = stringbaudRate.toInt();
  serialPort->setBaudRate(intbaudRate);


  QString dataBits = ui->dataBitsBox->currentText();
  if(dataBits == "5 Bits") {
     serialPort->setDataBits(QSerialPort::Data5);
  }
  else if((dataBits == "6 Bits")) {
     serialPort->setDataBits(QSerialPort::Data6);
  }
  else if(dataBits == "7 Bits") {
     serialPort->setDataBits(QSerialPort::Data7);
  }
  else if(dataBits == "8 Bits"){
     serialPort->setDataBits(QSerialPort::Data8);
  }


  QString parity = ui->parityBox->currentText();
  if(parity == "No Parity"){
    serialPort->setParity(QSerialPort::NoParity);
  }
  else if(parity == "Even Parity"){
    serialPort->setParity(QSerialPort::EvenParity);
  }
  else if(parity == "Odd Parity"){
    serialPort->setParity(QSerialPort::OddParity);
  }
  else if(parity == "Mark Parity"){
    serialPort->setParity(QSerialPort::MarkParity);
  }
  else if(parity == "Space Parity") {
      serialPort->setParity(QSerialPort::SpaceParity);
  }


  QString flowControl = ui->flowControlBox->currentText();
  if(flowControl == "No Flow Control") {
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
  }
  else if(flowControl == "Hardware Flow Control") {
    serialPort->setFlowControl(QSerialPort::HardwareControl);
  }
  else if(flowControl == "Software Flow Control") {
    serialPort->setFlowControl(QSerialPort::SoftwareControl);
  }


  QString portName = ui->portsBox->currentText();
  serialPort->setPortName(portName);

  QString stopBits = ui->stopBitsBox->currentText();
  if(stopBits == "1 Bit") {
   serialPort->setStopBits(QSerialPort::OneStop);
  }
  else if(stopBits == "1,5 Bits") {
   serialPort->setStopBits(QSerialPort::OneAndHalfStop);
  }
  else if(stopBits == "2 Bits") {
   serialPort->setStopBits(QSerialPort::TwoStop);
  }

  code = ui->lineEdit->text();

  serialPort->open(QIODevice::ReadOnly);
}


void Widget::on_connect_clicked()
{
    configure();
    if(!serialPort->isOpen()){
        ui->textBrowser->append("!!!! Something went Wrong !!!!");
    }
    else {
        connect(serialPort,SIGNAL(readyRead()),this,SLOT(read()));
    }

}

void Widget::read(){

    QByteArray dataBA = serialPort->readAll();
    QString data(dataBA);
    buffer.append(data);
    int index = buffer.indexOf(code);
    if(index != -1){
       QString message = buffer.mid(0,index) + "\n";
       ui->textBrowser->append(message);
       buffer.remove(0,index+4);
    }

}


void Widget::on_disConnect_clicked()
{
    if(serialPort->isOpen()) {
        serialPort->close();
    }

}


void Widget::on_refreshComs_clicked()
{
    ports.clear();
    ports = info.availablePorts();
    stringPorts.clear();
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->portsBox->clear();
    ui->portsBox->addItems(stringPorts);
}

