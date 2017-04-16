#pragma execution_character_set("utf-8")
#include "gcodeparameterwindow.h"

GCodeParameterWindow::GCodeParameterWindow(QWidget *parent) :QDialog(parent)
{
    initUI();
    initConnect();
}

GCodeParameterWindow::~GCodeParameterWindow()
{

}

void GCodeParameterWindow::slotOk()
{
    parameter.setXoffset(homewidget->xOffsetBox->value());
    parameter.setYoffset(homewidget->yOffsetBox->value());
    parameter.setYendset(homewidget->yEndsetBox->value());
    parameter.setZoffset(homewidget->zOffsetBox->value());

    parameter.setXYfeedrate(homewidget->xyFeedrateBox->value());
    parameter.setXYmaxFeedrate(homewidget->xyMaxFeedrateBox->value());
    parameter.setZfeedrate(homewidget->zFeedrateBox->value());
    parameter.setABfeedrate(homewidget->abFeedrateBox->value());

    parameter.setXwidth(homewidget->xWidthBox->value());
    parameter.setZheight(homewidget->zHeightBox->value());

    accept();
}

void GCodeParameterWindow::setGcodeParameter(GcodeParameter param)
{
    this->parameter = param;

    homewidget->xOffsetBox->setValue(param.getXoffset());
    homewidget->zOffsetBox->setValue(param.getZoffset());
    homewidget->yOffsetBox->setValue(param.getYoffset());
    homewidget->yEndsetBox->setValue(param.getYendset());

    homewidget->xyFeedrateBox->setValue(param.getXYfeedrate());
    homewidget->xyMaxFeedrateBox->setValue(param.getXYmaxFeedrate());
    homewidget->zFeedrateBox->setValue(param.getZfeedrate());
    homewidget->abFeedrateBox->setValue(param.getABfeedrate());

    homewidget->xWidthBox->setValue(param.getXwidth());
    homewidget->zHeightBox->setValue(param.getZheight());
}

GcodeParameter GCodeParameterWindow::getGcodeParameter()
{
    return this->parameter;
}

void GCodeParameterWindow::initUI()
{
    tabweight = new QTabWidget();
    homewidget = new HomeSetWidget();
    helpwiget = new HelpWidget();

    tabweight->addTab(homewidget,tr("参数配置"));
    tabweight->addTab(helpwiget,tr("帮助"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel); // 创建QDialogButtonBox
    buttonBox->button(QDialogButtonBox::Ok)->setText(tr("确定"));
    buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));

    mainLayout=new QVBoxLayout();
    mainLayout->addWidget(tabweight);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    setMinimumSize(450, 250);
    setMaximumSize(450, 250);
    setWindowTitle(tr("Gcode参数设置"));
}

void GCodeParameterWindow::initConnect()
{
    connect(buttonBox, &QDialogButtonBox::accepted, this, &GCodeParameterWindow::slotOk);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &GCodeParameterWindow::reject);
}

//home面板
HomeSetWidget::HomeSetWidget(QWidget *parent):QWidget(parent)
{
    initUI();
    initConnect();
}

HomeSetWidget::~HomeSetWidget()
{

}

void HomeSetWidget::slotBox(int value)
{
    xyFeedrateBox->setMaximum(value);
    abFeedrateBox->setMaximum(value);
}

