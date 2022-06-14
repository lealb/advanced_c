#include <iostream>
#include "opencv.hpp"
using namespace std;
using namespace cv;

#define WINDOW_NAME "test"
void getFilter(string img)
{
    Mat srcImg = imread(img);
    imshow("srcImg", srcImg);
    // box fileter
    Mat dstBoxFilterOut, dstMeanFilterOut, dstGaussianFilterOut;
    boxFilter(srcImg, dstBoxFilterOut, -1, Size(5, 5));
    // mean filter = bos fliter + normalize=true
    blur(srcImg, dstMeanFilterOut, Size(5, 5));
    // gaussiant filter
    GaussianBlur(srcImg, dstGaussianFilterOut, Size(5, 5), 0, 0);
    imshow("dstBoxFilterOut", dstBoxFilterOut);
    imshow("dstMeanFilterOut", dstMeanFilterOut);
    imshow("dstGaussianFilterOut", dstGaussianFilterOut);
    waitKey(0);
}
//LinearImageFilter
Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3; //存储图片的Mat类型
int g_nBoxFilterValue = 3;                             //方框滤波参数值
int g_nMeanBlurValue = 3;                              //均值滤波参数值
int g_nGaussianBlurValue = 3;                          //高斯滤波参数值
static void on_BoxFilter(int, void *)
{
    //方框滤波操作
    boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
    //显示窗口
    imshow("BoxFilter", g_dstImage1);
}
static void on_MeanBlur(int, void *)
{
    //均值滤波操作
    blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
    //显示窗口
    imshow("MeanBlur", g_dstImage2);
}
static void on_GaussianBlur(int, void *)
{
    //高斯滤波操作
    GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue * 2 + 1, g_nGaussianBlurValue * 2 + 1), 0, 0);
    //显示窗口
    imshow("GaussianBlur", g_dstImage3);
}
bool linearImageFilter()
{
    // 载入原图
    g_srcImage = imread("file/img/dm.jpg", 1);
    if (!g_srcImage.data)
    {
        printf("Oh，no，读取srcImage错误~！ \n");
        return false;
    }

    //克隆原图到三个Mat类型中
    g_dstImage1 = g_srcImage.clone();
    g_dstImage2 = g_srcImage.clone();
    g_dstImage3 = g_srcImage.clone();

    //g_srcImage
    namedWindow("g_srcImage", 1);
    imshow("g_srcImage", g_srcImage);

    //BoxFilter
    namedWindow("BoxFilter", 1);
    createTrackbar("kernel", "BoxFilter", &g_nBoxFilterValue, 40, on_BoxFilter);
    on_BoxFilter(g_nBoxFilterValue, 0);
    //MeanBlur
    namedWindow("MeanBlur", 1);
    createTrackbar("kernel", "MeanBlur", &g_nMeanBlurValue, 40, on_MeanBlur);
    on_MeanBlur(g_nMeanBlurValue, 0);
    //GaussianBlur
    namedWindow("GaussianBlur", 1);
    createTrackbar("kernel", "GaussianBlur", &g_nGaussianBlurValue, 40, on_GaussianBlur);
    on_GaussianBlur(g_nGaussianBlurValue, 0);

    waitKey(0);
    return true;
}

void nonLinearFilter(string img)
{
    Mat srcImg = imread(img);
    imshow("srcImg", srcImg);
    // box fileter
    Mat dstMeadianFilterOut, dstBilateralFilterOut;
    medianBlur(srcImg, dstMeadianFilterOut, 7);
    bilateralFilter(srcImg, dstBilateralFilterOut, 25, 25 * 2, 25 / 2);
    imshow("dstMeadianFilterOut", dstMeadianFilterOut);
    imshow("dstBilateralFilterOut", dstBilateralFilterOut);
    waitKey(0);
}

// dilate and erode

