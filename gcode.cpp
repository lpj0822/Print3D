#include "gcode.h"

GCode::GCode()
{
    init();
}

GCode::~GCode()
{

}

//增加gcode文件头
void GCode::addGcodeHead(int count)
{
    QString str1;
    QString str;
    str1.sprintf(";Layer count: %d",count);

    gcodeList.append(QObject::tr(""));
    gcodeList.append(str1);
    gcodeList.append(QObject::tr("M17"));
    gcodeList.append(QObject::tr("G28"));
    str.sprintf("M97 A%d B%d", abFeedrate, abFeedrate);
    gcodeList.append(str);
    addG01Z(zFeedrate,offsetZ);
    addG01X(xyMaxFeedrate,offsetX);
    addG01Y(xyMaxFeedrate,offsetY);
}

//增加gcode尾部
void GCode::addGcodeEnd()
{
    float z=preZ+zHeight+30;
    addG01Z(zFeedrate,z);
    gcodeList.append(QObject::tr("M18"));
    gcodeList.append(QObject::tr(";END"));
    preZ=z;
}

//增加层注释
void GCode::addLayer(int layer)
{
    QString str;
    str.sprintf(";LAYER:%d",layer);
    gcodeList.append(str);
}

//增加M107指令
void GCode::addM107()
{
    gcodeList.append(QObject::tr("M107"));
    this->curFanSpeed=0;
}

//增加M106指令
void GCode::addM106()
{
    QString str;
    int speed=curFanSpeed+5;
    if(speed>MAXFANSPEED)
    {
        speed=255;
    }
    str.sprintf("M106 S%d",speed);
    gcodeList.append(str);
    curFanSpeed=speed;
}

void GCode::addM106(int fanSpeed)
{
    QString str;
    if(fanSpeed<0)
    {
        fanSpeed=0;
        addM107();
    }
    else if(fanSpeed>255)
    {
        fanSpeed=255;
        str.sprintf("M106 S%d",fanSpeed);
        gcodeList.append(str);
        curFanSpeed=fanSpeed;
    }
    else
    {
        str.sprintf("M106 S%d",fanSpeed);
        gcodeList.append(str);
        curFanSpeed=fanSpeed;
    }
}

void GCode::addG00(float x,float y)
{
    QString str;
    str.sprintf("G0 X%.2f Y%.2f F%d",x,y,xyMaxFeedrate);
    gcodeList.append(str);
    preX=x;
    preY=y;
}

void GCode::addG01(int feedrate, float x, float y)
{
    QString str;
    str.sprintf("G1 X%.2f Y%.2f F%d",x,y,feedrate);
    gcodeList.append(str);
    preX=x;
    preY=y;
}

//增加G1指令
void GCode::addG01(int feedrate,float x,float y,int a,int b)
{
    QString str;
    str.sprintf("G1 X%.2f Y%.2f A%d B%d F%d",x,y,a,b,feedrate);
    gcodeList.append(str);
    preX=x;
    preY=y;
}

void GCode::addG01(int feedrate,float y,int a,int b)
{
    QString str;
    str.sprintf("G1 Y%.2f A%d B%d F%d",y,a,b,feedrate);
    gcodeList.append(str);
    preY=y;
}


void GCode::addG01Z(int feedrate,float z)
{
    QString str;
    str.sprintf("G1 Z%.2f F%d",z,feedrate);
    gcodeList.append(str);
    preZ=z;
}

void GCode::addG01X(int feedrate,float x)
{
    QString str;
    str.sprintf("G1 X%.2f F%d",x,feedrate);
    gcodeList.append(str);
    preX=x;
}

void GCode::addG01Y(int feedrate,float y)
{
    QString str;
    str.sprintf("G1 Y%.2f F%d",y,feedrate);
    gcodeList.append(str);
    preY=y;
}

//添加注释
void GCode::addNote(QString note)
{
    gcodeList.append(note);
}