void HomeSetWidget::initUI()
{
    label=new QLabel(tr("3D打印机gcode参数设置"));

    xOffsetLabel = new QLabel(tr("X坐标偏移："));
    xOffsetBox = new QDoubleSpinBox();
    xOffsetBox->setValue(16.0);
    xOffsetBox->setSuffix(tr("mm"));
    xOffsetBox->setMinimum(0.0);
    xOffsetBox->setMaximum(1000.0);
    xOffsetBox->setSingleStep(2.0);

    zOffsetLabel = new QLabel(tr("Z坐标偏移："));
    zOffsetBox = new QDoubleSpinBox();
    zOffsetBox->setValue(0.0);
    zOffsetBox->setSuffix(tr("mm"));
    zOffsetBox->setMinimum(0.0);
    zOffsetBox->setMaximum(100.0);
    zOffsetBox->setSingleStep(2.0);

    yOffsetLabel = new QLabel(tr("Y坐标偏移："));
    yOffsetBox = new QDoubleSpinBox();
    yOffsetBox->setValue(0.0);
    yOffsetBox->setSuffix(tr("mm"));
    yOffsetBox->setMinimum(10.0);
    yOffsetBox->setMaximum(1000.0);
    yOffsetBox->setSingleStep(2.0);

    yEndsetLabel = new QLabel(tr("Y轴终点坐标："));
    yEndsetBox = new QDoubleSpinBox();
    yEndsetBox->setValue(250.0);
    yEndsetBox->setSuffix(tr("mm"));
    yEndsetBox->setMinimum(0.0);
    yEndsetBox->setMaximum(1000.0);
    yEndsetBox->setSingleStep(10.0);

    xyFeedrateLabel = new QLabel(tr("X与Y轴运动速度："));
    xyFeedrateBox = new QSpinBox();
    xyFeedrateBox->setValue(2000);
    xyFeedrateBox->setSuffix(tr("mm/s"));
    xyFeedrateBox->setMinimum(100);
    xyFeedrateBox->setMaximum(5000);
    xyFeedrateBox->setSingleStep(1000);

    xyMaxFeedrateLabel = new QLabel(tr("X与Y轴最大运动速度："));
    xyMaxFeedrateBox = new QSpinBox();
    xyMaxFeedrateBox->setValue(5000);
    xyMaxFeedrateBox->setSuffix(tr("mm/s"));
    xyMaxFeedrateBox->setMinimum(1000);
    xyMaxFeedrateBox->setMaximum(9000);
    xyMaxFeedrateBox->setSingleStep(1000);

    zFeedrateLabel = new QLabel(tr("Z轴运动速度："));
    zFeedrateBox = new QSpinBox();
    zFeedrateBox->setValue(1000);
    zFeedrateBox->setSuffix(tr("mm/s"));
    zFeedrateBox->setMinimum(100);
    zFeedrateBox->setMaximum(2000);
    zFeedrateBox->setSingleStep(100);

    abFeedrateLabel = new QLabel(tr("AB轴运动速度："));
    abFeedrateBox = new QSpinBox();
    abFeedrateBox->setValue(2000);
    abFeedrateBox->setSuffix(tr("mm/s"));
    abFeedrateBox->setMinimum(100);
    abFeedrateBox->setMaximum(5000);
    abFeedrateBox->setSingleStep(100);

    xWidthLabel = new QLabel(tr("X轴运动宽度："));
    xWidthBox = new QDoubleSpinBox();
    xWidthBox->setValue(1.0);
    xWidthBox->setSuffix(tr("mm"));
    xWidthBox->setMinimum(0.1);
    xWidthBox->setMaximum(10.0);
    xWidthBox->setSingleStep(0.1);

    zHeightLabel = new QLabel(tr("Z轴运动高度："));
    zHeightBox = new QDoubleSpinBox();
    zHeightBox->setValue(2.0);
    zHeightBox->setSuffix(tr("mm"));
    zHeightBox->setMinimum(0.1);
    zHeightBox->setMaximum(100.0);
    zHeightBox->setSingleStep(1.0);

    mainlayout=new QGridLayout();
    mainlayout->addWidget(label, 0, 1, 1, 2);
    mainlayout->addWidget(xOffsetLabel, 1, 0);
    mainlayout->addWidget(xOffsetBox, 1, 1);
    mainlayout->addWidget(zOffsetLabel, 1, 2);
    mainlayout->addWidget(zOffsetBox, 1, 3);
    mainlayout->addWidget(yOffsetLabel, 2, 0);
    mainlayout->addWidget(yOffsetBox, 2, 1);
    mainlayout->addWidget(yEndsetLabel, 2, 2);
    mainlayout->addWidget(yEndsetBox, 2, 3);
    mainlayout->addWidget(xyFeedrateLabel, 3, 0);
    mainlayout->addWidget(xyFeedrateBox, 3, 1);
    mainlayout->addWidget(xyMaxFeedrateLabel, 3, 2);
    mainlayout->addWidget(xyMaxFeedrateBox, 3, 3);
    mainlayout->addWidget(zFeedrateLabel, 4, 0);
    mainlayout->addWidget(zFeedrateBox, 4, 1);
    mainlayout->addWidget(abFeedrateLabel, 4, 2);
    mainlayout->addWidget(abFeedrateBox, 4, 3);
    mainlayout->addWidget(xWidthLabel, 5, 0);
    mainlayout->addWidget(xWidthBox, 5, 1);
    mainlayout->addWidget(zHeightLabel, 5, 2);
    mainlayout->addWidget(zHeightBox, 5, 3);
    this->setLayout(mainlayout);
}

void HomeSetWidget::initConnect()
{
    connect(xyMaxFeedrateBox, static_cast< void (QSpinBox::*)(int) > (&QSpinBox::valueChanged),
            this, &HomeSetWidget::slotBox);
}

//help面板
HelpWidget::HelpWidget(QWidget *parent):QWidget(parent)
{
    initUI();
}

HelpWidget::~HelpWidget()
{

}

void HelpWidget::initUI()
{
    QVBoxLayout *mainlayout=new QVBoxLayout();
    helpLabel=new QLabel(tr("GCode代码输出\n初始参数设置"));
    helpLabel->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(helpLabel);
    this->setLayout(mainlayout);
}
