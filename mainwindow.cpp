#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include "gcode.h"
#include "gcodeparameterwindow.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
    createToolBars();
    initUI();//初始化UI
    initData();//初始化化数据
    initConnect();
}

MainWindow::~MainWindow()
{
    if(imageProcess)
    {
        delete imageProcess;
        imageProcess=NULL;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(printWindow->getIsPrint())
    {
        QMessageBox::information(this, tr("退出程序"),QString(tr("警告：打印设备正在打印，请先停止打印设备，再退出！")));
        event->ignore();
    }
    else
    {
        printWindow->deleteLater();
        event->accept();
    }
}

void MainWindow::saveAct()
{
    QString path = saveCurDir + "/untitled.png";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Picture"),path,tr("Image Files (*.png *.jpg *.bmp)"));
    if(!fileName.trimmed().isEmpty())
    {
        //返回包含文件名的绝对路径
        //saveCurDir = QFileInfo(fileName).absoluteFilePath();
        //返回文件的绝对路径，不包含文件名
        saveCurDir = QFileInfo(fileName).absolutePath();
        if (!pixmap.save(fileName))
        {
            QMessageBox::information(this, "Error Saving Picture","Could not save the image");
        }
    }
}

void MainWindow::loadAct()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open Picture"), loadCurDir, tr("Image Files (*.png *.jpg *.bmp)"));
    if(!fileName.trimmed().isEmpty())
    {
        imageProcess->clearImage();
        //返回包含文件名的绝对路径
        //loadCurDir = QFileInfo(fileName).absoluteFilePath();
        //返回文件的绝对路径，不包含文件名
        loadCurDir = QFileInfo(fileName).absolutePath();
        bool success = pixmap.load(fileName);
        int code=imageProcess->readIamge(fileName);
        if(success&&code==0)
        {
            imageWidth=pixmap.width();
            imageHeight=pixmap.height();
            labelImage->resize(imageWidth,imageHeight);
            labelImage->setPixmap(pixmap);
        }
    }
}

//新建画布
void MainWindow::newAct()
{

}

//保存Gcode代码
void MainWindow::saveGcodeAct()
{
    QString path = saveCurDir + "/untitled.gcode";
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save Gcode"),path,"G-code files(*.gcode)");
    GCode code;
    std::vector<std::vector<int> > vectorData;
    bool isBack=false;
    GCodeParameterWindow *paramterWindow = new GCodeParameterWindow(this);
    paramterWindow->setGcodeParameter(paramter);
    if(!fileName.trimmed().isEmpty())
    {
        if(paramterWindow->exec() == QDialog::Accepted)
        {
            paramter = paramterWindow->getGcodeParameter();
            code.setParameter(paramter);
            //返回包含文件名的绝对路径
            //saveCurDir = QFileInfo(fileName).absoluteFilePath();
            //返回文件的绝对路径，不包含文件名
            saveCurDir = QFileInfo(fileName).absolutePath();
            vectorData=imageProcess->getGrayPixel();
            if(vectorData.size()>0)
            {
                code.addGcodeHead((int)vectorData.size());
                for(int loop=0;loop<(int)vectorData.size();loop++)
                {
                    std::vector<int> layerData=vectorData[loop];
                    qDebug()<<layerData.size();
                    code.addGcodeLayer(layerData,loop);
                    isBack=!isBack;
                }
                code.addGcodeEnd();
                if(!code.printFile(fileName))
                {
                    QMessageBox::information(this,tr("保存gcode数据"),tr("保存gcode数据失败!"));
                    return;
                }
            }
            else
            {
                QMessageBox::information(this,tr("保存gcode数据"),tr("没有数据可以保存"));
                return;
            }
        }
        paramterWindow->deleteLater();
    }
}

//打印Gcode文件
void MainWindow::printGcodeAct()
{
    printWindow->show();
}

//转换为灰度图
void MainWindow::cvtGrayAct()
{
    QImage img;
    imageProcess->convertImage(0);
    img=imageProcess->getConvertImage(0);
    pixmap=QPixmap::fromImage(img);
    imageWidth=pixmap.width();
    imageHeight=pixmap.height();
    labelImage->resize(imageWidth,imageHeight);
    labelImage->setPixmap(pixmap);
}

void MainWindow::aboutAct()
{
    QMessageBox::about(this, tr("About 3D Print"),tr("3D打印机控制软件1.0"));
}

void MainWindow::createActions()
{
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);

    loadAction = new QAction(tr("&Open..."), this);
    loadAction->setShortcuts(QKeySequence::Open);

    saveAction = new QAction(tr("&Save As Picture"), this);
    saveAction->setShortcuts(QKeySequence::SaveAs);

    newAction=new QAction(tr("&New canvas"),this);
    newAction->setShortcuts(QKeySequence::New);

    saveGcodeAction=new QAction(tr("&Save As GCode"),this);//保存为Gcode代码
    saveGcodeAction->setShortcut(tr("Ctrl+G"));

    printGcodeAction=new QAction(tr("&Print Gcode"),this);//打印Gcode文件
    printGcodeAction->setShortcut(tr("Ctrl+P"));

    cvtGrayAction=new QAction(tr("转换为灰度图"),this);//转换为灰度图
    cvtGrayAction->setShortcut(tr("Ctrl+C"));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(loadAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveGcodeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(printGcodeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu=menuBar()->addMenu(tr("&Edit"));//编辑菜单
    editMenu->addAction(cvtGrayAction);

    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
}

//创造工具栏
void MainWindow::createToolBars()
{
    fileTool=addToolBar(tr("File"));
    fileTool->addAction(loadAction);
    fileTool->addAction(saveGcodeAction);
    fileTool->addAction(printGcodeAction);
}

//初始化数据
void MainWindow::initData()
{
    fileName="";
    imageWidth=0;
    imageHeight=0;
    imageProcess=new ImageProcess;
    loadCurDir = ".";//包含文件名的绝对路径
    saveCurDir = ".";

    paramter.setXoffset(16.0f);
    paramter.setYoffset(10.0f);
    paramter.setYendset(250.0f);
    paramter.setZoffset(0.0f);
    paramter.setXYfeedrate(2000);
    paramter.setXYmaxFeedrate(5000);
    paramter.setZfeedrate(1000);
    paramter.setABfeedrate(2000);
    paramter.setXwidth(1.4f);
    paramter.setZheight(1.4f);
}

//初始化UI
void MainWindow::initUI()
{
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setAlignment(Qt::AlignCenter);
    labelImage = new QLabel();
    labelImage->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(labelImage);
    setCentralWidget(scrollArea);
    //this->setMaximumSize(800,600);
    this->setMinimumSize(800,600);
    this->setWindowTitle(tr("3D Print"));

    printWindow=new PrintWindow();
}

void MainWindow::initConnect()
{
    connect(exitAction, SIGNAL(triggered()),this, SLOT(close()));
    connect(loadAction, SIGNAL(triggered()),this, SLOT(loadAct()));
    connect(saveAction, SIGNAL(triggered()),this, SLOT(saveAct()));
    connect(newAction,SIGNAL(triggered()),this,SLOT(newAct()));//新建画布
    connect(saveGcodeAction,SIGNAL(triggered()),this,SLOT(saveGcodeAct()));
    connect(printGcodeAction,SIGNAL(triggered()),this,SLOT(printGcodeAct()));
    connect(cvtGrayAction,SIGNAL(triggered()),this,SLOT(cvtGrayAct()));
    connect(aboutAction, SIGNAL(triggered()),this, SLOT(aboutAct()));
}


