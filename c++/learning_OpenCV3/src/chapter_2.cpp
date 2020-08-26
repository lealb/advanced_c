#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

int g_slider_position = 0;
int g_run = 1, g_dontset = 0; //start out in single step mode
cv::VideoCapture g_cap;

void onTrackbarSlide(int pos, void *)
{

    g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);

    if (!g_dontset)
        g_run = 1;

    g_dontset = 0;
}

void help(char **argv)
{
    std::cout << "\n"
              << "2-04: Addeing a trackbar to a basic viewer for moving w/in the video file \n"
              << argv[0] << " <path/video>\n"
              << "For example:\n"
              << argv[0] << " ../tree.avi\n"
              << std::endl;
}

int testRe(std::string video)
{
    cv::namedWindow("Example 2-4", cv::WINDOW_AUTOSIZE);

    g_cap.open(video);
    std::cout << g_cap.isOpened() << std::endl;
    int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "Video has " << frames << " frames of dimensions("
              << tmpw << ", " << tmph << ")." << std::endl;

    cv::createTrackbar(
        "Position",
        "Example 2-4",
        &g_slider_position,
        frames,
        onTrackbarSlide);
    cv::Mat frame;

    for (;;)
    {

        if (g_run != 0)
        {
            g_cap >> frame;
            if (frame.empty())
                break;
            int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
            g_dontset = 1;

            cv::setTrackbarPos("Position", "Example 2-4", current_pos);
            cv::imshow("Example 2-4", frame);
            g_run -= 1;
        }

        char c = (char)cv::waitKey(10);

        if (c == 's')
        { // single step
            g_run = 1;
            std::cout << "Single step, run = " << g_run << std::endl;
        }

        if (c == 'r')
        { // run mode
            g_run = -1;
            std::cout << "Run mode, run = " << g_run << std::endl;
        }

        if (c == 27)
            break;
    }

    return (0);
}

void testReadVideo(std::string video)
{
    cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap=cv::VideoCapture(video);
    cv::Mat frame;
    for (;;)
    {
        std::cout << cap.isOpened()<<std::endl;
        cap >> frame;
        if (frame.empty())
        break;
        cv::imshow("Video", frame);
        cv::waitKey(0);
    }
}
int main(int argc, char **argv)
{
    // D:\02-Money\leetcode\c++\learning_OpenCV3\file\video\v_test.mp4
    //c++/learning_OpenCV3/file/video/v_test.mp4
    std::string video = "c++/learning_OpenCV3/file/video/v_test.mp4";
    testReadVideo(video);
    // testRe(video);
    return 0;
}