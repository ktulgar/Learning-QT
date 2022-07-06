#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPixmap pixmapApp;
    QIcon iconApp;
    pixmapApp.load(":/resources/images/SignUpIn.png");
    iconApp.addPixmap(pixmapApp);
    QWidget::setWindowIcon(iconApp);
    QWidget::setWindowTitle("Sigmoid Chat Application");
    QWidget::setFixedSize(QSize(411,511));

    QPixmap pixmapSignUp;
    pixmapSignUp.load(":/resources/images/Sign_Up.png");
    ui->label->setPixmap(pixmapSignUp.scaled(ui->label->size()));

    QPixmap pixmapLogIn;
    pixmapLogIn.load(":/resources/images/Log_In.png");
    ui->label_9->setPixmap(pixmapLogIn.scaled(ui->label_9->size()));

    QPixmap pixmapBack;
    QIcon iconBack;
    pixmapBack.load(":/resources/images/back.png");
    iconBack.addPixmap(pixmapBack);
    ui->pushButton_5->setIcon(iconBack);
    ui->pushButton_5->setIconSize(ui->pushButton_5->size());

    ui->pushButton_6->setIcon(iconBack);
    ui->pushButton_6->setIconSize(ui->pushButton_6->size());

    QPixmap pixmapNext;
    QIcon iconNext;
    pixmapNext.load(":/resources/images/next.png");
    iconNext.addPixmap(pixmapNext);
    ui->pushButton_2->setIcon(iconNext);
    ui->pushButton_2->setIconSize(ui->pushButton_2->size());

    QIcon iconFirst;
    iconFirst.addPixmap(pixmapSignUp);
    ui->pushButton_3->setIcon(iconFirst);
    ui->pushButton_3->setIconSize(ui->pushButton_3->size());

    QIcon iconSecond;
    iconSecond.addPixmap(pixmapLogIn);
    ui->pushButton_4->setIcon(iconSecond);
    ui->pushButton_4->setIconSize(ui->pushButton_4->size());

    ui->pushButton->setIcon(iconNext);
    ui->pushButton->setIconSize(ui->pushButton->size());

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    ui->lineEdit_6->setEchoMode(QLineEdit::Password);

    ui->stackedWidget->setCurrentIndex(0);

    socket.connectToHost(QHostAddress("192.168.1.20"),777);
    imageSocket.connectToHost(QHostAddress("192.168.1.20"),2500);
    connect(&socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
    connect(&imageSocket,SIGNAL(readyRead()),this,SLOT(receiveImage()));

}

Widget::~Widget()
{
    delete ui;
}


