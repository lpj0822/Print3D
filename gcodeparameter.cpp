#include "gcodeparameter.h"

GcodeParameter::GcodeParameter()
{

}

GcodeParameter::~GcodeParameter()
{

}

float GcodeParameter::getXoffset()
{
    return this->xOffset;
}

void GcodeParameter::setXoffset(float value)
{
    this->xOffset = value;
}

float GcodeParameter::getYoffset()
{
    return this->yOffset;
}

void GcodeParameter::setYoffset(float value)
{
    this->yOffset = value;
}

float GcodeParameter::getYendset()
{
    return this->yEndSet;
}

void GcodeParameter::setYendset(float value)
{
    this->yEndSet = value;
}

float GcodeParameter::getZoffset()
{
    return this->zOffset;
}

void GcodeParameter::setZoffset(float value)
{
    this->zOffset = value;
}

int GcodeParameter::getXYfeedrate()
{
    return this->xyFeedrate;
}

void GcodeParameter::setXYfeedrate(int value)
{
    this->xyFeedrate = value;
}

int GcodeParameter::getXYmaxFeedrate()
{
    return this->xyMaxFeedrate;
}

void GcodeParameter::setXYmaxFeedrate(int value)
{
    this->xyMaxFeedrate = value;
}

int GcodeParameter::getZfeedrate()
{
    return this->zFeedrate;
}

void GcodeParameter::setZfeedrate(int value)
{
    this->zFeedrate = value;
}

int GcodeParameter::getABfeedrate()
{
    return this->abFeedrate;
}

void GcodeParameter::setABfeedrate(int value)
{
    this->abFeedrate = value;
}

float GcodeParameter::getXwidth()
{
    return this->xWidth;
}

void GcodeParameter::setXwidth(float value)
{
    this->xWidth = value;
}

float GcodeParameter::getZheight()
{
    return this->zHeight;
}

void GcodeParameter::setZheight(float value)
{
    this->zHeight = value;
}
