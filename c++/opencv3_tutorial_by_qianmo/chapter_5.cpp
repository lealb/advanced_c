#include <iostream>
#include "opencv.hpp"
#include <time.h>
using namespace std;
using namespace cv;

bool ROI_AddImage()
{
    // 【1】读入图像
    Mat srcImage1 = imread("file/img/dota_pa.jpg");
    Mat logoImage = imread("file/img/dota_logo.jpg");
    if (!srcImage1.data)
    {
        printf("读取srcImage1错误~！ \n");
        return false;
    }
    if (!logoImage.data)
    {
        printf("读取logoImage错误~！ \n");
        return false;
    }
    // 【2】定义一个Mat类型并给其设定ROI区域
    Mat imageROI = srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));
    // 【3】加载掩模（必须是灰度图）
    Mat mask = imread("file/img/dota_logo.jpg", 0);
    //【4】将掩膜拷贝到ROI
    logoImage.copyTo(imageROI, mask);
    // 【5】显示结果
    namedWindow("<1>利用ROI实现图像叠加示例窗口");
    imshow("<1>利用ROI实现图像叠加示例窗口", srcImage1);
    return true;
}

//---------------------------------【LinearBlending（）函数】-------------------------------------
// 函数名：LinearBlending（）
// 描述：利用cv::addWeighted（）函数实现图像线性混合
//--------------------------------------------------------------------------------------------
bool LinearBlending()
{
    //【0】定义一些局部变量
    double alphaValue = 0.5;
    double betaValue;
    Mat srcImage2, srcImage3, dstImage;

    // 【1】读取图像 ( 两幅图片需为同样的类型和尺寸 )
    srcImage2 = imread("file/img/mogu.jpg");
    srcImage3 = imread("file/img/rain.jpg");

    if (!srcImage2.data)
    {
        printf("read srcImage2 error \n");
        return false;
    }
    if (!srcImage3.data)
    {
        printf("读取srcImage3错误！ \n");
        return false;
    }

    // 【2】进行图像混合加权操作
    betaValue = (1.0 - alphaValue);
    addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

    // 【3】显示原图窗口
    imshow("srcImage2", srcImage2);
    imshow("dstImage", dstImage);

    return true;
}

//---------------------------------【ROI_LinearBlending（）】-------------------------------------
// 函数名：ROI_LinearBlending（）
// 描述：线性混合实现函数,指定区域线性图像混合.利用cv::addWeighted（）函数结合定义
//			  感兴趣区域ROI，实现自定义区域的线性混合
//--------------------------------------------------------------------------------------------
bool ROI_LinearBlending()
{

    //【1】读取图像
    Mat srcImage4 = imread("file/img/dota_pa.jpg", 1);
    Mat logoImage = imread("file/img/dota_logo.jpg");

    if (!srcImage4.data)
    {
        printf("读取srcImage4错误~！ \n");
        return false;
    }
    if (!logoImage.data)
    {
        printf("读取logoImage错误~！ \n");
        return false;
    }

    //【2】定义一个Mat类型并给其设定ROI区域
    Mat imageROI;
    //方法一
    imageROI = srcImage4(Rect(200, 250, logoImage.cols, logoImage.rows));
    //方法二
    //imageROI= srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));

    //【3】将logo加到原图上
    addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI);
    //【4】显示结果
    imshow("srcImage4", srcImage4);

    return true;
}
/**
 * @cOlor
 * 多通道混合-分量部分
 * 0-B ,1-G, 2-R
 */
bool MultiChannelBlending(int color = 0)
{
    //【0】定义相关变量
    Mat srcImage;
    Mat logoImage;
    vector<Mat> channels;
    Mat imageBlueChannel;
    // 【1】读入图片
    logoImage = imread("file/img/dota_logo.jpg", 0);
    srcImage = imread("file/img/dota_jugg.jpg");

    if (!logoImage.data)
    {
        printf("Oh，no，读取logoImage错误~！ \n");
        return false;
    }
    if (!srcImage.data)
    {
        printf("Oh，no，读取srcImage错误~！ \n");
        return false;
    }

    //【2】分离色彩通道-把一个3通道图像转换成3个单通道图像
    split(srcImage, channels);
    imageBlueChannel = channels.at(color);
    //【4】将原图的蓝色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，
    // 将得到的混合结果存到imageBlueChannel中
    addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
                logoImage, 0.5, 0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

    //【5】将三个单通道重新合并成一个三通道
    merge(channels, srcImage);

    //【6】显示效果图
    imshow("srcImage+logo", srcImage);
    return true;
}

int g_nContrastValue; //对比度值
int g_nBrightValue;   //亮度值
Mat g_srcImage, g_dstImage;
/**
 * 改变图像对比度和亮度值的回调函数
 */