void Widget::receiveMessage() {

     QByteArray data = socket.readAll();
     QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
     QJsonObject object = jsonDocument.object();

     int type = object.value("Type").toInt();

     if(type == NoRegistration) {
         QMessageBox msgBox;
         msgBox.setWindowTitle("!!! No Registration Found !!!");
         msgBox.setText("You did not register system before.\nPlease determine a password");
         msgBox.setIcon(QMessageBox::Critical);
         msgBox.exec();
         ui->stackedWidget->setCurrentIndex(1);
     }
     else if(type == NoEmploymentFound) {
         QMessageBox msgBox;
         msgBox.setWindowTitle("!!! No Employment Found !!!");
         msgBox.setText("It seems you don't work in this company");
         msgBox.setIcon(QMessageBox::Critical);
         msgBox.exec();
     }
     else if(type == SUCCESS_LOGIN) {
         userName = ui->lineEdit_4->text();
         chatScreen = new ChatScreen(&socket,&imageSocket,userName);
         close();
         chatScreen->show();
     }
     else if(type == SUCCESS_SIGNUP) {
         QMessageBox msgBox;
         msgBox.setWindowTitle("!!! You created password succesfully !!!");
         msgBox.setText("Now, try to log in chat application...");
         msgBox.setIcon(QMessageBox::Information);
         msgBox.exec();
         ui->stackedWidget->setCurrentIndex(1);
     }

     else if(type == WrongPassword) {
         QMessageBox msgBox;
         msgBox.setWindowTitle("!!!!!!");
         msgBox.setText("Your password or e-mail is wrong");
         msgBox.setIcon(QMessageBox::Critical);
         msgBox.exec();
     }
     else if(type == All) {
          QJsonArray cipherSender = object.value("Sender").toArray();
          QJsonArray cipherMessage = object.value("Message").toArray();

          QString sender = decrypt(cipherSender);
          QString message = decrypt(cipherMessage);

          chatScreen->ui->textBrowser->append(sender+" : "+message);
         }
     else if(type == ActiveClients) {
          QJsonArray cipherActiveClients = object.value("Message").toArray();
          QString activeClients = decrypt(cipherActiveClients);
          QStringList activeClientsList = activeClients.split(" ");
          chatScreen->ui->listWidget->clear();
             for(int i=0 ; i<activeClientsList.size() ; i++) {
                 chatScreen->ui->listWidget->addItem(activeClientsList.at(i));
             }
         }
     else if(type == Info) {

         QJsonArray cipherName = object.value("Name").toArray();
         QJsonArray cipherSurname = object.value("Surname").toArray();
         QJsonArray cipherDepartment = object.value("Department").toArray();

         QString name = decrypt(cipherName);
         QString surname = decrypt(cipherSurname);
         QString department = decrypt(cipherDepartment);

          chatScreen->ui->label_14->setText(name);
          chatScreen->ui->label_11->setText(surname);
          chatScreen->ui->label_13->setText(department);
         }

    else if(type == Private) {

         QJsonArray cipherSender = object.value("Sender").toArray();
         QJsonArray cipherMessage = object.value("Message").toArray();

         QString sender = decrypt(cipherSender);
         QString message = decrypt(cipherMessage);

         if(!chatScreen->isActiveWindow()) {
            chatScreen->systemTrayIcon->showMessage(sender,message,QSystemTrayIcon::MessageIcon::Information);
         }

          QMap<QString , PrivateChat *>::iterator iter = chatScreen->chatRooms.find(sender);
          if(iter != chatScreen->chatRooms.end()) {
              iter.value()->ui->textBrowser->append(sender + " : " + message);
          }
          else{
              PrivateChat *privateRoom = new PrivateChat(&socket,userName,sender);
              chatScreen->chatRooms.insert(sender,privateRoom);
              chatScreen->ui->tabWidget->insertTab(chatScreen->ui->tabWidget->count(),privateRoom,sender);
              privateRoom->ui->textBrowser->append(sender + " : " + message);
            }

        }
 }


void Widget::receiveImage() {

    QByteArray data = imageSocket.readAll();
    image.append(data);
    QString code = "*#%END%#*";
    int index = image.indexOf(code.toUtf8());
    if(index != -1){
         image = image.remove(index,code.size());
         QPixmap employeeImage;
         employeeImage.loadFromData(image);
         chatScreen->ui->label_12->setPixmap(employeeImage.scaled(chatScreen->ui->label_12->size()));
         image.clear();
         image.shrink_to_fit();
     }

}


void Widget::on_pushButton_2_clicked()
{
    QString userName = ui->lineEdit_4->text();
    QString password = ui->lineEdit_6->text();

    QJsonArray cipherUserName = encrypt(userName);
    QJsonArray cipherPassword = encrypt(password);

    QJsonObject jsonObject;
    jsonObject.insert("Type", SignIn);
    jsonObject.insert("User Name",cipherUserName);
    jsonObject.insert("Password",cipherPassword);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObject);
    QByteArray data = jsonDoc.toJson();

    if(socket.state() == QTcpSocket::ConnectedState) {
        socket.write(data);
    }

}

void Widget::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1 == 2) {
        ui->lineEdit_6->setEchoMode(QLineEdit::Normal);
    }
    else {
        ui->lineEdit_6->setEchoMode(QLineEdit::Password);
    }
}


void Widget::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2) {
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
        ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
    }
    else {
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
        ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    }
}


void Widget::on_pushButton_clicked()
{
    QString userName = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString repeatedPassword = ui->lineEdit_3->text();

    if(password != repeatedPassword){
        QMessageBox msgBox;
        msgBox.setWindowTitle("!!! Check your passwords !!!");
        msgBox.setText("Passwords do not match");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
    else{
        QJsonArray cipherUserName = encrypt(userName);
        QJsonArray cipherPassword = encrypt(password);

        QJsonObject jsonObject;
        jsonObject.insert("Type", SignUp);
        jsonObject.insert("User Name",cipherUserName);
        jsonObject.insert("Password",cipherPassword);

        QJsonDocument jsonDoc;
        jsonDoc.setObject(jsonObject);
        QByteArray data = jsonDoc.toJson();

        if(socket.state() == QTcpSocket::ConnectedState) {
             socket.write(data);
        }
    }
}

void Widget::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void Widget::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Widget::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Widget::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
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
