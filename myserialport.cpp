#include "myserialport.h"
#include <QDebug>

MySerialPort::MySerialPort(QObject *parent) : QObject(parent)
{
    init();
}

MySerialPort::~MySerialPort()
{
    closePort();
}

//接收串口传来的数据,显示在接收窗口中
void MySerialPort::slotPortReceive()
{
    //QString line = serialPort->port->readLine(1024);
    QString line=port->readAll();
    recvList.append(line);
    qDebug()<<"recv:"<<line<<endl;
    if(line.endsWith("\n"))
    {
        QString recvData=recvList.join("");
        QStringList strList=recvData.split("\n",QString::SkipEmptyParts);
        port->flush();
        if(strList.size()>0)
        {
            emit signalDataReceive(strList);
        }
        recvList.clear();
    }
}

//通过串口发送数据
bool MySerialPort::send(QString cmd)
{
    if(isConnected)
    {
        port->flush();
        if(cmd[cmd.size()-1] != '\n')
            cmd.append("\n");
        //qDebug()<<"Sending: " + cmd.toUtf8();
        port->write((const char*)cmd.toLatin1(),cmd.length());
    }
    else
    {
        emit signalDataSend(port->errorString()+QString(" port is not open"));
        return false;
    }
    cmd.chop(1);//截掉最后的1个字符
    emit signalDataSend(cmd);
    return true;
}

//连接串口
bool MySerialPort::connectPort(QString portName,int baudRate)
{
    port->setPortName(portName);
    port->open(QIODevice::ReadWrite); //we open the port
    if(!port->isOpen())
    {
        isConnected=false;
        return false;
    }

    //we set the port properties
    //波特率
    port->setBaudRate(baudRate);//modify the port settings on your own
    port->setFlowControl(QSerialPort::NoFlowControl);
    //奇偶校验
    port->setParity(QSerialPort::NoParity);
    port->setDataBits(QSerialPort::Data8);
    port->setStopBits(QSerialPort::OneStop);
    port->setReadBufferSize(1024);
    isConnected = true;
    if(isConnected)
    {
        connect(port,&QSerialPort::readyRead,this,&MySerialPort::slotPortReceive);
    }
    recvList.clear();
    return true;
}

//关闭串口
bool MySerialPort::closePort()
{
    port->close();
    isConnected = false;
    if(!isConnected)
    {
        disconnect(port,&QSerialPort::readyRead,this,&MySerialPort::slotPortReceive);
    }
    return true;
}

//串口是否打开
bool MySerialPort::getIsConnected()
{
    return isConnected;
}

void MySerialPort::init()
{
    port = new QSerialPort();
    isConnected = false;
    recvList.clear();
}
