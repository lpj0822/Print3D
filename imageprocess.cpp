#pragma execution_character_set("utf-8")
#include "imageprocess.h"
#include <QMessageBox>

ImageProcess::ImageProcess(QObject *parent) : QObject(parent)
{

}

ImageProcess::ImageProcess(const QString &fileName,QObject *parent): QObject(parent)
{
    image= cv::imread(fileName.toStdString().c_str());
    if(!image.empty())
    {
        cv::namedWindow("Original Image");
        cv::imshow("Original Image", image);
    }
}

ImageProcess::~ImageProcess()
{

}

//得到灰度图像的像素值
std::vector<std::vector<int> > ImageProcess::getGrayPixel()
{
    std::vector<std::vector<int> > tempPixel;
    tempPixel.clear();
    if(conImage.data)
    {
        if(conImage.channels()==1) //灰度图
        {
            int nl= conImage.rows; // number of lines
            int nc= conImage.cols * conImage.channels(); // total number of elements per line

            for (int j=0; j<nl; j++)
            {
                uchar* data= conImage.ptr<uchar>(j);
                std::vector<int> tempCol;
                tempCol.clear();
                for (int i=0; i<nc; i++)
                {
                    // process each pixel ---------------------
                    //data[i]= data[i]/div*div + div/2;
                    tempCol.push_back(data[i]);
                    // end of pixel processing ----------------
                } // end of line
                tempPixel.push_back(tempCol);
            }
        }
    }
    return tempPixel;
}

int ImageProcess::readIamge(const QString &fileName)
{
    image= cv::imread(fileName.toStdString().c_str());
    if(image.empty())
    {
        QMessageBox::information(NULL,tr("图像出错"),tr("图像数据加载不成功!"));
        return -1;
    }
    else
    {
        return 0;
    }
}

void ImageProcess::convertImage(int code)
{
    if(!image.empty())
    {
        switch(code){
        case 0:
            conImage=rgb2Gray.BGR2Gray(image);
            //cv::cvtColor(image,conImage,CV_BGR2GRAY);
            break;
        case 1:
            cv::cvtColor(image,conImage,CV_BGR2RGB);
            break;
        }
    }
}

QImage ImageProcess::getConvertImage(int code)//得到转换后的图像
{
    QImage tempImage=QImage();
    if(conImage.data)
    {
        switch(code)
        {
        case 0:
            {
                tempImage=QImage(conImage.cols,conImage.rows,QImage::Format_Indexed8);
                tempImage.setColorCount(256);
                for(int i = 0; i < 256; i++)
                {
                    tempImage.setColor(i, qRgb(i, i, i));
                }
                // Copy input Mat
                uchar *pSrc = conImage.data;
                for(int row = 0; row < conImage.rows; row ++)
                {
                    uchar *pDest = tempImage.scanLine(row);
                    memcpy(pDest, pSrc, conImage.cols);
                    pSrc += conImage.step;
                }
            }
            break;
        case 1:
            tempImage=QImage((const unsigned char*)(conImage.data),conImage.cols,conImage.rows,QImage::Format_RGB888);
            break;
        }
    }
    return tempImage;
}

//清空图像数据
void ImageProcess::clearImage()
{
    if(!image.empty())
    {
        image.release();
    }
    if(!conImage.empty())
    {
        conImage.release();
    }
}