void testDilate(string img)
{
    Mat srcImg = imread(img);
    imshow("srcImg", srcImg);
    Mat dstDilate;
    dilate(srcImg, dstDilate, getStructuringElement(MORPH_RECT, Size(15, 15)));
    imshow("dstDilate", dstDilate);
    waitKey(0);
}
void testErode(string img)
{
    Mat srcImg = imread(img);
    imshow("srcImg", srcImg);
    Mat dstErode;
    erode(srcImg, dstErode, getStructuringElement(MORPH_RECT, Size(15, 15)));
    imshow("dstErode", dstErode);
    waitKey(0);
}

Mat g_dstImage;                   //原始图和dstImg
int g_nElementShape = MORPH_RECT; //元素结构的形状

//变量接收的TrackBar位置参数
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;

/**
 * Open/Close窗口的回调函数
 */
static void on_OpenClose(int, void *)
{
    //偏移量的定义
    int offset = g_nOpenCloseNum - g_nMaxIterationNum;   //偏移量
    int Absolute_offset = offset > 0 ? offset : -offset; //偏移量绝对值
    //自定义核
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
    //进行操作
    if (offset < 0)
        //此句代码的OpenCV2版为：
        //morphologyEx(g_srcImage, g_dstImage, CV_MOP_OPEN, element);
        //此句代码的OpenCV3版为:
        morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
    else
        //此句代码的OpenCV2版为：
        //morphologyEx(g_srcImage, g_dstImage, CV_MOP_CLOSE, element);
        //此句代码的OpenCV3版为:
        morphologyEx(g_srcImage, g_dstImage, MORPH_CLOSE, element);
    imshow("Open/Close", g_dstImage);
}

/**
 * 【Erode/Dilate窗口的回调函数
 */
static void on_ErodeDilate(int, void *)
{
    //偏移量的定义
    int offset = g_nErodeDilateNum - g_nMaxIterationNum; //偏移量
    int Absolute_offset = offset > 0 ? offset : -offset; //偏移量绝对值
    //自定义核
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
    //进行操作
    if (offset < 0)
        erode(g_srcImage, g_dstImage, element);
    else
        dilate(g_srcImage, g_dstImage, element);
    //显示图像
    imshow("Erode/Dilate", g_dstImage);
}

/**
 * 【顶帽运算/黑帽运算】窗口的回调函数
 */
static void on_TopBlackHat(int, void *)
{
    //偏移量的定义
    int offset = g_nTopBlackHatNum - g_nMaxIterationNum; //偏移量
    int Absolute_offset = offset > 0 ? offset : -offset; //偏移量绝对值
    //自定义核
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
    //进行操作
    if (offset < 0)
        morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
    else
        morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
    //显示图像
    imshow("Top/BlackHat", g_dstImage);
}
bool Morphology(string img)
{
    //载入原图
    g_srcImage = imread(img);
    if (!g_srcImage.data)
    {
        printf("Oh，no，读取srcImage错误~！ \n");
        return false;
    }

    //显示原始图
    imshow("g_srcImage", g_srcImage);

    //创建三个窗口
    namedWindow("Open/Close", 1);
    namedWindow("Erode/Dilate", 1);
    namedWindow("Top/BlackHat", 1);

    //参数赋值
    g_nOpenCloseNum = 9;
    g_nErodeDilateNum = 9;
    g_nTopBlackHatNum = 2;

    //分别为三个窗口创建滚动条
    createTrackbar("iter_value", "Open/Close", &g_nOpenCloseNum, g_nMaxIterationNum * 2 + 1, on_OpenClose);
    createTrackbar("iter_value", "Erode/Dilate", &g_nErodeDilateNum, g_nMaxIterationNum * 2 + 1, on_ErodeDilate);
    createTrackbar("iter_value", "Top/BlackHat", &g_nTopBlackHatNum, g_nMaxIterationNum * 2 + 1, on_TopBlackHat);

    //轮询获取按键信息
    while (1)
    {
        int c;

        //执行回调函数
        on_OpenClose(g_nOpenCloseNum, 0);
        on_ErodeDilate(g_nErodeDilateNum, 0);
        on_TopBlackHat(g_nTopBlackHatNum, 0);

        //获取按键
        c = waitKey(0);

        //按下键盘按键Q或者ESC，程序退出
        if ((char)c == 'q' || (char)c == 27)
            break;
        //按下键盘按键1，使用椭圆(Elliptic)结构元素结构元素MORPH_ELLIPSE
        if ((char)c == 49) //键盘按键1的ASII码为49
            g_nElementShape = MORPH_ELLIPSE;
        //按下键盘按键2，使用矩形(Rectangle)结构元素MORPH_RECT
        else if ((char)c == 50) //键盘按键2的ASII码为50
            g_nElementShape = MORPH_RECT;
        //按下键盘按键3，使用十字形(Cross-shaped)结构元素MORPH_CROSS
        else if ((char)c == 51) //键盘按键3的ASII码为51
            g_nElementShape = MORPH_CROSS;
        //按下键盘按键space，在矩形、椭圆、十字形结构元素中循环
        else if ((char)c == ' ')
            g_nElementShape = (g_nElementShape + 1) % 3;
    }
    return true;
}

