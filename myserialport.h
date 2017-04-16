#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QStringList>

class MySerialPort : public QObject
{
    Q_OBJECT

public:
    MySerialPort(QObject *parent = 0);
    ~MySerialPort();

    bool connectPort(QString portName,int baudRate=115200);//连接串口
    bool closePort();//关闭串口
    bool getIsConnected();//串口是否打开
    bool send(QString cmd);//通过串口发送数据

signals:
    void signalDataSend(QString data);//串口发送数据后的信号
    void signalDataReceive(QStringList dataList);//接收到的数据

public slots:
    void slotPortReceive();

private:
    void init();

private:
    QStringList recvList;//接收的字符串
    bool isConnected;//串口是否打开
    QSerialPort *port;//串口
};

#endif // MYSERIALPORT_H
