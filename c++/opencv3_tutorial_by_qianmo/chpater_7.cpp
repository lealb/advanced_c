#include <iostream>
#include <opencv.hpp>
using namespace std;
using namespace cv;

void testCanny(string img)
{

    Mat srcImg = imread(img);
    imshow("srcImg", srcImg);

    Mat dstImg, edge, grayImg;
    //1. 创建同类型大小的矩阵
    dstImg.create(srcImg.size(), srcImg.type());
    //2. 灰度化处理
    cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
    //3.使用kernel3*3 降噪
    blur(grayImg, edge, Size(3, 3));
    //4. 执行Canny算子
    Canny(edge, edge, 3, 9, 3);
    // 5.灰度图
    imshow("grayImg", edge);
    dstImg = Scalar::all(0);
    // 6.恢复彩色图
    srcImg.copyTo(dstImg, edge);
    imshow("dstImage", dstImg);
    waitKey(0);
}

void testSobel(string img)
{
    Mat srcImg = imread(img);
    imshow("srcImg", srcImg);

    Mat gradX, gradY;
    Mat absGradX, absGradY, dstImg;
    // x
    Sobel(srcImg, gradX, CV_16S, 1, 0, 3, 1, 1);
    convertScaleAbs(gradX, absGradX);
    imshow("absGradX", absGradX);
    //Y
    Sobel(srcImg, gradY, CV_16S, 0, 1, 3, 1, 1);
    convertScaleAbs(gradY, absGradY);
    imshow("absGradY", absGradY);
    // merge x and y
    addWeighted(absGradX, 0.5, absGradY, 0.5, 0, dstImg);
    imshow("dstImg", dstImg);
    waitKey(0);
}

void testLaplacian(string img)
{
    Mat srcImg = imread(img);
    imshow("srcImg", srcImg);

    Mat dstImg, grayImg, absDstImg;
    // 高斯滤波消除噪声
    GaussianBlur(srcImg, srcImg, Size(3, 3), 0, 0);
    //灰度图
    cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
    // Laplacian
    Laplacian(grayImg, dstImg, CV_16S, 3, 1, 0);
    // 计算绝对值
    convertScaleAbs(dstImg, absDstImg);
    imshow("absDstImg", absDstImg);
    waitKey(0);
}

void testScarr(string img)
{
    Mat srcImg = imread(img);
    imshow("srcImg", srcImg);

    Mat gradX, gradY;
    Mat absGradX, absGradY, dstImg;
    // x
    Scharr(srcImg, gradX, CV_16S, 1, 0, 1, 0, 1);
    convertScaleAbs(gradX, absGradX);
    imshow("absGradX", absGradX);
    //Y
    Scharr(srcImg, gradY, CV_16S, 0, 1, 1, 0, 1);
    convertScaleAbs(gradY, absGradY);
    imshow("absGradY", absGradY);
    // merge x and y
    addWeighted(absGradX, 0.5, absGradY, 0.5, 0, dstImg);
    imshow("dstImg", dstImg);
    waitKey(0);
}

void testHl(string img)
{
    //【1】载入原始图和Mat变量定义
    Mat srcImage = imread(img);
    imshow("srcImage", srcImage);
    Mat midImage, dstImage; //临时变量和目标图的定义

    //【2】进行边缘检测和转化为灰度图
    Canny(srcImage, midImage, 50, 200, 3);        //进行一此canny边缘检测
    cvtColor(midImage, dstImage, COLOR_GRAY2BGR); //转化边缘检测后的图为灰度图

    //【3】进行霍夫线变换
    //定义一个矢量结构lines用于存放得到的线段矢量集合
    vector<Vec2f> lines;
    HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);

    //【4】依次在图中绘制出每条线段
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        //此句代码的OpenCV2版为:
        //line( dstImage, pt1, pt2, Scalar(55,100,195), 1, CV_AA);
        //此句代码的OpenCV3版为:
        line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
    }
    imshow("midImage", midImage);
    imshow("dstImage", dstImage);

    waitKey(0);
}

