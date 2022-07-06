#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    pixmapApp.load(":/images/appIcon.png");
    iconApp.addPixmap(pixmapApp);

    systemTrayIcon = new QSystemTrayIcon(this);
    systemTrayIcon->setIcon(iconApp);
    systemTrayIcon->setVisible(true);
    QMenu *menu = new QMenu();
    QAction *quit = new QAction();
    quit->setText("Quit");
    menu->addAction(quit);
    systemTrayIcon->setContextMenu(menu);
    connect(menu,SIGNAL(triggered(QAction *)),this,SLOT(quit(QAction *)));
    connect(systemTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(activated(QSystemTrayIcon::ActivationReason)));

    QWidget::setWindowIcon(iconApp);
    QWidget::setFixedSize(QSize(475,369));
    QWidget::setWindowTitle("Sigmoid Chat Server");

    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("localhost");
    this->db.setPort(3306);
    this->db.setDatabaseName("company");
    this->db.setUserName("root");
    this->db.setPassword("123456789");
    this->db.open();

    ui->stackedWidget->setCurrentIndex(0);

    QPixmap pixmapAddEmp;
    QIcon iconAddEmp;
    pixmapAddEmp.load(":/images/addEmp.png");
    iconAddEmp.addPixmap(pixmapAddEmp);
    ui->pushButton_6->setIcon(iconAddEmp);
    ui->pushButton_6->setIconSize(ui->pushButton_6->size());

    QPixmap pixmapChatServer;
    QIcon iconChatServer;
    pixmapChatServer.load(":/images/chatServer.png");
    iconChatServer.addPixmap(pixmapChatServer);
    ui->pushButton_7->setIcon(iconChatServer);
    ui->pushButton_7->setIconSize(ui->pushButton_7->size());

    QPixmap pixmapAdd;
    QIcon iconAdd;
    pixmapAdd.load(":/images/add.png");
    iconAdd.addPixmap(pixmapAdd);
    ui->pushButton_9->setIcon(iconAdd);
    ui->pushButton_9->setIconSize(ui->pushButton_9->size());

    QPixmap pixmapBack;
    QIcon iconBack;
    pixmapBack.load(":/images/back.png");
    iconBack.addPixmap(pixmapBack);
    ui->pushButton_10->setIcon(iconBack);
    ui->pushButton_10->setIconSize(ui->pushButton_10->size());

    QPixmap pixmapSearch;
    QIcon iconSearch;
    pixmapSearch.load(":/images/search.png");
    iconSearch.addPixmap(pixmapSearch);
    ui->pushButton_8->setIcon(iconSearch);
    ui->pushButton_8->setIconSize(ui->pushButton_8->size());

    QPixmap pixmapReport;
    QIcon iconReport;
    pixmapReport.load(":/images/timedate.jpg");
    iconReport.addPixmap(pixmapReport);
    ui->pushButton_5->setIcon(iconReport);
    ui->pushButton_5->setIconSize(ui->pushButton_5->size());

    QPixmap pixmapStart;
    QIcon iconStart;
    pixmapStart.load(":/images/Start.png");
    iconStart.addPixmap(pixmapStart);
    ui->pushButton->setIcon(iconStart);
    ui->pushButton->setIconSize(ui->pushButton->size());

    QPixmap pixmapStop;
    QIcon iconStop;
    pixmapStop.load(":/images/stop.png");
    iconStart.addPixmap(pixmapStop);
    ui->pushButton_3->setIcon(iconStart);
    ui->pushButton_3->setIconSize(ui->pushButton_3->size());

    QPixmap pixmapGroup;
    QIcon iconGroup;
    pixmapGroup.load(":/images/group.png");
    iconGroup.addPixmap(pixmapGroup);
    ui->pushButton_4->setIcon(iconGroup);
    ui->pushButton_4->setIconSize(ui->pushButton_4->size());

    QPixmap pixmapPrivate;
    QIcon iconPrivate;
    pixmapPrivate.load(":/images/privateChat.png");
    iconPrivate.addPixmap(pixmapPrivate);
    ui->pushButton_2->setIcon(iconPrivate);
    ui->pushButton_2->setIconSize(ui->pushButton_2->size());


    ui->pushButton_11->setIcon(iconBack);
    ui->pushButton_11->setIconSize(ui->pushButton_11->size());


    connect(&timer,SIGNAL(timeout()),this,SLOT(changeColor()));
    color = "White";
    activeUsers = 0;
    ui->lcdNumber->display(activeUsers);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{

    bool status = this->server.listen(QHostAddress("192.168.1.20"),777);
    bool status2 = imageServer.listen(QHostAddress("192.168.1.20"),2500);

    if(status && status2) {
        timer.start(1000);
        connect(&this->server,SIGNAL(newConnection()),this,SLOT(newClient()));
        connect(&imageServer,SIGNAL(newConnection()),this,SLOT(imageClient()));
    }
}


