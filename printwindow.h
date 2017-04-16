#ifndef PRINTWINDOW_H
#define PRINTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QTextBrowser>
#include <QLineEdit>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QKeyEvent>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "myserialport.h"

class PrintWindow : public QWidget
{
    Q_OBJECT
public:
     PrintWindow(QWidget *parent = 0);
    ~PrintWindow();

     bool getIsPrint();//是否正在打印

signals:
     void signalPrinting();

public slots:
    void slotRestCom();
    void slotConnect();
    void slotClear();

    void slotZeroPoint();
    void slotAddX();
    void slotSubX();
    void slotAddY();
    void slotSubY();
    void slotAddZ();
    void slotSubZ();
    void slotAddA();
    void slotAddB();
    void slotChangeAB(int value);
    void slotAddAB();

    void slotSendText();
    void slotLoad();
    void slotPrint();
    void slotPause();
    void slotStop();
    void slotClickStop(QStringList dataList);
    void slotPortSendData(QString data);
    void slotPortReceiveData(QStringList dataList);

    void slotPrinting();//打印

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    void initData();
    void initUI();
    void initConnect();

    void loadFile(const QString &fileName);//加载gcode文件
    QList<QString> removeComments(QString code);//删除空白与g-code的注释部分

private:

    QGroupBox *comGroup;
    QPushButton *restComButton;
    QPushButton *connectButton;
    QComboBox *comBox;
    QComboBox *baudRateBox;
    QPushButton *clearButton;

    QGroupBox *controlGroup;
    QPushButton *zeroPoinButton;
    QLabel *XLabel;
    QSpinBox *XBox;
    QPushButton *addXButton;
    QPushButton *subXButton;
    QLabel *YLabel;
    QSpinBox *YBox;
    QPushButton *addYButton;
    QPushButton *subYButton;
    QLabel *ZLabel;
    QSpinBox *ZBox;
    QPushButton *addZButton;
    QPushButton *subZButton;
    QLabel *ABLabel;
    QSpinBox *ABBox;
    QPushButton *addAButton;
    QPushButton *addBButton;
    QSpinBox *AandBBox;
    QLabel *AandBLabel;
    QPushButton *addABButton;

    QTextBrowser *receiveText;

    QGroupBox *sendGroup;
    QLabel *sendLabel;
    QLineEdit *sendText;
    QPushButton *sendButton;

    QTextBrowser *gcodeText;
    QGroupBox *printGroup;
    QProgressBar *printProgressBar;
    QPushButton *loadButton;
    QPushButton *printButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;

    QHBoxLayout *mainLayout;

    QList<QSerialPortInfo> portList;//串口信息列表
    MySerialPort *serialPort;//串口操作
    QString curDir;//包含文件名的绝对路径

    QString cmdStr;//当前指令
    int cmdN;//第几条指令
    int layerCount;//gcode层数
    QList<QString> gcodeList;

    bool isPrint;//是否正在打印
    bool isPause;//是否暂停打印
    int printNumber;//打印第一条指令
};

#endif // PRINTWINDOW_H
