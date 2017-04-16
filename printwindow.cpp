#pragma execution_character_set("utf-8")
#include "printwindow.h"
#include <QDebug>

PrintWindow::PrintWindow(QWidget *parent) : QWidget(parent)
{
    initData();
    initUI();
    initConnect();
    slotRestCom();
}

PrintWindow::~PrintWindow()
{
    if(serialPort)
    {
        delete serialPort;
        serialPort=NULL;
    }
}

void PrintWindow::keyPressEvent(QKeyEvent *e)
{
    if(sendText->hasFocus())
    {
        if(e->key()==Qt::Key_Enter||e->key()==Qt::Key_Return)
        {
            slotSendText();
        }
    }
}

//是否正在打印
bool PrintWindow::getIsPrint()
{
    return isPrint;
}

void PrintWindow::slotRestCom()
{
    QSerialPortInfo portInfo;//串口信息
    portList = portInfo.availablePorts();
    comBox->clear();
    for(int i=0;i<portList.size();i++)
    {
        comBox->addItem(portList[i].portName());
    }
    if(comBox->count()<=0)
    {
        connectButton->setEnabled(false);
    }
    else
    {
        connectButton->setEnabled(true);
    }
}

void PrintWindow::slotConnect()
{
    if(serialPort->getIsConnected())
    {
        //disconnect
        serialPort->closePort();
        connectButton->setText(tr("连接"));
        controlGroup->setEnabled(false);
        sendGroup->setEnabled(false);
        printGroup->setEnabled(false);
    }
    else
    {
        if(serialPort->connectPort(comBox->currentText(),baudRateBox->currentData().toInt()))
        {
            //successfully connected
            controlGroup->setEnabled(true);
            sendGroup->setEnabled(true);
            printGroup->setEnabled(true);
            loadButton->setEnabled(true);
            printButton->setEnabled(false);
            pauseButton->setEnabled(false);
            stopButton->setEnabled(false);
            connectButton->setText(tr("断开"));
            receiveText->clear();
            gcodeText->clear();
            gcodeList.clear();
            sendText->clear();
            QString str="N"+QString::number(cmdN)+" "+QString("M999")+" ";
            cmdStr=str+"*"+QString::number(str.length());
            serialPort->send(cmdStr);
        }
        else
        {
            QMessageBox::information(this,tr("串口操作"),tr("串口打开失败！"));
        }
    }
}

void PrintWindow::slotClear()
{
    cmdN = 0;
    receiveText->clear();
}

void PrintWindow::slotZeroPoint()
{
    QString str="N"+QString::number(cmdN)+" "+QString("G28")+" ";
    cmdStr=str+"*"+QString::number(str.length());
    serialPort->send(cmdStr);
    controlGroup->setEnabled(false);
    sendGroup->setEnabled(false);
    printGroup->setEnabled(false);
}

void PrintWindow::slotAddX()
{
    QString cmdLine;
    float XLength = XBox->value();
    cmdLine.sprintf("G2 X%.2f F%d", XLength, 2000);
    QString str="N"+QString::number(cmdN)+" "+cmdLine + " ";
    cmdStr=str+"*"+QString::number(str.length());
    serialPort->send(cmdStr);
    controlGroup->setEnabled(false);
    sendGroup->setEnabled(false);
    printGroup->setEnabled(false);
}

void PrintWindow::slotSubX()
{
    QString cmdLine;
    float XLength = XBox->value();
    cmdLine.sprintf("G2 X-%.2f F%d", XLength, 2000);
    QString str="N"+QString::number(cmdN)+" "+cmdLine + " ";
    cmdStr=str+"*"+QString::number(str.length());
    serialPort->send(cmdStr);
    controlGroup->setEnabled(false);
    sendGroup->setEnabled(false);
    printGroup->setEnabled(false);
}

void PrintWindow::slotAddY()
{
    QString cmdLine;
    float YLength = YBox->value();
    cmdLine.sprintf("G2 Y%.2f F%d", YLength, 2000);
    QString str="N"+QString::number(cmdN)+" "+cmdLine + " ";
    cmdStr=str+"*"+QString::number(str.length());
    serialPort->send(cmdStr);
    controlGroup->setEnabled(false);
    sendGroup->setEnabled(false);
    printGroup->setEnabled(false);
}

