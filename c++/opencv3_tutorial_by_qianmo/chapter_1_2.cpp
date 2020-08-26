#include <iostream>
#include "opencv.hpp"
// #include <core.hpp>
#include "videoio.hpp"
// #include "highgui.hpp"
// #include "imgproc.hpp"
using namespace std;
using namespace cv;
/**
 * 腐蚀操作
 **/
void getStrucuring(String img)
{
    //1.load artwork img
    Mat srcImage = imread(img);
    imshow("srcImage", srcImage);
    // 进行腐蚀操作
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat dstImage;
    erode(srcImage, dstImage, element);
    imshow("dstImage", dstImage);
    waitKey(0);
}
/**
 * 均值滤波
 */
void getMeanFilter(String img)
{
    //1.load artwork img
    Mat srcImage = imread(img);
    imshow("srcImage[原图]", srcImage);
    // 2. mean filter
    Mat dstImage;
    blur(srcImage, dstImage, Size(7, 7));
    imshow("dstImage[均值滤波]", dstImage);
    waitKey(0);
}
/**
 * Canny 边缘检测
 */
void getEdgeDetection(String img)
{
    //1.load artwork img
    Mat srcImage = imread(img);
    imshow("srcImage", srcImage);
    // 2. Canny
    Mat dstImage, edge, grayImage;
    // 2.1 create dstImagt Mat as Src
    dstImage.create(srcImage.size(), srcImage.type());
    // 2.2 convent to gray image
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    // 2.3 denoise use 3*3 kernel
    blur(grayImage, edge, Size(3, 3));
    // 2.4 use Canny operator
    Canny(edge, edge, 3, 9, 3);
    //3. show
    imshow("Canny Edge Detection ", edge);
    waitKey(0);
}

int readVideo(String video)
{
    // Create a VideoCapture object and open the input file
    // If the input is the web camera, pass 0 instead of the video file name
    VideoCapture cap(video);

    // Check if camera opened successfully
    if (!cap.isOpened())
    {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    while (1)
    {
        Mat frame;
        // Capture frame-by-frame
        cap >> frame;
        // If the frame is empty, break immediately
        if (frame.empty())
            break;
        // Display the resulting frame
        imshow("Frame", frame);
        // Press  ESC on keyboard to exit
        char c = (char)waitKey(25);
        if (c == 27)
            break;
    }
    // When everything done, release the video capture object
    cap.release();
    // Closes all the frames
    destroyAllWindows();
    return 0;
}
/**
 * Turn on the camera
 * 0-rear camera
 * 1-front-facing camera
 */
int openCamera(int decice)
{
    Mat frame;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = decice;   // 0 = open default camera
    int apiID = cv::CAP_ANY; // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID + apiID);
    // check if we succeeded
    if (!cap.isOpened())
    {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;
    Mat edge;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // canny edge detection
        cvtColor(frame, edge, COLOR_BGR2GRAY);
        // kernel 3*3 2*3+1
        blur(edge, edge, Size(7, 7));
        Canny(edge, edge, 0, 30, 3);
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", edge);
        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

void testAdd()
{
    Mat srcImg = imread("file/img/dota_jugg.jpg");
    Mat logo = imread("file/img/dota_logo.jpg");
    // imshow("srcImg", srcImg);
    // imshow("logo", logo);
    // roi
    Mat imgROI = srcImg(Rect(500, 200, logo.cols, logo.rows));
    // imshow("ROI", imgROI);
    //InputArray src1, double alpha, InputArray src2,double beta, double gamma, OutputArray dst, int dtype = -1
    addWeighted(imgROI, 0.5, logo, 0.3, 0.1, imgROI);
    imshow("dstImg", srcImg);
    waitKey(0);
}
/**
 * argc 为整数，用来统计运行程序送给main函数的命令行参数的个数
 * *argv[] 字符串数组，用来存放指向字符串参数的指针数组，每个元素指向一个参数
 */
int main(int argc, char const *argv[])
{
    String imgPath = "file/img/tt.jpg";
    String videoPath = "file/video/v_test.mp4";
    // getStrucuring(imgPath);
    // getMeanFilter(imgPath);
    // getEdgeDetection(imgPath);
    // readVideo(0);
    // openCamera(1);
    testAdd();
    return 0;
}