void ContrastAndBright(int, void *)
{
    // 三个for循环，执行运算 g_dstImage(i,j) = a*g_srcImage(i,j) + b
    for (int y = 0; y < g_srcImage.rows; y++)
    {
        for (int x = 0; x < g_srcImage.cols; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                //0-255
                g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue * 0.01) * (g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);
            }
        }
    }

    // 显示图像
    imshow("src", g_srcImage);
    imshow("dst", g_dstImage);
}
void ContrastAndBrightTest()
{

    // 读入用户提供的图像
    g_srcImage = imread("file/img/1.jpg");
    if (!g_srcImage.data)
    {
        printf("读取g_srcImage图片错误~！ \n");
    }
    g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

    //设定对比度和亮度的初值
    g_nContrastValue = 80;
    g_nBrightValue = 80;
    namedWindow("dst");
    //创建轨迹条
    createTrackbar("Contrast", "dst", &g_nContrastValue, 300, ContrastAndBright);
    createTrackbar("Bright", "dst", &g_nBrightValue, 200, ContrastAndBright);

    //调用回调函数
    ContrastAndBright(g_nContrastValue, 0);
    ContrastAndBright(g_nBrightValue, 0);

    //按下“q”键时，程序退出
    while (char(waitKey(1)) != 'q')
    {
    }
}

bool dft()
{
    //【1】以灰度模式读取原始图像并显示
    Mat srcImage = imread("file/img/1.jpg", 0);
    if (!srcImage.data)
    {
        printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~！ \n");
        return false;
    }
    imshow("srcImage", srcImage);
    //【2】将输入图像延扩到最佳的尺寸，边界用0补充
    int m = getOptimalDFTSize(srcImage.rows);
    int n = getOptimalDFTSize(srcImage.cols);
    //将添加的像素初始化为0.
    Mat padded;
    // copyMakeBorder(InputArray src, OutputArray dst,
    //                              int top, int bottom, int left, int right,
    //                              int borderType, const Scalar& value = Scalar() )
    copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

    //【3】为傅立叶变换的结果(实部和虚部)分配存储空间。
    //将planes数组组合合并成一个多通道的数组complexI
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);

    //【4】进行就地离散傅里叶变换
    dft(complexI, complexI);

    //【5】将复数转换为幅值，即=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                    // 将多通道数组complexI分离成几个单通道数组，planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]); // planes[0] = magnitude
    Mat magnitudeImage = planes[0];

    //【6】进行对数尺度(logarithmic scale)缩放
    magnitudeImage += Scalar::all(1);
    log(magnitudeImage, magnitudeImage); //求自然对数

    //【7】剪切和重分布幅度图象限
    //若有奇数行或奇数列，进行频谱裁剪
    magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
    //重新排列傅立叶图像中的象限，使得原点位于图像中心
    int cx = magnitudeImage.cols / 2;
    int cy = magnitudeImage.rows / 2;
    Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   // ROI区域的左上
    Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  // ROI区域的右上
    Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  // ROI区域的左下
    Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI区域的右下
    //交换象限（左上与右下进行交换）
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    //交换象限（右上与左下进行交换）
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    //【8】归一化，用0到1之间的浮点值将矩阵变换为可视的图像格式
    //此句代码的OpenCV2版为：
    //normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX);
    //此句代码的OpenCV3版为:
    normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

    //【9】显示效果图
    imshow("magnitudeImage", magnitudeImage);
    waitKey();
    return true;
}

/**
 * xml、yaml file read and write
 */
void writeFile(String fileName)
{
    //初始化
    FileStorage fs(fileName, FileStorage::WRITE);
    //开始文件写入
    fs << "frameCount" << 5;
    time_t rawtime;
    // 获取当前时间
    time(&rawtime);
    fs << "calibrationDate" << asctime(localtime(&rawtime));
    Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
    Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
    fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
    fs << "features"
       << "[";
    for (int i = 0; i < 3; i++)
    {
        int x = rand() % 640;
        int y = rand() % 480;
        uchar lbp = rand() % 256;

        fs << "{:"
           << "x" << x << "y" << y << "lbp"
           << "[:";
        for (int j = 0; j < 8; j++)
            fs << ((lbp >> j) & 1);
        fs << "]"
           << "}";
    }
    fs << "]";
    // 释放文件对象
    fs.release();
}

void readFile(String fileName)
{
    //初始化
    FileStorage fs(fileName, FileStorage::READ);
    // 第一种方法，对FileNode操作
    int frameCount = (int)fs["frameCount"];
    string date;
    // 第二种方法，使用FileNode运算符>>
    fs["calibrationDate"] >> date;

    Mat cameraMatrix2, distCoeffs;
    fs["cameraMatrix"] >> cameraMatrix2;
    fs["distCoeffs"] >> distCoeffs;

    cout << "frameCount: " << frameCount << endl
         << "calibration date: " << date << endl
         << "camera matrix: " << cameraMatrix2 << endl
         << "distortion coeffs: " << distCoeffs << endl;

    FileNode features = fs["features"];
    FileNodeIterator it = features.begin(), it_end = features.end();
    int idx = 0;
    vector<uchar> lbpval;

    //使用FileNodeIterator遍历序列
    for (; it != it_end; ++it, idx++)
    {
        cout << "feature #" << idx << ": ";
        cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";
        // 我们也可以使用使用filenode >> std::vector操作符很容易的读数值阵列
        (*it)["lbp"] >> lbpval;
        for (int i = 0; i < (int)lbpval.size(); i++)
            cout << " " << (int)lbpval[i];
        cout << ")" << endl;
    }
    fs.release();
    getchar();
}

int main()
{
    //改变console字体颜色
    system("color 6F");
    String fileName = "file/txt/test.yaml";
    // ROI_AddImage();
    // LinearBlending();
    // ROI_LinearBlending();
    // MultiChannelBlending(2);
    // ContrastAndBrightTest();
    // dft();
    // writeFile(fileName);
    readFile(fileName);
    waitKey(0);
    return 0;
}