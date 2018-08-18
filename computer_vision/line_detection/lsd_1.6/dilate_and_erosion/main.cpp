#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

/** Function Headers */
void Erosion(Mat src, int erosion_size);
void Dilation(Mat src, int dilation_size);

/** @function main */
int main(int argc, char **argv) {
    /// Load an image
    src = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    if (!src.data) {
        return -1;
    }
    /*
    /// Create windows
    namedWindow( "Erosion Demo", CV_WINDOW_AUTOSIZE );
    namedWindow( "Dilation Demo", CV_WINDOW_AUTOSIZE );
    cvMoveWindow( "Dilation Demo", src.cols, 0 );

    /// Create Erosion Trackbar
    createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
                    &erosion_elem, max_elem,
                    Erosion );

    createTrackbar( "Kernel size:\n 2n +1", "Erosion Demo",
                    &erosion_size, max_kernel_size,
                    Erosion );

    /// Create Dilation Trackbar
    createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
                    &dilation_elem, max_elem,
                    Dilation );

    createTrackbar( "Kernel size:\n 2n +1", "Dilation Demo",
                    &dilation_size, max_kernel_size,
                    Dilation );*/

    /// Default start
    Erosion(src, 10);
    Dilation(erosion_dst, 12);
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PXM_BINARY);
    compression_params.push_back(1);
    imwrite("3_3.pgm", dilation_dst, compression_params);
    //imshow( "Dilation Demo", dilation_dst );
    //waitKey(0);
    return 0;
}

/**  @function Erosion  */
void Erosion(Mat src, int erosion_size) {
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                                        Point(erosion_size, erosion_size));

    /// Apply the erosion operation
    erode(src, erosion_dst, element);
    //imshow( "Erosion Demo", erosion_dst );
}

/** @function Dilation */
void Dilation(Mat src, int dilation_size) {
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                        Point(dilation_size, dilation_size));
    /// Apply the dilation operation
    dilate(src, dilation_dst, element);
}