void PrintWindow::slotSubY()
{
    QString cmdLine;
    float YLength = YBox->value();
    cmdLine.sprintf("G2 Y-%.2f F%d", YLength, 2000);
    QString str="N"+QString::number(cmdN)+" "+cmdLine + " ";
    cmdStr=str+"*"+QString::number(str.length());
    serialPort->send(cmdStr);
    controlGroup->setEnabled(false);
    sendGroup->setEnabled(false);
    printGroup->setEnabled(false);
}

void PrintWindow::slotAddZ()
{
    QString cmdLine;
    float ZLength = ZBox->value();
    cmdLine.sprintf("G2 Z%.2f F%d", ZLength, 1000);
    QString str="N"+QString::number(cmdN)+" "+cmdLine + " ";
    cmdStr=str+"*"+QString::number(str.length());
    serialPort->send(cmdStr);
    controlGroup->setEnabled(false);
    sendGroup->setEnabled(false);
    printGroup->setEnabled(false);
}

void PrintWindow::slotSubZ()
{
    QString cmdLine;
    float ZLength = ZBox->value();
    cmdLine.sprintf("G2 Z-%.2f F%d", ZLength, 1000);
    QString str="N"+QString::number(cmdN)+" "+cmdLine + " ";
    cmdStr=str+"*"+QString::number(str.length());
    serialPort->send(cmdStr);
    controlGroup->setEnabled(false);
    sendGroup->setEnabled(false);
    printGroup->setEnabled(false);
}

void PrintWindow::slotAddA()
{
    int ALength = ABBox->value();
    QString str="N"+QString::number(cmdN)+" "+QString("G1 A255 B0 S%1 ").arg(ALength);
    cmdStr=str+"*"+QString::number(str.length());
    serialPort->send(cmdStr);
    controlGroup->setEnabled(false);
    sendGroup->setEnabled(false);
    printGroup->setEnabled(false);
}

void PrintWindow::slotAddB()
{
    int BLength = ABBox->value();
    QString str="N"+QString::number(cmdN)+" "+QString("G1 A0 B255 S%1 ").arg(BLength);
    cmdStr=str+"*"+QString::number(str.length());
    serialPort->send(cmdStr);
    controlGroup->setEnabled(false);
    sendGroup->setEnabled(false);
    printGroup->setEnabled(false);
}

void PrintWindow::slotChangeAB(int value)
{
    AandBLabel->setText(tr("A:B = %1:%2").arg(value).arg(255 - value));
}

void PrintWindow::slotAddAB()
{
    int BALength = ABBox->value();
    int AValue = AandBBox->value();
    int BValue = 255 - AValue;
    QString str="N"+QString::number(cmdN)+" "+QString("G1 A%1 B%2 S%3 ").arg(AValue).arg(BValue).arg(BALength);
    cmdStr=str+"*"+QString::number(str.length());
    serialPort->send(cmdStr);
    controlGroup->setEnabled(false);
    sendGroup->setEnabled(false);
    printGroup->setEnabled(false);
}

void PrintWindow::slotSendText()
{
    if(!sendText->text().trimmed().isEmpty())
    {
        QString cmd=sendText->text().trimmed();
        QString str="N"+QString::number(cmdN)+" "+cmd+" ";
        cmdStr=str+"*"+QString::number(str.length());
        if(!serialPort->send(cmdStr))
        {
            QString str=QString("SEND:ERROR");
            receiveText->append(str);
        }
        else
        {
            controlGroup->setEnabled(false);
            sendGroup->setEnabled(false);
            printGroup->setEnabled(false);
        }
    }
}

void PrintWindow::slotLoad()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open File"),curDir,tr("GCode Files(*.gcode)"));
    if (!fileName.trimmed().isEmpty())
    {
        loadFile(fileName);
    }
}

void PrintWindow::slotPrint()
{
    isPrint=true;
    printNumber=0;
    comGroup->setEnabled(false);
    controlGroup->setEnabled(false);
    sendGroup->setEnabled(false);
    loadButton->setEnabled(false);
    printButton->setEnabled(false);
    pauseButton->setEnabled(true);
    stopButton->setEnabled(true);
    printProgressBar->setRange(printNumber, gcodeList.size());
    emit signalPrinting();
}

void PrintWindow::slotPause()
{
    if(!isPause)
    {
        isPause=true;
        pauseButton->setText(tr("继续"));
    }
    else
    {
        isPause=false;
        pauseButton->setText(tr("暂停"));
        emit signalPrinting();
    }
}

void PrintWindow::slotStop()
{
    isPrint=false;
    isPause=false;
    printNumber = 0;
    pauseButton->setText(tr("暂停"));
    printProgressBar->setValue(printNumber);
    connect(serialPort, &MySerialPort::signalDataReceive, this, &PrintWindow::slotClickStop);
}

