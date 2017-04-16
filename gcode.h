#ifndef GCODE_H
#define GCODE_H

#include<QObject>
#include<QList>
#include<QString>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>

#include<vector>

#include "datadef.h"
#include "gcodeparameter.h"


class GCode
{
public:
    GCode();
    ~GCode();

    void addGcodeHead(int count);//增加gcode文件头
    void addGcodeEnd();//增加gcode尾部
    void addLayer(int layer);//增加层注释

    void addM107();//增加M107指令
    void addM106();//增加M106指令
    void addM106(int fanSpeed);

    void addG00(float x,float y);
    void addG01(int feedrate,float x,float y);
    void addG01(int feedrate,float x,float y,int a,int b);//增加G1指令

    void addG01(int feedrate,float y,int a,int b);
    void addG01Z(int feedrate,float z);
    void addG01X(int feedrate,float x);
    void addG01Y(int feedrate,float y);

    void addNote(QString note);//添加注释

    void addGcodeLayer(std::vector<int> layer,bool isBack,int count);//生成一层Gcode
    void addGcodeLayer(std::vector<int> layer, int count);

    bool printFile(const QString &fileName);//输出为文件

    void setParameter(GcodeParameter param);
    GcodeParameter getParameter();

private:

    void init();

    QList<QString> gcodeList;//gcode文件数据

    float zHeight;//z轴移动的高度
    float xWidth;//宽度

    int xyMaxFeedrate;//最大速度
    int xyFeedrate;
    int abFeedrate;
    int zFeedrate;

    float endsetY;

    float offsetX;
    float offsetY;
    float offsetZ;

    int curFanSpeed;//当前风速

    float preX;
    float preY;
    float preZ;
};

#endif // GCODE_H
