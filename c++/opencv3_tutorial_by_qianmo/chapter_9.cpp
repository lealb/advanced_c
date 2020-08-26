#include <iostream>
#include "opencv.hpp"
using namespace std;
using namespace cv;

// H-s直方图
void testHistogram(string img)
{
    //【1】载入源图，转化为HSV颜色模型
    Mat srcImage, hsvImage;
    srcImage = imread(img);
    // hsvImage.create(srcImage.size(),srcImage.type());
    if (!srcImage.data)
    {
        cout << "read image error!" << endl;
    }
    cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);

    //【2】参数准备
    //将色调量化为30个等级，将饱和度量化为32个等级
    int hueBinNum = 30;        //色调的直方图直条数量
    int saturationBinNum = 32; //饱和度的直方图直条数量
    int histSize[] = {hueBinNum, saturationBinNum};
    // 定义色调的变化范围为0到179
    float hueRanges[] = {0, 180};
    //定义饱和度的变化范围为0（黑、白、灰）到255（纯光谱颜色）
    float saturationRanges[] = {0, 256};
    const float *ranges[] = {hueRanges, saturationRanges};
    MatND dstHist;
    //参数准备，calcHist函数中将计算第0通道和第1通道的直方图
    int channels[] = {0, 1};

    //【3】正式调用calcHist，进行直方图计算
    calcHist(&hsvImage, //输入的数组
             1,         //数组个数为1
             channels,  //通道索引
             Mat(),     //不使用掩膜
             dstHist,   //输出的目标直方图
             2,         //需要计算的直方图的维度为2
             histSize,  //存放每个维度的直方图尺寸的数组
             ranges,    //每一维数值的取值范围数组
             true,      // 指示直方图是否均匀的标识符，true表示均匀的直方图
             false);    //累计标识符，false表示直方图在配置阶段会被清零

    //【4】为绘制直方图准备参数
    double maxValue = 0;                    //最大值
    minMaxLoc(dstHist, 0, &maxValue, 0, 0); //查找数组和子数组的全局最小值和最大值存入maxValue中
    int scale = 10;
    Mat histImg = Mat::zeros(saturationBinNum * scale, hueBinNum * 10, CV_8UC3);

    //【5】双层循环，进行直方图绘制
    for (int hue = 0; hue < hueBinNum; hue++)
        for (int saturation = 0; saturation < saturationBinNum; saturation++)
        {
            float binValue = dstHist.at<float>(hue, saturation); //直方图组距的值
            int intensity = cvRound(binValue * 255 / maxValue);  //强度

            //正式进行绘制
            rectangle(histImg, Point(hue * scale, saturation * scale),
                      Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1),
                      Scalar::all(intensity), FILLED);
        }

    //【6】显示效果图
    imshow("srcImage", srcImage);
    imshow("histImg", histImg);

    waitKey(0);
}

void testHistogramOne(string img)
{
    Mat srcImage = imread(img, 0);
    imshow("srcImage", srcImage);
    if (!srcImage.data)
    {
        cout << "fail to load image" << endl;
    }

    //【2】定义变量
    MatND dstHist; // 在cv中用CvHistogram *hist = cvCreateHist
    int dims = 1;
    float hranges[] = {0, 255};
    const float *ranges[] = {hranges}; // 这里需要为const类型
    int size = 256;
    int channels = 0;

    //【3】计算图像的直方图
    calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges); // cv 中是cvCalcHist
    int scale = 1;

    Mat dstImage(size * scale, size, CV_8U, Scalar(0));
    //【4】获取最大值和最小值
    double minValue = 0;
    double maxValue = 0;
    minMaxLoc(dstHist, &minValue, &maxValue, 0, 0); //  在cv中用的是cvGetMinMaxHistValue

    //【5】绘制出直方图
    int hpt = saturate_cast<int>(0.9 * size);
    for (int i = 0; i < 256; i++)
    {
        // 注意hist中是float类型
        //而在OpenCV1.0版中用cvQueryHistValue_1D
        float binValue = dstHist.at<float>(i);
        int realValue = saturate_cast<int>(binValue * hpt / maxValue);
        rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue), Scalar(255));
    }
    imshow("dstImage", dstImage);
    waitKey(0);
}

void testHistogramRGB(string img)
{

    Mat srcImage = imread(img);
    imshow("srcImage", srcImage);
    if (!srcImage.data)
    {
        cout << "fail to load image" << endl;
    }

    //【2】参数准备
    int bins = 256;
    int hist_size[] = {bins};
    float range[] = {0, 256};
    const float *ranges[] = {range};
    MatND redHist, grayHist, blueHist;
    int channels_r[] = {0};

    //【3】进行直方图的计算（红色分量部分）
    calcHist(&srcImage, 1, channels_r, Mat(), //不使用掩膜
             redHist, 1, hist_size, ranges,
             true, false);

    //【4】进行直方图的计算（绿色分量部分）
    int channels_g[] = {1};
    calcHist(&srcImage, 1, channels_g, Mat(), // do not use mask
             grayHist, 1, hist_size, ranges,
             true, // the histogram is uniform
             false);

    //【5】进行直方图的计算（蓝色分量部分）
    int channels_b[] = {2};
    calcHist(&srcImage, 1, channels_b, Mat(), // do not use mask
             blueHist, 1, hist_size, ranges,
             true, // the histogram is uniform
             false);

    //-----------------------绘制出三色直方图------------------------
    //参数准备
    double maxValue_red, maxValue_green, maxValue_blue;
    minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
    minMaxLoc(grayHist, 0, &maxValue_green, 0, 0);
    minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
    int scale = 1;
    int histHeight = 256;
    Mat histImage = Mat::zeros(histHeight, bins * 3, CV_8UC3);

    //正式开始绘制
    for (int i = 0; i < bins; i++)
    {
        //参数准备
        float binValue_red = redHist.at<float>(i);
        float binValue_green = grayHist.at<float>(i);
        float binValue_blue = blueHist.at<float>(i);
        int intensity_red = cvRound(binValue_red * histHeight / maxValue_red);       //要绘制的高度
        int intensity_green = cvRound(binValue_green * histHeight / maxValue_green); //要绘制的高度
        int intensity_blue = cvRound(binValue_blue * histHeight / maxValue_blue);    //要绘制的高度

        //绘制红色分量的直方图
        rectangle(histImage, Point(i * scale, histHeight - 1),
                  Point((i + 1) * scale - 1, histHeight - intensity_red),
                  Scalar(255, 0, 0));

        //绘制绿色分量的直方图
        rectangle(histImage, Point((i + bins) * scale, histHeight - 1),
                  Point((i + bins + 1) * scale - 1, histHeight - intensity_green),
                  Scalar(0, 255, 0));

        //绘制蓝色分量的直方图
        rectangle(histImage, Point((i + bins * 2) * scale, histHeight - 1),
                  Point((i + bins * 2 + 1) * scale - 1, histHeight - intensity_blue),
                  Scalar(0, 0, 255));
    }

    //在窗口中显示出绘制好的直方图
    imshow("histImage", histImage);
    waitKey(0);
}

int main(int argc, char const *argv[])
{
    string img = "file/img/tt.jpg";
    // testHistogram(img);
    // testHistogramOne(img);
    testHistogramRGB(img);
    return 0;
}