// floodFill
void getFloodFill(string img)
{
    Mat srcImg = imread(img);
    imshow("srcImg", srcImg);
    Rect ccomp;
    floodFill(srcImg, Point(50, 300), Scalar(155, 255, 55), &ccomp, Scalar(20, 20, 20), Scalar(20, 20, 20));
    imshow("dstImg", srcImg);
    waitKey(0);
}

Mat g_grayImage, g_maskImage;                    //定义原始图、目标图、灰度图、掩模图
int g_nFillMode = 1;                             //漫水填充的模式
int g_nLowDifference = 20, g_nUpDifference = 20; //负差最大值、正差最大值
int g_nConnectivity = 4;                         //表示floodFill函数标识符低八位的连通值
int g_bIsColor = true;                           //是否为彩色图的标识符布尔值
bool g_bUseMask = false;                         //是否显示掩膜窗口的布尔值
int g_nNewMaskVal = 255;                         //新的重新绘制的像素值

/**
 * 鼠标消息onMouse回调函数
 */
static void onMouse(int event, int x, int y, int, void *)
{
    // 若鼠标左键没有按下，便返回
    //此句代码的OpenCV2版为：
    //if( event != CV_EVENT_LBUTTONDOWN )
    //此句代码的OpenCV3版为：
    if (event != EVENT_LBUTTONDOWN)
        return;

    Point seed = Point(x, y);
    //空范围的漫水填充，此值设为0，否则设为全局的g_nLowDifference
    int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;
    int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;

    //标识符的0~7位为g_nConnectivity，8~15位为g_nNewMaskVal左移8位的值，16~23位为CV_FLOODFILL_FIXED_RANGE或者0。
    //此句代码的OpenCV2版为：
    //int flags = g_nConnectivity + (g_nNewMaskVal << 8) +(g_nFillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
    //此句代码的OpenCV3版为：
    int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

    //随机生成bgr值
    int b = (unsigned)theRNG() & 255; //随机返回一个0~255之间的值
    int g = (unsigned)theRNG() & 255; //随机返回一个0~255之间的值
    int r = (unsigned)theRNG() & 255; //随机返回一个0~255之间的值
    Rect ccomp;                       //定义重绘区域的最小边界矩形区域

    Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r * 0.299 + g * 0.587 + b * 0.114); //在重绘区域像素的新值，若是彩色图模式，取Scalar(b, g, r)；若是灰度图模式，取Scalar(r*0.299 + g*0.587 + b*0.114)

    Mat dst = g_bIsColor ? g_dstImage : g_grayImage; //目标图的赋值
    int area;

    if (g_bUseMask)
    {
        //此句代码的OpenCV2版为：
        //threshold(g_maskImage, g_maskImage, 1, 128, CV_THRESH_BINARY);
        //此句代码的OpenCV3版为：
        threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);
        area = floodFill(dst, g_maskImage, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
                         Scalar(UpDifference, UpDifference, UpDifference), flags);
        imshow("mask", g_maskImage);
    }
    else
    {
        area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
                         Scalar(UpDifference, UpDifference, UpDifference), flags);
    }

    imshow("dstImg", dst);
    cout << area << " 个像素被重绘\n";
}

