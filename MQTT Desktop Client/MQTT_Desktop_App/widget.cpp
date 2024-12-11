#include "widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Disable maximizing
    setFixedSize(width(), height());

    // Adding title for widget
    QWidget::setWindowTitle("STM32 - QT MQTT Application");

    QPixmap pix(":images/temp_icon.png");
    ui->label->setPixmap(pix);

    QPixmap pix1(":images/dcMotor.png");
    ui->label_2->setPixmap(pix1);

    QPixmap pix2(":images/Acc_Icon.png");
    ui->label_3->setPixmap(pix2);

    QPixmap pix3(":images/st.png");
    ui->label_16->setPixmap(pix3);

    QPixmap pix4(":images/MQTT.png");
    ui->label_17->setPixmap(pix4);

    QPixmap pix5(":images/qt.png");
    ui->label_15->setPixmap(pix5);

  //  QPixmap pix6(":images/potentiometer.png");
  //  ui->label_18->setPixmap(pix6);

    QPixmap pix7(":images/x.png");
    ui->label_9->setPixmap(pix7);

    QPixmap pix8(":images/y.png");
    ui->label_10->setPixmap(pix8);

    QPixmap pix9(":images/z.png");
    ui->label_11->setPixmap(pix9);

    QPixmap pix11(":images/atmospheric_pressure.png");
    ui->label_12->setPixmap(pix11);

    QPixmap pix10(":images/altitude.png");
    ui->label_13->setPixmap(pix10);

    QPixmap pixmapConnect;
    QIcon   iconConnect;
    pixmapConnect.load(":images/connect.png");
    iconConnect.addPixmap(pixmapConnect);
    ui->pushButton_7->setIcon(iconConnect);
    ui->pushButton_7->setIconSize( ui->pushButton_7->rect().size());


    QPixmap pixmapSubscribe;
    QIcon   iconSubscribe;
    pixmapSubscribe.load(":images/subscribe.png");
    iconSubscribe.addPixmap(pixmapSubscribe);
    ui->pushButton_9->setIcon(iconSubscribe);
    ui->pushButton_9->setIconSize( ui->pushButton_9->rect().size());

    QPixmap pixmapNext;
    QIcon   iconNext;
    pixmapNext.load(":images/next_page.png");
    iconNext.addPixmap(pixmapNext);
    ui->pushButton_10->setIcon(iconNext);
    ui->pushButton_10->setIconSize(ui->pushButton_10->rect().size());

    ui->textBrowser->setTextColor(Qt::green);

    pixmapOffRed.load(":/images/off_red.png");
    pixmapOffYellow.load(":/images/off_yellow.png");
    pixmapOffGreen.load(":/images/off_green.png");

    pixmapOnRed.load(":/images/on_red.png");
    pixmapOnYellow.load(":/images/on_yellow.png");
    pixmapOnGreen.load(":/images/on_green.png");

    iconOffRed.addPixmap(pixmapOffRed);
    iconOffGreen.addPixmap(pixmapOffGreen);
    iconOffYellow.addPixmap(pixmapOffYellow);

    iconOnRed.addPixmap(pixmapOnRed);
    iconOnGreen.addPixmap(pixmapOnGreen);
    iconOnYellow.addPixmap(pixmapOnYellow);


    ui->pushButton->setIcon(iconOffRed);
    ui->pushButton_2->setIcon(iconOffGreen);
    ui->pushButton_3->setIcon(iconOffYellow);

    ui->pushButton->setIconSize(pixmapOffRed.rect().size());
    ui->pushButton_2->setIconSize(pixmapOffGreen.rect().size());
    ui->pushButton_3->setIconSize(pixmapOffYellow.rect().size());


    connect(&m_client,SIGNAL(stateChanged(QMqttClient::ClientState)),this,SLOT(stateChanged(QMqttClient::ClientState)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QMqttTopicName topic("RED_LED");
    if(off_button_1)
    {
        QByteArray message("ON");
        m_client.publish(topic,message);
        ui->pushButton->setIcon(iconOnRed);
        ui->pushButton->setIconSize(pixmapOnRed.rect().size());
        off_button_1 = false;
    }
    else
    {
        QByteArray message("OFF");
        m_client.publish(topic,message);
        ui->pushButton->setIcon(iconOffRed);
        ui->pushButton->setIconSize(pixmapOffRed.rect().size());
        off_button_1 = true;
    }

}


void Widget::on_pushButton_2_clicked()
{
    QMqttTopicName topic("GREEN_LED");
    if(off_button_2)
    {
        QByteArray message("ON");
        m_client.publish(topic,message);
        ui->pushButton_2->setIcon(iconOnGreen);
        ui->pushButton_2->setIconSize(pixmapOnGreen.rect().size());
        off_button_2 = false;
    }
    else
    {
        QByteArray message("OFF");
        m_client.publish(topic,message);
        ui->pushButton_2->setIcon(iconOffGreen);
        ui->pushButton_2->setIconSize(pixmapOffGreen.rect().size());
        off_button_2 = true;
    }
}


void Widget::on_pushButton_3_clicked()
{
    QMqttTopicName topic("YELLOW_LED");
    if(off_button_3)
    {
        QByteArray message("ON");
        m_client.publish(topic,message);
        ui->pushButton_3->setIcon(iconOnYellow);
        ui->pushButton_3->setIconSize(pixmapOnYellow.rect().size());
        off_button_3 = false;
    }
    else
    {
        QByteArray message("OFF");
        m_client.publish(topic,message);
        ui->pushButton_3->setIcon(iconOffYellow);
        ui->pushButton_3->setIconSize(pixmapOffYellow.rect().size());
        off_button_3 = true;
    }
}


void Widget::on_pushButton_7_clicked()
{
    m_client.setHostname( ui->lineEdit->text());
    m_client.setPort(ui->lineEdit_2->text().toInt());
    m_client.setUsername(ui->lineEdit_3->text());
    m_client.setPassword(ui->lineEdit_7->text());
    m_client.setClientId(ui->lineEdit_9->text());
    m_client.connectToHost();

}


void Widget::on_pushButton_9_clicked()
{
    QString topicName = ui->lineEdit_8->text();
    QMqttSubscription *topic_pointer =m_client.subscribe(topicName);
    if(topic_pointer != nullptr)
    {
        connect(topic_pointer,SIGNAL(messageReceived(QMqttMessage)),this,SLOT(messageReceived(QMqttMessage)));
        ui->textBrowser->append("... Subscribed To " + topicName +" Succesfully ...");
    }

}

void Widget::messageReceived(QMqttMessage mqttMessage)
{
    QString topicName = mqttMessage.topic().name();
    QString message = mqttMessage.payload();
    if(QString::compare(topicName,"BMP180",Qt::CaseSensitive) == 0)
    {
        QStringList val_list = message.split("  ");
        QString temperature = val_list.at(0);
        QString pressure = val_list.at(1);
        QString altitude = val_list.at(2);
        ui->lcdNumber->display(temperature);
        ui->lcdNumber_8->display(pressure);
        ui->lcdNumber_9->display(altitude);
    }
    else if(QString::compare(topicName,"MPU6050",Qt::CaseSensitive) == 0)
    {
        QStringList val_list = message.split("  ");
        QString ACC_X_Val = val_list.at(0);
        QString ACC_Y_Val = val_list.at(1);
        QString ACC_Z_Val = val_list.at(2);
        QString GYRO_X_Val = val_list.at(3);
        QString GYRO_Y_Val = val_list.at(4);
        QString GYRO_Z_Val = val_list.at(5);
        ui->lcdNumber_2->display(ACC_X_Val);
        ui->lcdNumber_3->display(ACC_Y_Val);
        ui->lcdNumber_4->display(ACC_Z_Val);
        ui->lcdNumber_5->display(GYRO_X_Val);
        ui->lcdNumber_6->display(GYRO_Y_Val);
        ui->lcdNumber_7->display(GYRO_Z_Val);
    }

}


void Widget:: stateChanged(QMqttClient::ClientState state)
{
    if(state == QMqttClient::ClientState::Disconnected)
    {
         ui->textBrowser->append("... not connected  ...");
    }
    else if(state == QMqttClient::ClientState::Connecting)
    {
         ui->textBrowser->append("... connecting ...");
    }
    else
    {
         ui->textBrowser->append("... connected ...");
    }

}

void Widget::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Widget::on_horizontalSlider_sliderReleased()
{
    QMqttTopicName topic("MOTOR_SPEED");
    QByteArray message = QString::number(ui->horizontalSlider->value()).toLocal8Bit();
    m_client.publish(topic,message);
}






