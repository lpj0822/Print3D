#ifndef GCODEPARAMETERWINDOW_H
#define GCODEPARAMETERWINDOW_H

#include <QDialog>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include "gcodeparameter.h"

//home面板
class HomeSetWidget: public QWidget
{
    Q_OBJECT

public:
     HomeSetWidget(QWidget *parent = 0);
     ~HomeSetWidget();

     QDoubleSpinBox *xOffsetBox;
     QDoubleSpinBox *zOffsetBox;
     QDoubleSpinBox *yOffsetBox;
     QDoubleSpinBox *yEndsetBox;

     QSpinBox *xyFeedrateBox;
     QSpinBox *xyMaxFeedrateBox;
     QSpinBox *zFeedrateBox;
     QSpinBox *abFeedrateBox;

     QDoubleSpinBox *xWidthBox;
     QDoubleSpinBox *zHeightBox;

private slots:
     void slotBox(int value);

private:
     void initUI();//初始化
     void initConnect();

     QGridLayout *mainlayout;
     QLabel *label;

     QLabel *xOffsetLabel;
     QLabel *yOffsetLabel;
     QLabel *yEndsetLabel;
     QLabel *zOffsetLabel;

     QLabel *xyFeedrateLabel;
     QLabel *xyMaxFeedrateLabel;
     QLabel *zFeedrateLabel;
     QLabel *abFeedrateLabel;

     QLabel *xWidthLabel;
     QLabel *zHeightLabel;
};

//help面板
class HelpWidget: public QWidget
{
    Q_OBJECT

public:
     HelpWidget(QWidget *parent = 0);
     ~HelpWidget();

private:
     void initUI();

     QLabel *helpLabel;
};

class GCodeParameterWindow : public QDialog
{
     Q_OBJECT

public:
    GCodeParameterWindow(QWidget *parent = 0);
    ~GCodeParameterWindow();

    void setGcodeParameter(GcodeParameter param);
    GcodeParameter getGcodeParameter();

signals:

public slots:
    void slotOk();//点击确定

private:

    void initUI();
    void initConnect();

    QVBoxLayout *mainLayout;//布局
    QTabWidget *tabweight;//tab
    QDialogButtonBox *buttonBox;
    HomeSetWidget *homewidget;//home面板
    HelpWidget *helpwiget;//help面板

    GcodeParameter parameter;
};

#endif // GCODEPARAMETERWINDOW_H
