/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label;
    QLineEdit *lineEdit;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QRadioButton *radioButton_9;
    QRadioButton *radioButton_10;
    QComboBox *comboBox;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLCDNumber *lcdNumber;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(498, 231);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(390, 110, 81, 31));
        QFont font;
        font.setPointSize(15);
        pushButton->setFont(font);
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(390, 150, 81, 31));
        pushButton_2->setFont(font);
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(390, 190, 81, 31));
        pushButton_3->setFont(font);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 150, 71, 16));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(110, 150, 181, 22));
        radioButton_6 = new QRadioButton(Widget);
        buttonGroup = new QButtonGroup(Widget);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButton_6);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));
        radioButton_6->setGeometry(QRect(350, 60, 89, 20));
        radioButton_7 = new QRadioButton(Widget);
        buttonGroup->addButton(radioButton_7);
        radioButton_7->setObjectName(QString::fromUtf8("radioButton_7"));
        radioButton_7->setGeometry(QRect(400, 10, 89, 20));
        radioButton_8 = new QRadioButton(Widget);
        buttonGroup->addButton(radioButton_8);
        radioButton_8->setObjectName(QString::fromUtf8("radioButton_8"));
        radioButton_8->setGeometry(QRect(400, 30, 89, 20));
        radioButton_9 = new QRadioButton(Widget);
        buttonGroup->addButton(radioButton_9);
        radioButton_9->setObjectName(QString::fromUtf8("radioButton_9"));
        radioButton_9->setGeometry(QRect(310, 10, 89, 20));
        radioButton_10 = new QRadioButton(Widget);
        buttonGroup->addButton(radioButton_10);
        radioButton_10->setObjectName(QString::fromUtf8("radioButton_10"));
        radioButton_10->setGeometry(QRect(310, 30, 89, 20));
        comboBox = new QComboBox(Widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(30, 20, 69, 21));
        pushButton_4 = new QPushButton(Widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(70, 60, 91, 31));
        pushButton_4->setFont(font);
        pushButton_5 = new QPushButton(Widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(110, 20, 91, 31));
        pushButton_5->setFont(font);
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(110, 180, 181, 41));
        QFont font2;
        font2.setPointSize(20);
        lcdNumber->setFont(font2);
        lcdNumber->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"background-color: rgb(0, 0, 0);"));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "START", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "PAUSE", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "STOP", nullptr));
        label->setText(QCoreApplication::translate("Widget", "File Name", nullptr));
        radioButton_6->setText(QCoreApplication::translate("Widget", "    48 KHz", nullptr));
        radioButton_7->setText(QCoreApplication::translate("Widget", "16 KHz", nullptr));
        radioButton_8->setText(QCoreApplication::translate("Widget", "44.1 KHz", nullptr));
        radioButton_9->setText(QCoreApplication::translate("Widget", "    8 KHz", nullptr));
        radioButton_10->setText(QCoreApplication::translate("Widget", "   32 KHz", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Widget", "Connect", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Widget", "Refresh", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