void Widget::newClient()
{
    QTcpSocket *socket = server.nextPendingConnection();
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
}

void Widget::quit(QAction *action)
{
    QCoreApplication::quit();
}

void Widget::sendImage()
{
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
    QByteArray data = socket->readAll();

    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject object = document.object();
    QJsonArray cipherWhoseInfo = object.value("Whose Info").toArray();
    QString whoseInfo = decrypt(cipherWhoseInfo);

    QSqlQuery query(this->db);
    query.exec("select image from sigmoidchat where mail ='"+whoseInfo+"'");
    query.next();
    QByteArray imagev2 = query.value(0).toByteArray();

    imagev2.append("*#%END%#*");
    socket->write(imagev2);

}

void Widget::imageClient()
{
    QTcpSocket *socket = imageServer.nextPendingConnection();
    connect(socket,SIGNAL(readyRead()),this,SLOT(sendImage()));
}

void Widget::receiveMessage() {

     QTcpSocket *socket = static_cast<QTcpSocket *>(sender());

     QByteArray receivedData = socket->readAll();
     QJsonDocument receivedDocument = QJsonDocument::fromJson(receivedData);
     QJsonObject receivedObject = receivedDocument.object();

     QJsonObject sentObject;
     QJsonDocument sentDoc;

     int type = receivedObject.value("Type").toInt();

     if(type == SignIn) {

        QJsonArray cipherUserName = receivedObject.value("User Name").toArray();
        QJsonArray cipherPassword = receivedObject.value("Password").toArray();

        QString userName = decrypt(cipherUserName);
        QString password = decrypt(cipherPassword);

        QSqlQuery query(this->db);
        query.prepare("select * from sigmoidchat where mail=:mailAddress");
        query.bindValue(":mailAddress",userName);
        query.exec();
        int size = query.size();
        if(size > 0){
           query.next();
           if(!query.value("chatRegisterStatus").toBool()) {
               QJsonObject jsonObject;
               jsonObject.insert("Type", NoRegistration);
               QJsonDocument jsonDoc;
               jsonDoc.setObject(jsonObject);
               QByteArray data = jsonDoc.toJson();
               socket->write(data);
            }
           else {
               if(!(query.value("password").toString() == password)){
                   QJsonObject jsonObject;
                   jsonObject.insert("Type", WrongPassword);
                   QJsonDocument jsonDoc;
                   jsonDoc.setObject(jsonObject);
                   QByteArray data = jsonDoc.toJson();
                   socket->write(data);
                         }
               else{
                   QString email = userName;
                   QTcpSocket *client = socket;
                   struct Client user;
                   user.mail = email;
                   user.loginTime = QTime::currentTime().toString("hh:mm");
                   user.loginDate = QDate::currentDate().toString("dd:MM:yy");
                   connectedClients.insert(client,user);
                   ui->textBrowser->setTextColor(Qt::darkGreen);
                   ui->textBrowser->append(userName + " has logged in.");
                   activeUsers++;
                   ui->lcdNumber->display(activeUsers);

                   sentObject.insert("Type", SUCCESS_LOGIN);

                   sentDoc.setObject(sentObject);
                   QByteArray data = sentDoc.toJson();
                   socket->write(data);
                   }
                  }

               }

        else {

            sentObject.insert("Type", NoEmploymentFound);
            sentDoc.setObject(sentObject);
            QByteArray data = sentDoc.toJson();
            socket->write(data);
         }
      }
     else if(type == SignUp) {

         QJsonArray cipherUserName = receivedObject.value("User Name").toArray();
         QJsonArray cipherPassword = receivedObject.value("Password").toArray();

         QString userName = decrypt(cipherUserName);
         QString password = decrypt(cipherPassword);

         QSqlQuery query(this->db);
         query.prepare("select * from sigmoidchat where mail=:mailAddress");
         query.bindValue(":mailAddress",userName);
         query.exec();
         int size = query.size();
         if(size > 0){
             QString queryString = "UPDATE sigmoidchat SET password ='"+password+"', chatRegisterStatus = 1 WHERE mail ='"+userName+"'";
             query.exec(queryString);
             ui->textBrowser->setTextColor(Qt::blue);
             ui->textBrowser->append(userName + " has signed up.");
             sentObject.insert("Type", SUCCESS_SIGNUP);
             sentDoc.setObject(sentObject);
             QByteArray data = sentDoc.toJson();
             socket->write(data);
         }
         else {

             sentObject.insert("Type", NoEmploymentFound);
             sentDoc.setObject(sentObject);
             QByteArray data = sentDoc.toJson();
             socket->write(data);
         }
     }

     else if(type == All) {

         QMapIterator<QTcpSocket * , struct Client> iterator(connectedClients);
         while(iterator.hasNext()) {
             iterator.next();
             if(iterator.key()->socketDescriptor() == socket->socketDescriptor()) {
                 continue;
             }
             else{
                 iterator.key()->write(receivedData);
             }
         }

         QJsonArray cipherSender = receivedObject.value("Sender").toArray();
         QJsonArray cipherMessage = receivedObject.value("Message").toArray();

         QString message = decrypt(cipherMessage);
         QString sender  = decrypt(cipherSender);

         message.append("\n");
         message = sender + " : " + message;
         groupChat.append(message.toUtf8());
     }

     else if(type == Info) {

         QJsonArray cipherWhoseInfo = receivedObject.value("Whose Info").toArray();
         QString whose = decrypt(cipherWhoseInfo);

         QSqlQuery query(this->db);
         query.exec("select name,surname,department from sigmoidchat where mail ='"+whose+"'");
         query.next();
         QString name = query.value(0).toString();
         QString surname = query.value(1).toString();
         QString department = query.value(2).toString();

         QJsonArray cipherName = encrypt(name);
         QJsonArray cipherSurname = encrypt(surname);
         QJsonArray cipherDepartment = encrypt(department);

         sentObject.insert("Type", Info);
         sentObject.insert("Name", cipherName);
         sentObject.insert("Surname", cipherSurname);
         sentObject.insert("Department", cipherDepartment);

         sentDoc.setObject(sentObject);
         QByteArray data = sentDoc.toJson();
         socket->write(data);
     }


     else if(type == Private) {

         QJsonArray cipherSender = receivedObject.value("Sender").toArray();
         QJsonArray cipherReceiver  = receivedObject.value("Receiver").toArray();
         QJsonArray cipherMessage  = receivedObject.value("Message").toArray();

         QString sender = decrypt(cipherSender);
         QString receiver = decrypt(cipherReceiver);
         QString message = decrypt(cipherMessage);

         QMapIterator<QTcpSocket * , struct Client> iterator(connectedClients);
         while(iterator.hasNext()) {
             iterator.next();
             if(iterator.value().mail == receiver) {

                 iterator.key()->write(receivedData);
             }

         }
         QMapIterator<QPair<QString,QString>,QByteArray> iterator2(chatRooms);
         int found = 0;
         while(iterator2.hasNext()) {
             iterator2.next();
             if((iterator2.key().first == sender && iterator2.key().second == receiver) || (iterator2.key().first == receiver && iterator2.key().second == sender)) {
                 chatRooms[iterator2.key()].append((sender + " : " +message+"\n").toUtf8());
                 found++;
             }

         }
         if(found == 0) {
             QPair<QString,QString> pair;
             ui->listWidget->addItem(sender + " - " + receiver);
             pair.first = sender;
             pair.second = receiver;
             QByteArray privateMessage;
             privateMessage.append((sender + " : " + message+"\n").toUtf8());
             chatRooms.insert(pair,privateMessage);
         }



     }

     else if(type == Exit) {

         QString logOffDate = QDate::currentDate().toString("dd:MM:yy");
         QString logOffTime = QTime::currentTime().toString("hh:mm");

         QMapIterator<QTcpSocket * , struct Client> iterator(connectedClients);
         while(iterator.hasNext()) {
             iterator.next();
             if(iterator.key()->socketDescriptor() == socket->socketDescriptor()) {
                 break;
             }

         }


         QString activity;
         activity.insert(0,connectedClients.find(iterator.key()).value().mail);
         activity.insert(50,connectedClients.find(iterator.key()).value().loginDate);
         activity.insert(66,connectedClients.find(iterator.key()).value().loginTime);
         activity.insert(83,logOffDate);
         activity.insert(102,logOffTime);
         activity.append("\n");
         activityDuration.append(activity.toUtf8());
         ui->textBrowser->setTextColor(Qt::red);
         ui->textBrowser->append(connectedClients.find(iterator.key()).value().mail + " has logged off.");
         connectedClients.take(iterator.key());
         activeUsers--;
         ui->lcdNumber->display(activeUsers);

     }

     else if(type == ActiveClients) {
         QString activeClients = "";

         sentObject.insert("Type", ActiveClients);

         QMapIterator<QTcpSocket * , struct Client> iterator(connectedClients);
         while(iterator.hasNext()) {
             iterator.next();
             QString client = connectedClients.find(iterator.key()).value().mail;
             activeClients += client;
             if(iterator.hasNext()) {
                 activeClients += " ";
             }
         }

         QJsonArray cipherActiveClients = encrypt(activeClients);
         sentObject.insert("Message", cipherActiveClients);
         sentDoc.setObject(sentObject);
         QByteArray data = sentDoc.toJson();
         socket->write(data);
     }



}