void testHlF(string img)
{
    //【1】载入原始图和Mat变量定义
    Mat srcImage = imread(img);
    imshow("srcImage", srcImage);
    Mat midImage, dstImage; //临时变量和目标图的定义

    //【2】进行边缘检测和转化为灰度图
    Canny(srcImage, midImage, 50, 200, 3);        //进行一此canny边缘检测
    cvtColor(midImage, dstImage, COLOR_GRAY2BGR); //转化边缘检测后的图为灰度图
    // 进行霍夫变换
    vector<Vec4i> lines;
    HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);
    // 绘制直线
    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];
        line(dstImage, Point(l[0], l[1]), Point(l[3], l[4]), Scalar(186, 88, 255), 1, LINE_AA);
    }
    imshow("midImage", midImage);
    imshow("dstImage", dstImage);

    waitKey(0);
}
void testHlC(string img)
{

    //【1】载入原始图和Mat变量定义
    Mat srcImage = imread(img);
    imshow("srcImage", srcImage);
    Mat midImage, dstImage;                       //临时变量和目标图的定义
                                                  //【3】转为灰度图并进行图像平滑
    cvtColor(srcImage, midImage, COLOR_BGR2GRAY); //转化边缘检测后的图为灰度图
    GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);

    //【4】进行霍夫圆变换
    vector<Vec3f> circles;
    HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);

    //【5】依次在图中绘制出圆
    for (size_t i = 0; i < circles.size(); i++)
    {
        //参数定义
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        //绘制圆心
        circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
        //绘制圆轮廓
        circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
    }
    imshow("dstImage", srcImage);
    waitKey(0);
}

void testReMap(string img)
{
    Mat srcImage, dstImage;
    Mat map_x, map_y;

    srcImage = imread(img);
    imshow("srcImage", srcImage);

    // 效果图
    dstImage.create(srcImage.size(), srcImage.type());
    map_x.create(srcImage.size(), CV_32FC1);
    map_y.create(srcImage.size(), CV_32FC1);

    for (size_t j = 0; j < srcImage.rows; j++)
    {
        for (size_t i = 0; i < srcImage.cols; i++)
        {
            //change map_x and map_y
            map_x.at<float>(j, i) = static_cast<float>(srcImage.cols - i);
            map_y.at<float>(j, i) = static_cast<float>(j);
        }
    }
    remap(srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_DEFAULT, Scalar(0, 0, 0));
    imshow("dstImage", dstImage);
    waitKey(0);
}

void testGeometricTransforms(string img)
{

    Mat srcImage = imread(img);
    imshow("srcImage", srcImage);

    //Set your 3 points to calculate the  Affine Transform
    Point2f srcTri[3]{
        Point2f(0.f, 0.f),
        Point2f(srcImage.cols - 1.f, 0.f),
        Point2f(0.f, srcImage.rows - 1.f)};

    Point2f dstTri[3]{
        Point2f(0.f, srcImage.rows * 0.33f),
        Point2f(srcImage.cols * 0.85f, srcImage.rows * 0.25f),
        Point2f(srcImage.cols * 0.15f, srcImage.rows * 0.7f)};

    //! [Get the Affine Transform]
    Mat warp_mat = getAffineTransform(srcTri, dstTri);

    //! [Apply the Affine Transform just found to the src image]
    /// Set the dst image the same type and size as src
    Mat warp_dst = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

    warpAffine(srcImage, warp_dst, warp_mat, warp_dst.size());

    /** Rotating the image after Warp */

    //! [Compute a rotation matrix with respect to the center of the image]
    Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
    double angle = -50.0;
    double scale = 0.6;
    //! [Get the rotation matrix with the specifications above]
    Mat rot_mat = getRotationMatrix2D(center, angle, scale);

    //! [Rotate the warped image]
    Mat warp_rotate_dst;
    warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());

    imshow("Warp", warp_dst);
    imshow("Warp + Rotate", warp_rotate_dst);
    waitKey(0);
}

void testEqualizeHist(string img)
{
    Mat srcImage = imread(img);
    imshow("srcImage", srcImage);
    //! [Convert to grayscale]
    cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);

    //! [Apply Histogram Equalization]
    Mat dstImage;
    equalizeHist(srcImage, dstImage);

    imshow("Source image", srcImage);
    imshow("Equalized Image", dstImage);
    waitKey(0);
}
int main()
{
    string img = "file/img/huidu.jpg";
    // testCanny(img);
    // testSobel(img);
    // testLaplacian(img);
    // testScarr(img);
    // testHl(img);
    // testHlF(img);
    // testHlC(img);
    // testReMap(img);
    // testGeometricTransforms(img);
    testEqualizeHist(img);
    return 0;
}