#include <iostream>
#include "opencv.hpp"
using namespace std;
using namespace cv;

// 图像轮廓与图像分割修复

void testDrawContours(string img)
{
    //模式0 灰度
    Mat srcImage = imread(img, 0);
    imshow("srcImage", srcImage);

    //【2】初始化结果图
    Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

    //【3】srcImage取大于阈值119的那部分
    srcImage = srcImage > 119;
    imshow("get_srcImage", srcImage);

    //【4】定义轮廓和层次结构
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    //【5】查找轮廓
    //此句代码的OpenCV2版为：
    //findContours( srcImage, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    //此句代码的OpenCV3版为：
    findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    // 【6】遍历所有顶层的轮廓， 以随机颜色绘制出每个连接组件颜色
    int index = 0;
    for (; index >= 0; index = hierarchy[index][0])
    {
        Scalar color(rand() & 255, rand() & 255, rand() & 255);
        //此句代码的OpenCV2版为：
        //drawContours( dstImage, contours, index, color, CV_FILLED, 8, hierarchy );
        //此句代码的OpenCV3版为：
        drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
    }

    //【7】显示最后的轮廓图
    imshow("dstImage", dstImage);

    waitKey(0);
}
//
void testConvexHull()
{
    Mat image(600, 600, CV_8UC3);
    RNG &rng = theRNG();

    while (true)
    {
        char key;
        int count = (unsigned)rng % 100 + 3;
        vector<Point> points;

        // 坐标
        for (size_t i = 0; i < count; i++)
        {
            Point point;
            point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
            point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
            points.push_back(point);
        }

        // convexHull
        vector<int> hull;
        convexHull(Mat(points), hull, true);

        // draw random points
        image = Scalar::all(0);
        for (size_t i = 0; i < count; i++)
        {
            circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);
        }

        //param
        int hullcount = (int)hull.size();
        Point p0 = points[hull[hullcount - 1]];
        for (size_t i = 0; i < hullcount; i++)
        {
            Point p = points[hull[i]];
            line(image, p0, p, Scalar(255, 255, 255), 2, LINE_AA);
            p0 = p;
        }

        imshow("dstImage", image);

        // esc
        key = (char)waitKey();
        if (key == 27 || key == 'q' || key == 'Q')
        {
            break;
        }
    }
}

Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 50;     //阈值
int g_nMaxThresh = 255; //阈值最大值
RNG g_rng(12345);       //随机数生成器
void on_ContoursChange(int, void *)
{
    //定义一些参数
    Mat threshold_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    // 使用Threshold检测边缘
    threshold(g_grayImage, threshold_output, g_nThresh, 255, THRESH_BINARY);

    // 找出轮廓
    findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    // 多边形逼近轮廓 + 获取矩形和圆形边界框
    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f> center(contours.size());
    vector<float> radius(contours.size());

    for (unsigned int i = 0; i < contours.size(); i++)
    {
        //用指定精度逼近多边形曲线
        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        //计算点集的最外面（up-right）矩形边界
        boundRect[i] = boundingRect(Mat(contours_poly[i]));
        //对给定的 2D点集，寻找最小面积的包围圆形
        minEnclosingCircle(contours_poly[i], center[i], radius[i]);
    }

    // 绘制多边形轮廓 + 包围的矩形框 + 圆形框
    Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
    for (int unsigned i = 0; i < contours.size(); i++)
    {
        //随机设置颜色
        Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
        //绘制轮廓
        drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        //绘制矩形
        rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
        //绘制圆
        circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
    }

    // 显示效果图窗口
    namedWindow("dstImage", WINDOW_AUTOSIZE);
    imshow("dstImage", drawing);
}

bool testRectangle(string img)
{

    //【1】载入3通道的原图像
    g_srcImage = imread(img, 1);
    if (!g_srcImage.data)
    {
        printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n");
        return false;
    }

    //【2】得到原图的灰度图像并进行平滑
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
    blur(g_grayImage, g_grayImage, Size(3, 3));

    //【3】创建原始图窗口并显示
    namedWindow("g_srcImage", WINDOW_AUTOSIZE);
    imshow("g_srcImage", g_srcImage);

    //【4】设置滚动条并调用一次回调函数
    createTrackbar("threshold", "g_srcImage", &g_nThresh, g_nMaxThresh, on_ContoursChange);
    on_ContoursChange(0, 0);
    waitKey(0);
    return true;
}