void Widget::on_pushButton_5_clicked()
{
    QFile activityDurationFile;
    QFileDialog dialog;
    QString directory = dialog.getSaveFileName();
    activityDurationFile.setFileName(directory);
    activityDurationFile.open(QIODevice::WriteOnly | QFile::Append);
    QString header = "Mail Address                                 -    "
                     "Log in Date  - "
                     " Log in Time   -  "
                     "Log Off Date   -   "
                     "Log Off Time\n";
    activityDurationFile.write(header.toUtf8());
    activityDurationFile.write(activityDuration);
    activityDurationFile.close();
}


void Widget::on_pushButton_4_clicked()
{
    QFile activityDurationFile;
    QFileDialog dialog;
    QString directory = dialog.getSaveFileName();
    activityDurationFile.setFileName(directory);
    activityDurationFile.open(QIODevice::WriteOnly);
    activityDurationFile.write(groupChat);
    activityDurationFile.close();
}




void Widget::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void Widget::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Widget::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Widget::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Widget::on_pushButton_9_clicked()
{
   QMessageBox msgBox;
   if(!ui->lineEdit_2->text().isEmpty() && !ui->lineEdit_3->text().isEmpty() && !ui->lineEdit_4->text().isEmpty() && !ui->lineEdit_5->text().isEmpty()) {

       QString mail = ui->lineEdit_4->text();

       QSqlQuery query(this->db);
       query.prepare("select * from sigmoidchat where mail=:mail");
       query.bindValue(":mail",mail);
       query.exec();
       int size = query.size();


       if(size == 0) {

           QString name = ui->lineEdit_2->text();
           QString surname = ui->lineEdit_3->text();
           QString department = ui->lineEdit_5->text();

           query.prepare("insert into sigmoidchat(name, surname, mail, department, image, chatRegisterStatus) "
                         "VALUES (?, ?, ?, ? , ?, ?)");
           query.addBindValue(name);
           query.addBindValue(surname);
           query.addBindValue(mail);
           query.addBindValue(department);
           query.addBindValue(image);
           query.addBindValue(false);

           bool status = query.exec();


           if(status) {

               msgBox.setWindowTitle("!!!!!!!");
               msgBox.setText("You have added employee into database successfully.");
               msgBox.setIcon(QMessageBox::Information);
               msgBox.exec();
               ui->lineEdit_2->clear();
               ui->lineEdit_3->clear();
               ui->lineEdit_4->clear();
               ui->lineEdit_5->clear();
               ui->label_7->clear();
               ui->stackedWidget->setCurrentIndex(0);
           }


       }
       else {

           msgBox.setWindowTitle("!!!!!!!!!!!!!!!!");
           msgBox.setText("There is an employee who has same e-mail address.");
           msgBox.setIcon(QMessageBox::Critical);
           msgBox.exec();

       }
   }


  else {
       msgBox.setWindowTitle("!!!!!!!!!!!!!!!!");
       msgBox.setText("You have to fill blanks correctly");
       msgBox.setIcon(QMessageBox::Critical);
       msgBox.exec();
   }

}


