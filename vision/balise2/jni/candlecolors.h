#ifndef CANDLECOLORS_H
#define CANDLECOLORS_H

#include <opencv2/core/core.hpp>

#include "computefeaturepoints.h"
#include "matchdescriptors.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

using namespace cv;
using namespace std;

typedef enum{RED, BLUE, WHITE, UNKNOWN} color;

class CandleColors
{
public:
    CandleColors(KEYPOINT keypoint, DESCRIPTOR descriptor, MATCHER matcher );

    void init(Mat imRef);

    int findColor(Mat img, Mat& imOut);
    int findColor2(std::vector<Point2f> calibPoints, Mat& imOut);

private:

    color getColor(Mat img, int x, int y);

    KEYPOINT keypoint;
    DESCRIPTOR descriptor;
    MATCHER matcher ;
    Mat imRef;

    ComputeFeaturePoints* computeFP;
    vector<KeyPoint> keypointsRef;
    Mat descriptorsRef;
    vector<Point2f> bougies;
};

#endif // CANDLECOLORS_H
