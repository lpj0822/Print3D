#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    qApp->setWindowIcon(QIcon(":/images/li.png"));
    MainWindow w;
    w.show();

    return a.exec();
}
