#include <iostream>
#include "opencv.hpp"
using namespace std;
using namespace cv;

#define WINDOWS_WIDTH 600
#define WINDOWS_HEIGHT 400
void createMat()
{
    //1.使用Mat 构造函数
    // Mat(int rows, int cols, int type, const Scalar& s);
    Mat M(2, 3, CV_8UC3, Scalar(0, 0, 255));
    cout << "M= " << M << endl;
    //2.在C/C++ 中使用构造函数进行初始化
    int sz[3] = {2, 2, 2};
    // Mat L(3, sz, CV_8UC, Scalar::all(0)); cv4 is error
    // cout << "L= " << L << endl;
    //3. IplImage指针创建
    // IplImage *
    // 4.Create() function
    M.create(4, 4, CV_8UC(2));
    cout << "M= " << M << endl;
    //5. ONES\ZEROS\EYES
    Mat E = Mat::eye(4, 4, CV_64F);
    cout << "M= " << E << endl;
    Mat O = Mat::ones(4, 4, CV_64F);
    cout << "M= " << O << endl;
    Mat Z = Mat::zeros(4, 4, CV_64F);
    cout << "M= " << Z << endl;
    // 6.小矩阵
    Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "M= " << C << endl;
    //7. 使用clone、copyTo
    Mat RowClone = C.row(1).clone();
    cout << "M= " << RowClone << endl;
}
void formatOpuput()
{
    // init
    Mat r = Mat(10, 3, CV_8UC3);
    randu(r, Scalar::all(0), Scalar::all(255));
    cout << "r= " << r << endl;
    cout << "r_PYTHON=" << format(r, Formatter::FMT_PYTHON) << endl;
    cout << "r_C=" << format(r, Formatter::FMT_C) << endl;
    cout << "r_NUMPY=" << format(r, Formatter::FMT_NUMPY) << endl;
    cout << "r_CSV=" << format(r, Formatter::FMT_CSV) << endl;
}

void convertColor(String image)
{
    Mat srcImg = imread(image), dstImg;
    imshow("srcImage", srcImg);
    cvtColor(srcImg, dstImg, COLOR_BGR2HSV);
    imshow("dstImage", dstImg);
    waitKey(0);
}
void colorReduce(Mat &inputImage, Mat &outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone();                          //拷贝实参到临时变量
    int rowNumber = outputImage.rows;                          //行数
    int colNumber = outputImage.cols * outputImage.channels(); //列数 x 通道数=每一行元素的个数

    //双重循环，遍历所有的像素值
    for (int i = 0; i < rowNumber; i++)
    {
        uchar *data = outputImage.ptr<uchar>(i);
        for (int j = 0; j < colNumber; j++)
        {
            data[j] = data[j] / div * div + div / 2;
        }
    }
}
void getPixByPoint(String img)
{
    //【1】创建原始图并显示
    Mat srcImage = imread(img);
    imshow("srcImage", srcImage);
    //【2】按原始图的参数规格来创建创建效果图
    Mat dstImage;
    dstImage.create(srcImage.rows, srcImage.cols, srcImage.type()); //效果图的大小、类型与原图片相同
    //【3】记录起始时间
    double time0 = static_cast<double>(getTickCount());
    //【4】调用颜色空间缩减函数
    colorReduce(srcImage, dstImage, 32);
    //【5】计算运行时间并输出
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "Timeout: " << time0 << "s" << endl; //输出运行时间
    //【6】显示效果图
    imshow("dstImage", dstImage);
    waitKey(0);
}
void drawEllipse(Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;
    // cv::InputOutputArray img, const cv::RotatedRect &box, const cv::Scalar &color, int thickness = 1, int lineType = 8
    ellipse(
        img,
        Point(WINDOWS_WIDTH / 2, WINDOWS_WIDTH / 2),
        Size(WINDOWS_WIDTH / 6, WINDOWS_WIDTH / 6),
        angle,
        0,
        360,
        Scalar(255, 129, 0),
        thickness,
        lineType);
}
void drawFilledCircle(Mat img, Point center)
{
    int thickness = 2;
    int lineType = 8;
    circle(
        img,
        center,
        WINDOWS_WIDTH / 32,
        Scalar(0, 0, 255),
        thickness,
        lineType);
}
void drawPolygon(Mat img)
{
    int lineType = 8;
    Point rookPoints[1][20];
    rookPoints[0][0] = Point(WINDOWS_WIDTH / 4, 7 * WINDOWS_WIDTH / 8);
    rookPoints[0][1] = Point(3 * WINDOWS_WIDTH / 4, 7 * WINDOWS_WIDTH / 8);
}
void colorReduceByIter(Mat &inputImage, Mat &outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone(); //拷贝实参到临时变量
    //获取迭代器
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();  //初始位置的迭代器
    Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>(); //终止位置的迭代器

    //存取彩色图像像素
    for (; it != itend; ++it)
    {
        (*it)[0] = (*it)[0] / div * div + div / 2;
        (*it)[1] = (*it)[1] / div * div + div / 2;
        (*it)[2] = (*it)[2] / div * div + div / 2;
    }
}
//          描述：使用【动态地址运算配合at】方法版本的颜色空间缩减函数
//----------------------------------------------------------------------------------------------
void colorReduceByAt(Mat &inputImage, Mat &outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone(); //拷贝实参到临时变量
    int rowNumber = outputImage.rows; //行数
    int colNumber = outputImage.cols; //列数

    for (int i = 0; i < rowNumber; i++)
    {
        for (int j = 0; j < colNumber; j++)
        {
            // BGR
            outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2; //蓝色通道
            outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2; //绿色通道
            outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2; //红是通道
        }
    }
}
void getPixByIter(String img)
{
    Mat srcImage = imread(img);
    imshow("srcImage", srcImage);
    //【2】按原始图的参数规格来创建创建效果图
    Mat dstImage;
    dstImage.create(srcImage.rows, srcImage.cols, srcImage.type()); //效果图的大小、类型与原图片相同
    //【3】记录起始时间
    double time0 = static_cast<double>(getTickCount());
    //【4】调用颜色空间缩减函数
    //colorReduceByIter(srcImage, dstImage, 32); //0.0145279s
    colorReduceByAt(srcImage, dstImage, 30);
    //【5】计算运行时间并输出
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "Time: " << time0 << "s" << endl; //输出运行时间
    //【6】显示效果图
    imshow("dstImage", dstImage);
    waitKey(0);
}
int main()
{
    String imgPath = "file/img/tt.jpg";
    String videoPath = "file/video/v_test.mp4";
    // createMat();
    // formatOpuput();
    // convertColor(imgPath);
    // getPixByPoint(imgPath);
    getPixByIter(imgPath);
    return 0;
}