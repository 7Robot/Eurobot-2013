#ifndef CANDLECOLORS_H
#define CANDLECOLORS_H

#include <opencv2/core/core.hpp>

#include "computefeaturepoints.h"
#include "matchdescriptors.h"

using namespace cv;
using namespace std;

class CandleColors
{
public:
    CandleColors(KEYPOINT keypoint, DESCRIPTOR descriptor, MATCHER matcher );

    void init(Mat imRef);

    int findColor(Mat img, Mat& imOut);
    int findColor2(std::vector<Point2f> calibPoints, Mat& imOut);

private:
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
