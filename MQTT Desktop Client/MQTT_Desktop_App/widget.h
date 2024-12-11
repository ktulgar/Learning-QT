#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "./ui_widget.h"
#include <QPixmap>
#include <QIcon>
#include "qdebug.h"
#include <QTcpSocket>
#include <QtMqtt/QMqttClient>
#include <QMqttMessage>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void messageReceived(QMqttMessage);
    void stateChanged(QMqttClient::ClientState state);
    void on_pushButton_10_clicked();
    void on_horizontalSlider_sliderReleased();

private:
    Ui::Widget *ui;
    QPixmap pixmapOffRed;
    QPixmap pixmapOffGreen;
    QPixmap pixmapOffYellow;
    QPixmap pixmapOnRed;
    QPixmap pixmapOnGreen;
    QPixmap pixmapOnYellow;
    QIcon iconOffRed;
    QIcon iconOffGreen;
    QIcon iconOffYellow;
    QIcon iconOnRed;
    QIcon iconOnGreen;
    QIcon iconOnYellow;
    bool off_button_1 = true;
    bool off_button_2 = true;
    bool off_button_3 = true;
    QMqttClient m_client;
};
#endif // WIDGET_H