//生成一层Gcode
void GCode::addGcodeLayer(std::vector<int> layer,bool isBack,int count)
{
    int a=0,b=255;
//    if(count==0)
//    {
//        addLayer(count);
//        addNote(QObject::tr(";TYPE:FILL"));
//        for(int loop=0;loop<(int)layer.size();loop++)
//        {
//            a=layer[loop];
//            b=255-a;
//            if(preY==offsetY)
//            {
//                addG01(abFeedrate,preX,endsetY,a,b);
//                if(loop<(int)layer.size()-1)
//                {
//                    float x=preX+xWidth;
//                    addG01(xyFeedrate,x,preY);
//                }
//            }
//            else if(preY==endsetY)
//            {
//                addG01(abFeedrate,preX,offsetY,a,b);
//                if(loop<(int)layer.size()-1)
//                {
//                    float x=preX+xWidth;
//                    addG01(xyFeedrate,x,preY);
//                }
//            }
//        }
//    }
//    else
//    {
//        if(!isBack)
//        {
//            float x=preX;
//            float z=preZ+zHeight;
//            addLayer(count);
//            addG01Z(zFeedrate,z);
//            addNote(QObject::tr(";TYPE:FILL"));
//            for(int loop=0;loop<(int)layer.size();loop++)
//            {
//                a=layer[loop];
//                b=255-a;
//                if(preY==offsetY)
//                {
//                    addG01(abFeedrate,preX,endsetY,a,b);
//                    if(loop<(int)layer.size()-1)
//                    {
//                        x=preX+xWidth;
//                        addG01(xyFeedrate,x,preY);
//                    }
//                }
//                else if(preY==endsetY)
//                {
//                    addG01(abFeedrate,preX,offsetY,a,b);
//                    if(loop<(int)layer.size()-1)
//                    {
//                        x=preX+xWidth;
//                        addG01(xyFeedrate,x,preY);
//                    }
//                }
//            }
//        }
//        else
//        {
//            float x=preX;
//            float z=preZ+zHeight;
//            addLayer(count);
//            addG01Z(zFeedrate,z);
//            addNote(QObject::tr(";TYPE:FILL"));
//            for(int loop=(int)layer.size()-1;loop>=0;loop--)
//            {
//                a=layer[loop];
//                b=255-a;
//                if(preY==offsetY)
//                {
//                    addG01(abFeedrate,preX,endsetY,a,b);
//                    if(loop>0)
//                    {
//                        x=preX-xWidth;
//                        if(x<offsetX)
//                            x=offsetX;
//                        addG01(xyFeedrate,x,preY);
//                    }
//                }
//                else if(preY==endsetY)
//                {
//                    addG01(abFeedrate,preX,offsetY,a,b);
//                    if(loop>0)
//                    {
//                        x=preX-xWidth;
//                        if(x<offsetX)
//                            x=offsetX;
//                        addG01(xyFeedrate,x,preY);
//                    }
//                }
//            }
//        }
//    }
    if(count==0)
    {
        addLayer(count);
        addNote(QObject::tr(";TYPE:FILL"));
        for(int loop=0;loop<(int)layer.size();loop++)
        {
            a=layer[loop];
            b=255-a;
            if(preY==offsetY)
            {
                addG01(xyFeedrate,endsetY,a,b);
                if(loop<(int)layer.size()-1)
                {
                    float x=preX+xWidth;
                    addG01X(xyFeedrate,x);
                }
            }
            else if(preY==endsetY)
            {
                addG01(xyFeedrate,offsetY,a,b);
                if(loop<(int)layer.size()-1)
                {
                    float x=preX+xWidth;
                    addG01X(xyFeedrate,x);
                }
            }
        }
    }
    else
    {
        if(!isBack)
        {
            float x=preX;
            float z=preZ+zHeight;
            addLayer(count);
            addG01Z(zFeedrate,z);
            addNote(QObject::tr(";TYPE:FILL"));
            for(int loop=0;loop<(int)layer.size();loop++)
            {
                a=layer[loop];
                b=255-a;
                if(preY==offsetY)
                {
                    addG01(xyFeedrate,endsetY,a,b);
                    if(loop<(int)layer.size()-1)
                    {
                        x=preX+xWidth;
                        addG01X(xyFeedrate,x);
                    }
                }
                else if(preY==endsetY)
                {
                    addG01(xyFeedrate,offsetY,a,b);
                    if(loop<(int)layer.size()-1)
                    {
                        x=preX+xWidth;
                        addG01X(xyFeedrate,x);
                    }
                }
            }
        }
        else
        {
            float x=preX;
            float z=preZ+zHeight;
            addLayer(count);
            addG01Z(zFeedrate,z);
            addNote(QObject::tr(";TYPE:FILL"));
            for(int loop=(int)layer.size()-1;loop>=0;loop--)
            {
                a=layer[loop];
                b=255-a;
                if(preY==offsetY)
                {
                    addG01(xyFeedrate,endsetY,a,b);
                    if(loop>0)
                    {
                        x=preX-xWidth;
                        if(x<offsetX)
                            x=offsetX;
                        addG01X(xyFeedrate,x);
                    }
                }
                else if(preY==endsetY)
                {
                    addG01(xyFeedrate,offsetY,a,b);
                    if(loop>0)
                    {
                        x=preX-xWidth;
                        if(x<offsetX)
                            x=offsetX;
                        addG01X(xyFeedrate,x);
                    }
                }
            }
        }
    }
}