int floodFillAll(string img)
{
    g_srcImage = imread(img, 1);

    if (!g_srcImage.data)
    {
        printf("读取图片image0错误~！ \n");
        return false;
    }

    g_srcImage.copyTo(g_dstImage);                                         //拷贝源图到目标图
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);                     //转换三通道的image0到灰度图
    g_maskImage.create(g_srcImage.rows + 2, g_srcImage.cols + 2, CV_8UC1); //利用image0的尺寸来初始化掩膜mask

    //此句代码的OpenCV2版为：
    //namedWindow( "dstImg",CV_WINDOW_AUTOSIZE );
    //此句代码的OpenCV2版为：
    namedWindow("dstImg", WINDOW_AUTOSIZE);

    //创建Trackbar
    createTrackbar("negative max value", "dstImg", &g_nLowDifference, 255, 0);
    createTrackbar("positive max value", "dstImg", &g_nUpDifference, 255, 0);

    //鼠标回调函数
    setMouseCallback("dstImg", onMouse, 0);

    //循环轮询按键
    while (1)
    {
        //先显示dstImg
        imshow("dstImg", g_bIsColor ? g_dstImage : g_grayImage);

        //获取键盘按键
        int c = waitKey(0);
        //判断ESC是否按下，若按下便退出
        if ((c & 255) == 27)
        {
            cout << "程序退出...........\n";
            break;
        }

        //根据按键的不同，进行各种操作
        switch ((char)c)
        {
            //如果键盘“1”被按下，dstImg在在灰度图，彩色图之间互换
        case '1':
            if (g_bIsColor) //若原来为彩色，转为灰度图，并且将掩膜mask所有元素设置为0
            {
                cout << "键盘“1”被按下，切换彩色/灰度模式，当前操作为将【彩色模式】切换为【灰度模式】\n";
                cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
                g_maskImage = Scalar::all(0); //将mask所有元素设置为0
                g_bIsColor = false;           //将标识符置为false，表示当前图像不为彩色，而是灰度
            }
            else //若原来为灰度图，便将原来的彩图image0再次拷贝给image，并且将掩膜mask所有元素设置为0
            {
                cout << "键盘“1”被按下，切换彩色/灰度模式，当前操作为将【彩色模式】切换为【灰度模式】\n";
                g_srcImage.copyTo(g_dstImage);
                g_maskImage = Scalar::all(0);
                g_bIsColor = true; //将标识符置为true，表示当前图像模式为彩色
            }
            break;
            //如果键盘按键“2”被按下，显示/隐藏掩膜窗口
        case '2':
            if (g_bUseMask)
            {
                destroyWindow("mask");
                g_bUseMask = false;
            }
            else
            {
                namedWindow("mask", 0);
                g_maskImage = Scalar::all(0);
                imshow("mask", g_maskImage);
                g_bUseMask = true;
            }
            break;
            //如果键盘按键“3”被按下，恢复原始图像
        case '3':
            cout << "按键“3”被按下，恢复原始图像\n";
            g_srcImage.copyTo(g_dstImage);
            cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
            g_maskImage = Scalar::all(0);
            break;
            //如果键盘按键“4”被按下，使用空范围的漫水填充
        case '4':
            cout << "按键“4”被按下，使用空范围的漫水填充\n";
            g_nFillMode = 0;
            break;
            //如果键盘按键“5”被按下，使用渐变、固定范围的漫水填充
        case '5':
            cout << "按键“5”被按下，使用渐变、固定范围的漫水填充\n";
            g_nFillMode = 1;
            break;
            //如果键盘按键“6”被按下，使用渐变、浮动范围的漫水填充
        case '6':
            cout << "按键“6”被按下，使用渐变、浮动范围的漫水填充\n";
            g_nFillMode = 2;
            break;
            //如果键盘按键“7”被按下，操作标志符的低八位使用4位的连接模式
        case '7':
            cout << "按键“7”被按下，操作标志符的低八位使用4位的连接模式\n";
            g_nConnectivity = 4;
            break;
            //如果键盘按键“8”被按下，操作标志符的低八位使用8位的连接模式
        case '8':
            cout << "按键“8”被按下，操作标志符的低八位使用8位的连接模式\n";
            g_nConnectivity = 8;
            break;
        }
    }

    return 0;
}