void PrintWindow::slotClickStop(QStringList dataList)
{
    emit signalPrinting();
    disconnect(serialPort, &MySerialPort::signalDataReceive, this, &PrintWindow::slotClickStop);
}

void PrintWindow::slotPortSendData(QString data)
{
    QString str=QString("SEND:")+data;
    receiveText->append(str);
}

//接收串口传来的数据,显示在接收窗口中
void PrintWindow::slotPortReceiveData(QStringList dataList)
{
    if(dataList.size()>0)
    {
        foreach(QString str,dataList)
        {
            receiveText->append(QString("RECV:%1").arg(str));
        }
        if(dataList[0].startsWith("ok"))
        {
            cmdN++;
            if(isPrint)
            {
                emit signalPrinting();
            }
        }
        if(dataList[0].startsWith("ret"))
        {
            serialPort->send(cmdStr);
        }
        else
        {
            if(!isPrint)
            {
                sendText->setFocus();
                sendGroup->setEnabled(true);
                controlGroup->setEnabled(true);
                printGroup->setEnabled(true);
            }
        }
    }
}

void PrintWindow::slotPrinting()
{
    if(isPrint)
    {
        if(!isPause)
        {
            if(printNumber<gcodeList.size())
            {
                QString str="N"+QString::number(cmdN)+" "+gcodeList[printNumber]+" ";
                cmdStr=str+"*"+QString::number(str.length());
                if(!serialPort->send(cmdStr))
                {
                    QString str=QString("SEND:ERROR");
                    receiveText->append(str);
                }
                else
                {
                    printNumber++;
                }
            }
            else
            {
                isPrint=false;
                comGroup->setEnabled(true);
                controlGroup->setEnabled(true);
                sendGroup->setEnabled(true);
                loadButton->setEnabled(true);
                printButton->setEnabled(true);
                pauseButton->setEnabled(false);
                stopButton->setEnabled(false);
            }
        }
    }
    else
    {
        QString str="N"+QString::number(cmdN)+" "+QString("M18")+" ";
        cmdStr=str+"*"+QString::number(str.length());
        serialPort->send(cmdStr);
        comGroup->setEnabled(true);
        controlGroup->setEnabled(true);
        sendGroup->setEnabled(true);
        loadButton->setEnabled(true);
        printButton->setEnabled(true);
        pauseButton->setEnabled(false);
        stopButton->setEnabled(false);
    }
    printProgressBar->setValue(printNumber);
}

void PrintWindow::loadFile(const QString &fileName)
{
    qDebug()<<"loading file: "<<fileName;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Print3D"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
    gcodeText->clear();
    gcodeList.clear();
    //返回包含文件名的绝对路径
    //curDir = QFileInfo(fileName).absoluteFilePath();
    //返回文件的绝对路径，不包含文件名
    curDir=QFileInfo(fileName).absolutePath();

    QString code = file.readAll();
    gcodeText->setText(code);
    gcodeList=removeComments(code);
    //qDebug()<<gcodeList;
    if(gcodeList.size()>0)
    {
        printButton->setEnabled(true);
    }
}

//删除空白与g-code的注释部分
QList<QString> PrintWindow::removeComments(QString code)
{
    QList<QString> codeList;
    QStringList tempList;
    codeList.clear();
    tempList=code.split("\n");
    for(int loop=0;loop<tempList.size();loop++)
    {
        QString temp=tempList.at(loop);
        if(!temp.trimmed().isEmpty()&&!temp.trimmed().startsWith(";"))
        {
            codeList.append(temp.trimmed());
        }
    }
    return codeList;
}

void PrintWindow::initData()
{
    serialPort=new MySerialPort();
    isPrint=false;
    curDir=".";
    layerCount=0;
    gcodeList.clear();
    cmdN=0;
    cmdStr="";

    isPrint=false;
    isPause=false;
    printNumber=0;
}

