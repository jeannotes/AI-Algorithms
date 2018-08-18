/**
 * @file lsd_opencv_example.cpp
 *
 * Test the LSD algorithm with OpenCV
 */
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "lsd.h"

using namespace cv;

void Erosion(Mat &src, int erosion_size) {
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                                        Point(erosion_size, erosion_size));

    /// Apply the erosion operation
    erode(src, src, element);
    //imshow( "Erosion Demo", erosion_dst );
}

void Dilation(Mat &src, int dilation_size) {
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                        Point(dilation_size, dilation_size));
    /// Apply the dilation operation
    dilate(src, src, element);
}

int main(int argc, char **argv) {
    if (argc < 2 || argc > 2) {
        std::cout << "Usage: lsd_opencv_example imageName" << std::endl;
        return -1;
    }
    cv::Mat src = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cv::Mat tmp, src_gray;
    Erosion(src, 8);
    Dilation(src, 9);
    cv::cvtColor(src, tmp, CV_RGB2GRAY);
    tmp.convertTo(src_gray, CV_64FC1);
    cv::imwrite("src_gray.pgm", src_gray);
    int cols = src_gray.cols;
    int rows = src_gray.rows;

    image_double image = new_image_double(cols, rows);
    image->data = src_gray.ptr<double>(0);
    ntuple_list ntl = lsd(image);

    cv::Mat lsd = cv::Mat::zeros(rows, cols, CV_8UC1);
    cv::Point pt1, pt2;
    for (int j = 0; j != ntl->size; ++j) {
        pt1.x = int(ntl->values[0 + j * ntl->dim]);
        pt1.y = int(ntl->values[1 + j * ntl->dim]);
        pt2.x = int(ntl->values[2 + j * ntl->dim]);
        pt2.y = int(ntl->values[3 + j * ntl->dim]);
        int width = int(ntl->values[4 + j * ntl->dim]) / 2;
        cv::line(lsd, pt1, pt2, cv::Scalar(255), width, CV_AA);
    }
    free_ntuple_list(ntl);

    cv::namedWindow("src", CV_WINDOW_AUTOSIZE);
    cv::imshow("src", src);
    cv::namedWindow("lsd", CV_WINDOW_AUTOSIZE);
    cv::imshow("lsd", lsd);

    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PXM_BINARY);
    //compression_params.push_back(1);
    cv::imwrite("lsd.pgm", lsd);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}