void testresize()
{
    Mat srcImage = imread("file/img/1.jpg"); //工程目录下应该有一张名为1.jpg的素材图
    Mat tmpImage, dstImage1, dstImage2;      //临时变量和目标图的定义
    tmpImage = srcImage;                     //将原始图赋给临时变量
    //显示原始图
    imshow("srcImage", srcImage);
    //进行尺寸调整操作
    resize(tmpImage, dstImage1, Size(tmpImage.cols / 2, tmpImage.rows / 2), (0, 0), (0, 0), 3);
    resize(tmpImage, dstImage2, Size(tmpImage.cols * 2, tmpImage.rows * 2), (0, 0), (0, 0), 3);
    //显示效果图
    imshow("dstImage1", dstImage1);
    imshow("dstImage2", dstImage2);
    waitKey(0);
}

void testPyrUpDown(string img)
{
    Mat srcImage = imread(img);               //工程目录下应该有一张名为1.jpg的素材图
    Mat tmpImage, dstImage_up, dstImage_down; //临时变量和目标图的定义
    tmpImage = srcImage;                      //将原始图赋给临时变量
    //显示原始图
    imshow("srcImage", srcImage);
    //进行向上取样操作
    pyrUp(tmpImage, dstImage_up, Size(tmpImage.cols * 2, tmpImage.rows * 2));
    pyrDown(tmpImage, dstImage_down, Size(tmpImage.cols / 2, tmpImage.rows / 2));
    //显示效果图
    imshow("dstImage_up", dstImage_up);
    imshow("dstImage_down", dstImage_down);
    waitKey(0);
}

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
/**
 * 自定义的阈值回调函数
 * 0- 二进制阈值 
 * 1- 反二进制阈值 
 * 2- 截断阈值 
 * 3- 反阈值化为0 
 * 4- 阈值化为0
 */
void on_Threshold(int, void *)
{
    //调用阈值函数
    threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
    //更新效果图
    imshow(WINDOW_NAME, g_dstImage);
}

bool testThreshold(string img)
{
    g_srcImage = imread(img);
    if (!g_srcImage.data)
    {
        printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n");
        return false;
    }
    imshow("g_srcImage", g_srcImage);
    //【2】存留一份原图的灰度图
    cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
    //【3】创建窗口并显示原始图
    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    //【4】创建滑动条来控制阈值
    createTrackbar("mode",
                   WINDOW_NAME, &g_nThresholdType,
                   4, on_Threshold);

    createTrackbar("value",
                   WINDOW_NAME, &g_nThresholdValue,
                   255, on_Threshold);
    //【5】初始化自定义的阈值回调函数
    on_Threshold(0, 0);
    waitKey(0);
    return true;
}

int main(int argc, char **argv)
{
    string img = "file/img/fill.jpg";
    // getFilter(img);
    // linearImageFilter();
    // nonLinearFilter(img);
    // testDilate(img);
    // testErode(img);
    // Morphology(img);
    // getFloodFill(img);
    //floodFillAll(img);
    // testresize();
    // testPyrUpDown(img);
    testThreshold(img);
    return 0;
}