void PrintWindow::initUI()
{
    QVBoxLayout *leftLayout=new QVBoxLayout();

    comGroup=new QGroupBox(tr("串口"));
    QHBoxLayout *leftTopLayout=new QHBoxLayout();
    leftTopLayout->setSpacing(20);
    restComButton=new QPushButton(tr("串口"));
    baudRateBox=new QComboBox();//波特率
    baudRateBox->addItem(tr("4800"),4800);
    baudRateBox->addItem(tr("9600"),9600);
    baudRateBox->addItem(tr("19200"),19200);
    baudRateBox->addItem(tr("38400"),38400);
    baudRateBox->addItem(tr("57600"),57600);
    baudRateBox->addItem(tr("115200"),115200);
    comBox=new QComboBox();
    connectButton=new QPushButton(tr("连接"));
    clearButton = new QPushButton(tr("清空"));
    leftTopLayout->addWidget(restComButton);
    leftTopLayout->addWidget(baudRateBox);
    leftTopLayout->addWidget(comBox);
    leftTopLayout->addWidget(connectButton);
    leftTopLayout -> addWidget(clearButton);
    comGroup->setLayout(leftTopLayout);

    controlGroup= new QGroupBox(tr("控制面板"));
    QGridLayout *leftCTopLayout=new QGridLayout();
    zeroPoinButton = new QPushButton(tr("回归原点"));

    XLabel = new QLabel(tr("X移动:"));
    XBox = new QSpinBox();
    XBox->setSuffix(tr("mm"));
    XBox->setSingleStep(5);
    XBox->setMinimum(1);
    XBox->setMaximum(100);
    XBox->setValue(10);
    addXButton = new QPushButton(tr("+X"));
    subXButton = new QPushButton(tr("-X"));

    YLabel = new QLabel(tr("Y移动:"));
    YBox = new QSpinBox();
    YBox->setSuffix(tr("mm"));
    YBox->setSingleStep(5);
    YBox->setMinimum(1);
    YBox->setMaximum(100);
    YBox->setValue(10);
    addYButton = new QPushButton(tr("+Y"));
    subYButton = new QPushButton(tr("-Y"));

    ZLabel = new QLabel(tr("Z移动:"));
    ZBox = new QSpinBox();
    ZBox->setSuffix(tr("mm"));
    ZBox->setSingleStep(5);
    ZBox->setMinimum(1);
    ZBox->setMaximum(100);
    ZBox->setValue(10);
    addZButton = new QPushButton(tr("+Z"));
    subZButton = new QPushButton(tr("-Z"));

    ABLabel = new QLabel(tr("AB吐丝:"));
    ABBox = new QSpinBox();
    ABBox->setSuffix(tr("mm"));
    ABBox->setSingleStep(100);
    ABBox->setMinimum(10);
    ABBox->setMaximum(10000);
    ABBox->setValue(100);
    addAButton = new QPushButton(tr("A吐丝"));
    addBButton = new QPushButton(tr("B吐丝"));
    AandBBox = new QSpinBox();
    AandBBox->setSingleStep(10);
    AandBBox->setMinimum(0);
    AandBBox->setMaximum(255);
    AandBBox->setValue(0);
    AandBLabel = new QLabel(tr("A:B = 0:255"));
    AandBLabel->setAlignment(Qt::AlignCenter);
    addABButton = new QPushButton(tr("AB同时吐丝"));

    leftCTopLayout->addWidget(zeroPoinButton, 0, 1, 1, 2);
    leftCTopLayout->addWidget(XLabel, 1, 0);
    leftCTopLayout->addWidget(XBox, 1, 1);
    leftCTopLayout->addWidget(addXButton, 1, 2);
    leftCTopLayout->addWidget(subXButton, 1, 3);
    leftCTopLayout->addWidget(YLabel, 2, 0);
    leftCTopLayout->addWidget(YBox, 2, 1);
    leftCTopLayout->addWidget(addYButton, 2, 2);
    leftCTopLayout->addWidget(subYButton, 2, 3);
    leftCTopLayout->addWidget(ZLabel, 3, 0);
    leftCTopLayout->addWidget(ZBox, 3, 1);
    leftCTopLayout->addWidget(addZButton, 3, 2);
    leftCTopLayout->addWidget(subZButton, 3, 3);
    leftCTopLayout->addWidget(ABLabel, 4, 0);
    leftCTopLayout->addWidget(ABBox, 4, 1);
    leftCTopLayout->addWidget(addAButton, 4, 2);
    leftCTopLayout->addWidget(addBButton, 4, 3);
    leftCTopLayout->addWidget(AandBBox, 5, 1);
    leftCTopLayout->addWidget(AandBLabel, 5, 2);
    leftCTopLayout->addWidget(addABButton, 5, 3);
    controlGroup->setLayout(leftCTopLayout);
    controlGroup->setEnabled(false);

    receiveText= new QTextBrowser();
    receiveText->setReadOnly(true);

    QHBoxLayout *leftBottomLayout=new QHBoxLayout();
    sendGroup = new QGroupBox(tr("发送指令"));
    sendLabel=new QLabel(tr("指令:"));
    sendText=new QLineEdit();
    sendButton=new QPushButton(tr("发送"));
    leftBottomLayout->addWidget(sendLabel);
    leftBottomLayout->addWidget(sendText);
    leftBottomLayout->addWidget(sendButton);
    sendGroup->setLayout(leftBottomLayout);
    sendGroup ->setEnabled(false);

    leftLayout->addWidget(comGroup);
    leftLayout->addWidget(controlGroup);
    leftLayout->addWidget(receiveText);
    leftLayout->addWidget(sendGroup);

    QVBoxLayout *rightLayout=new QVBoxLayout();
    gcodeText=new QTextBrowser();
    gcodeText->setReadOnly(true);

    QVBoxLayout *rightBottomLayoutMain = new QVBoxLayout();
    QHBoxLayout *rightBottomLayout=new QHBoxLayout();
    printGroup = new QGroupBox(tr("打印"));
    printProgressBar = new QProgressBar();
    printProgressBar->setValue(printNumber);
    rightBottomLayout->setSpacing(20);
    loadButton=new QPushButton(tr("打开"));
    printButton=new QPushButton(tr("打印"));
    pauseButton=new QPushButton(tr("暂停"));
    stopButton=new QPushButton(tr("停止"));
    rightBottomLayout->addWidget(loadButton);
    rightBottomLayout->addWidget(printButton);
    rightBottomLayout->addWidget(pauseButton);
    rightBottomLayout->addWidget(stopButton);
    loadButton->setEnabled(false);
    printButton->setEnabled(false);
    pauseButton->setEnabled(false);
    stopButton->setEnabled(false);
    rightBottomLayoutMain->addWidget(printProgressBar);
    rightBottomLayoutMain->addLayout(rightBottomLayout);
    printGroup->setLayout(rightBottomLayoutMain);

    rightLayout->addWidget(gcodeText);
    rightLayout->addWidget(printGroup);

    mainLayout=new QHBoxLayout();
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setMargin(10); //设置这个对话框的边距
    mainLayout->setSpacing(10);  //设置各个控件之间的边距
    this->setLayout(mainLayout);
    //this->setMaximumSize(700,520);
    this->setMinimumSize(550,650);
    this->setWindowTitle(tr("打印gcode"));
}

