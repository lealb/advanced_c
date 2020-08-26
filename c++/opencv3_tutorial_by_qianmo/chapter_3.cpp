#include "opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void createAlphaMat(Mat &mat)
{
    for (int i = 0; i < mat.rows; ++i)
    {
        for (int j = 0; j < mat.cols; ++j)
        {
            Vec4b &rgba = mat.at<Vec4b>(i, j);
            rgba[0] = UCHAR_MAX;
            // 溢出检查 uchar 0-255
            rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
            rgba[2] = saturate_cast<uchar>((float(mat.rows - j)) / ((float)mat.rows) * UCHAR_MAX);
            rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
        }
    }
}
/**
 * create image use mat
 */
void getImg()
{
    Mat mat(480, 600, CV_8UC4);
    createAlphaMat(mat);
    vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    try
    {
        imwrite("file/img/alpha.png", mat, compression_params);
        imshow("Alpha png", mat);
        fprintf(stdout, "Success create image!");
        waitKey(0);
    }
    catch (runtime_error &e)
    {
        fprintf(stderr, "error!", e.what());
    }
}
int main(int argc, char const *argv[])
{
    String imgPath = "file/img/tt.jpg";
    String videoPath = "file/video/v_test.mp4";
    // Mat image = imread(imgPath);
    getImg();
}