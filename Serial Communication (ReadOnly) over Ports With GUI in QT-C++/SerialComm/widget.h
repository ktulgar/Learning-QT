#ifndef WIDGET_H
#define WIDGET_H

#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort>
#include <QCheckBox>
#include <QWidget>
#include <QSize>
#include <QList>

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
    void on_connect_clicked();
    void read(void);
    void on_disConnect_clicked();
    void on_refreshComs_clicked();

private:
    Ui::Widget *ui;
    QSerialPort *serialPort;
    QSerialPortInfo info;
    QList<QSerialPortInfo> ports;
    QList<QString> stringPorts;
    QString buffer;
    QString code;
    void configure(void);
    void buttonConnect(void);
    void buttonDisconnect(void);

};
#endif // WIDGET_H
