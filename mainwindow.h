#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QScrollArea>
#include <QLabel>
#include <QPixmap>
#include <QFileDialog>
#include <QCloseEvent>
#include "imageprocess.h"
#include "printwindow.h"
#include "gcodeparameter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void saveAct();
    void loadAct();
    void newAct();
    void saveGcodeAct();
    void printGcodeAct();
    void cvtGrayAct();
    void aboutAct();

private:
    void initUI();//初始化UI
    void initData();//初始化数据
    void initConnect();

    void createActions();
    void createMenus();
    void createToolBars();

    QScrollArea *scrollArea;//滚动区域

    QLabel *labelImage;
    QPixmap pixmap;//生成图片
    QString fileName;//图片路径
    int imageWidth;//图片宽度
    int imageHeight;//图片宽度

    QAction *exitAction;
    QAction *saveAction;
    QAction *loadAction;
    QAction *newAction;//新建

    QAction *cvtGrayAction;//转换为灰度图

    QAction *saveGcodeAction;//保存为Gcode代码
    QAction *printGcodeAction;//打印Gcode文件

    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;

    QToolBar *fileTool;

    PrintWindow *printWindow;

    ImageProcess *imageProcess;//图像处理类

    QString loadCurDir;//包含文件名的绝对路径
    QString saveCurDir;

    GcodeParameter paramter;

};

#endif // MAINWINDOW_H