// 分水岭算法
Mat g_maskImage;
Point prevPt(-1, -1);

static void on_Mouse(int event, int x, int y, int flags, void *)
{
    //处理鼠标不在窗口中的情况
    if (x < 0 || x >= g_srcImage.cols || y < 0 || y >= g_srcImage.rows)
        return;

    //处理鼠标左键相关消息
    if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
        prevPt = Point(-1, -1);
    else if (event == EVENT_LBUTTONDOWN)
        prevPt = Point(x, y);

    //鼠标左键按下并移动，绘制出白色线条
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
    {
        Point pt(x, y);
        if (prevPt.x < 0)
            prevPt = pt;
        line(g_maskImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
        line(g_srcImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
        prevPt = pt;
        imshow("g_srcImage", g_srcImage);
    }
}

bool testWatershed(string img)
{
    //【1】载入原图并显示，初始化掩膜和灰度图
    g_srcImage = imread(img, 1);
    imshow("g_srcImage", g_srcImage);
    Mat srcImage, grayImage;
    g_srcImage.copyTo(srcImage);
    cvtColor(g_srcImage, g_maskImage, COLOR_BGR2GRAY);
    cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
    g_maskImage = Scalar::all(0);

    //【2】设置鼠标回调函数
    setMouseCallback("g_srcImage", on_Mouse, 0);

    //【3】轮询按键，进行处理
    while (1)
    {
        //获取键值
        int c = waitKey(0);

        //若按键键值为ESC时，退出
        if ((char)c == 27)
            break;

        //按键键值为2时，恢复源图
        if ((char)c == '2')
        {
            g_maskImage = Scalar::all(0);
            srcImage.copyTo(g_srcImage);
            imshow("g_srcImage", g_srcImage);
        }

        //若检测到按键值为1或者空格，则进行处理
        if ((char)c == '1' || (char)c == ' ')
        {
            //定义一些参数
            int i, j, compCount = 0;
            vector<vector<Point>> contours;
            vector<Vec4i> hierarchy;

            //寻找轮廓
            findContours(g_maskImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

            //轮廓为空时的处理
            if (contours.empty())
                continue;

            //拷贝掩膜
            Mat maskImage(g_maskImage.size(), CV_32S);
            maskImage = Scalar::all(0);

            //循环绘制出轮廓
            for (int index = 0; index >= 0; index = hierarchy[index][0], compCount++)
                drawContours(maskImage, contours, index, Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);

            //compCount为零时的处理
            if (compCount == 0)
                continue;

            //生成随机颜色
            vector<Vec3b> colorTab;
            for (i = 0; i < compCount; i++)
            {
                int b = theRNG().uniform(0, 255);
                int g = theRNG().uniform(0, 255);
                int r = theRNG().uniform(0, 255);

                colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
            }

            //计算处理时间并输出到窗口中
            double dTime = (double)getTickCount();
            watershed(srcImage, maskImage);
            dTime = (double)getTickCount() - dTime;
            printf("\time = %gms\n", dTime * 1000. / getTickFrequency());

            //双层循环，将分水岭图像遍历存入watershedImage中
            Mat watershedImage(maskImage.size(), CV_8UC3);
            for (i = 0; i < maskImage.rows; i++)
                for (j = 0; j < maskImage.cols; j++)
                {
                    int index = maskImage.at<int>(i, j);
                    if (index == -1)
                        watershedImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
                    else if (index <= 0 || index > compCount)
                        watershedImage.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
                    else
                        watershedImage.at<Vec3b>(i, j) = colorTab[index - 1];
                }

            //混合灰度图和分水岭效果图并显示最终的窗口
            watershedImage = watershedImage * 0.5 + grayImage * 0.5;
            imshow("watershedImage", watershedImage);
        }
    }

    return 0;
}

// 图像修补

int main(int argc, char const *argv[])
{
    string img = "file/img/dm.jpg";
    // testDrawContours(img);
    // testConvexHull();
    // testRectangle(img);
    testWatershed(img);
    return 0;
}