void Widget::on_pushButton_8_clicked()
{
    QFile imageFile;
    QFileDialog dialog;
    QString imageFileAddress = dialog.getOpenFileName();
    imageFile.setFileName(imageFileAddress);
    imageFile.open(QIODevice::ReadOnly);
    image = imageFile.readAll();
    imageFile.close();
    QPixmap pixmapEmpImage;
    pixmapEmpImage.loadFromData(image);
    ui->label_7->setPixmap(pixmapEmpImage.scaled(ui->label_7->size()));
}

void Widget::changeColor()
{
    if(color == "White") {
        ui->pushButton->setStyleSheet("background-color : rgb(85, 255, 0)");
        color = "Green";
    }
    else {
        ui->pushButton->setStyleSheet("background-color : rgb(255, 255, 255)");
        color = "White";
    }
}



void Widget::on_pushButton_3_pressed()
{
    timer.stop();
    ui->pushButton->setStyleSheet("background-color : rgb(255, 255, 255)");
    color = "White";
    ui->pushButton_3->setStyleSheet("background-color : rgb(255, 0, 0)");
}


void Widget::on_pushButton_3_released()
{
    ui->pushButton_3->setStyleSheet("background-color : rgb(255, 255, 255)");
    server.close();
    imageServer.close();
}

void Widget::activated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::ActivationReason::DoubleClick) this->show();
}


void Widget::on_pushButton_2_clicked()
{
    QStringList parts = ui->listWidget->currentItem()->text().split(" - ");
    QMapIterator<QPair<QString,QString>,QByteArray> iterator(chatRooms);
    while(iterator.hasNext()) {
        iterator.next();
        if((iterator.key().first == parts.at(0) && iterator.key().second == parts.at(1)) || (iterator.key().first == parts.at(1) && iterator.key().second == parts.at(0))) {
           {
            QByteArray message = iterator.value();
            QFile oneTOoneChat;
            QFileDialog dialog;
            QString directory = dialog.getSaveFileName();
            oneTOoneChat.setFileName(directory);
            oneTOoneChat.open(QIODevice::WriteOnly);
            oneTOoneChat.write(message);
            oneTOoneChat.close();
            }}}

}

QJsonArray Widget::encrypt(QString message)
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

QString Widget::decrypt(QJsonArray cipher)
{
    QString plain;
    for(int j = 0 ; j < cipher.size() ; j++) {
        int result = 1;
        for(int i = 0 ; i < 2753 ; i++) {
          result = (result*cipher.at(j).toInt())%n;
        }
       plain.append(result);
    }
    return plain;
}
