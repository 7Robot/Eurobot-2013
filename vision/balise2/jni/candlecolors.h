#ifndef CANDLECOLORS_H
#define CANDLECOLORS_H

#include <opencv2/core/core.hpp>

#include "computefeaturepoints.h"
#include "matchdescriptors.h"



using namespace cv;
using namespace std;

typedef enum{RED=0, BLUE=1, WHITE=2, UNKNOWN=3} color;

class CandleColors
{
public:
    CandleColors(KEYPOINT keypoint, DESCRIPTOR descriptor, MATCHER matcher );

    void init(Mat imRef);

    int findColor(Mat img, Mat& imOut);
    int findColor2(std::vector<Point2f> calibPoints, Mat& imOut);
    void setPosition(int position);

private:

    color getColor(Mat img, int x, int y);
    int candlesColor(std::vector<Point2f> candles, Mat &imOut);

    KEYPOINT keypoint;
    DESCRIPTOR descriptor;
    MATCHER matcher ;
    Mat imRef;
    int position;
    std::vector<Point2f> refPoints; // mode manuel

    ComputeFeaturePoints* computeFP;
    vector<KeyPoint> keypointsRef;
    Mat descriptorsRef;
    vector<Point2f> bougies;
};

#endif // CANDLECOLORS_H