void GCode::addGcodeLayer(std::vector<int> layer, int count)
{
    int a=0,b=255;
    if(count==0)
    {
        addLayer(count);
        addNote(QObject::tr(";TYPE:FILL"));
        for(int loop=0;loop<(int)layer.size();loop++)
        {
            a=layer[loop];
            b=255-a;
            if(preY==offsetY)
            {
                addG01(xyFeedrate,endsetY,a,b);
                if(loop<(int)layer.size()-1)
                {
                    float x=preX+xWidth;
                    addG01X(xyFeedrate,x);
                }
            }
            else if(preY==endsetY)
            {
                addG01(xyFeedrate,offsetY,a,b);
                if(loop<(int)layer.size()-1)
                {
                    float x=preX+xWidth;
                    addG01X(xyFeedrate,x);
                }
            }
        }
    }
    else
    {
        float x = preX;
        float z = preZ+zHeight;
        addLayer(count);
        addG01Z(zFeedrate,z);
        addG01X(xyMaxFeedrate,offsetX);
        addNote(QObject::tr(";TYPE:FILL"));
        for(int loop=0;loop<(int)layer.size();loop++)
        {
            a=layer[loop];
            b=255-a;
            if(preY==offsetY)
            {
                    addG01(xyFeedrate,endsetY,a,b);
                    if(loop<(int)layer.size()-1)
                    {
                        x=preX+xWidth;
                        addG01X(xyFeedrate,x);
                    }
            }
            else if(preY==endsetY)
            {
                addG01(xyFeedrate,offsetY,a,b);
                if(loop<(int)layer.size()-1)
                {
                    x=preX+xWidth;
                    addG01X(xyFeedrate,x);
                }
            }
        }
    }
}

//输出为文件
bool GCode::printFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(NULL, QObject::tr("保存gcode"),
                             QObject::tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    for(int loop=0;loop<gcodeList.count();loop++)
    {
        out<<gcodeList[loop]<<'\n';
    }
    return true;
}

GcodeParameter GCode::getParameter()
{
    GcodeParameter param;
    param.setXoffset(offsetX);
    param.setYoffset(offsetY);
    param.setYendset(endsetY);
    param.setZoffset(offsetZ);

    param.setXYfeedrate(xyFeedrate);
    param.setXYmaxFeedrate(xyMaxFeedrate);
    param.setZfeedrate(zFeedrate);
    param.setABfeedrate(abFeedrate);

    param.setXwidth(xWidth);
    param.setZheight(zHeight);

    return param;
}

void GCode::setParameter(GcodeParameter param)
{
    this->zHeight = param.getZheight();
    this->xWidth = param.getXwidth();

    this->xyMaxFeedrate = param.getXYmaxFeedrate();
    this->xyFeedrate = param.getXYfeedrate();
    this->abFeedrate = param.getABfeedrate();
    this->zFeedrate = param.getZfeedrate();

    this->endsetY = param.getYendset();

    this->offsetX = param.getXoffset();
    this->offsetY = param.getYoffset();
    this->offsetZ = param.getZoffset();
}

void GCode::init()
{
    gcodeList.clear();

    this->zHeight = 1.4f;
    this->xWidth = 1.4f;

    this->xyMaxFeedrate = 5000;
    this->xyFeedrate = 4000;
    this->abFeedrate = 2000;
    this->zFeedrate = 1000;

    this->endsetY = 250.0f;

    this->offsetX = 16.0f;
    this->offsetY = 10.0f;
    this->offsetZ = 0.0f;

    this->preX = 0.0f;
    this->preY = 0.0f;
    this->preZ = 0.0f;

    this->curFanSpeed = 0;
}