void PrintWindow::initConnect()
{
    connect(restComButton,&QPushButton::clicked,this,&PrintWindow::slotRestCom);
    connect(connectButton,&QPushButton::clicked,this,&PrintWindow::slotConnect);
    connect(clearButton, &QPushButton::clicked, this, &PrintWindow::slotClear);

    connect(zeroPoinButton, &QPushButton::clicked, this, &PrintWindow::slotZeroPoint);
    connect(addXButton, &QPushButton::clicked, this, &PrintWindow::slotAddX);
    connect(subXButton, &QPushButton::clicked, this, &PrintWindow::slotSubX);
    connect(addYButton, &QPushButton::clicked, this, &PrintWindow::slotAddY);
    connect(subYButton, &QPushButton::clicked, this, &PrintWindow::slotSubY);
    connect(addZButton, &QPushButton::clicked, this, &PrintWindow::slotAddZ);
    connect(subZButton, &QPushButton::clicked, this, &PrintWindow::slotSubZ);
    connect(addAButton, &QPushButton::clicked, this, &PrintWindow::slotAddA);
    connect(addBButton, &QPushButton::clicked, this, &PrintWindow::slotAddB);
    connect(AandBBox, static_cast< void (QSpinBox::*)(int) > (&QSpinBox::valueChanged),
            this, &PrintWindow::slotChangeAB);
    connect(addABButton, &QPushButton::clicked, this, &PrintWindow::slotAddAB);

    connect(sendButton,&QPushButton::clicked,this,&PrintWindow::slotSendText);

    connect(loadButton,&QPushButton::clicked,this,&PrintWindow::slotLoad);
    connect(printButton,&QPushButton::clicked,this,&PrintWindow::slotPrint);
    connect(pauseButton,&QPushButton::clicked,this,&PrintWindow::slotPause);
    connect(stopButton,&QPushButton::clicked,this,&PrintWindow::slotStop);

    connect(serialPort,&MySerialPort::signalDataSend,this,&PrintWindow::slotPortSendData);
    connect(serialPort,&MySerialPort::signalDataReceive,this,&PrintWindow::slotPortReceiveData);
    connect(this,&PrintWindow::signalPrinting,this,&PrintWindow::slotPrinting);
}
