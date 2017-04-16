#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include<stdlib.h>
#include<vector>

#include<QImage>
#include<QObject>
#include<QString>

#include "rtcprgb2gray.h"

class ImageProcess: public QObject
{
    Q_OBJECT

public:
    ImageProcess(QObject *parent = 0);
    ImageProcess(const QString &fileName,QObject *parent = 0);
    ~ImageProcess();
    int readIamge(const QString &fileName);
    void convertImage(int code);//转换图像
    QImage getConvertImage(int code);//得到转换后的图像

    std::vector<std::vector<int> > getGrayPixel();//得到灰度图像的像素值

    void clearImage();//清空图像数据

private:
    cv::Mat image;  // the image variable
    cv::Mat conImage;

    RTCPrgb2gray rgb2Gray;
};

#endif // IMAGEPROCESS_H
