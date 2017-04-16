#ifndef GCODEPARAMETER_H
#define GCODEPARAMETER_H


class GcodeParameter
{
public:
    GcodeParameter();
    ~GcodeParameter();

    float getXoffset();
    void setXoffset(float value);
    float getYoffset();
    void setYoffset(float value);
    float getYendset();
    void setYendset(float value);
    float getZoffset();
    void setZoffset(float value);

    int getXYfeedrate();
    void setXYfeedrate(int value);
    int getXYmaxFeedrate();
    void setXYmaxFeedrate(int value);
    int getZfeedrate();
    void setZfeedrate(int value);
    int getABfeedrate();
    void setABfeedrate(int value);

    float getXwidth();
    void setXwidth(float value);
    float getZheight();
    void setZheight(float value);

private:

    float zHeight;//z轴移动的高度
    float xWidth;//x移动宽度

    int xyMaxFeedrate;//最大速度
    int xyFeedrate;
    int abFeedrate;
    int zFeedrate;

    float yEndSet;

    float xOffset;
    float yOffset;
    float zOffset;
};

#endif // GCODEPARAMETER_H
