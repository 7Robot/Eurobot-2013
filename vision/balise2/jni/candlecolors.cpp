#include "candlecolors.h"

#include "computehomography.h"

#include <android/log.h>

#define LOG_TAG "Msg"
#define printf(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))




CandleColors::CandleColors(KEYPOINT keypoint, DESCRIPTOR descriptor, MATCHER matcher )
{
    this->keypoint = keypoint;
    this->descriptor = descriptor;
    this->matcher = matcher;
    bougies.push_back(Point2f(380 , 116));
    bougies.push_back(Point2f(380 , 150));
    bougies.push_back(Point2f(380 , 189));
    bougies.push_back(Point2f(412 , 91));
    bougies.push_back(Point2f(416 , 116));
    bougies.push_back(Point2f(413 , 146));
    bougies.push_back(Point2f(415 , 184));
    bougies.push_back(Point2f(410 , 220));
}

void CandleColors::init(Mat imRef)
{
    this->imRef    = imRef;
    computeFP      = new ComputeFeaturePoints(imRef, keypoint, descriptor, false);
    keypointsRef   = computeFP->keypoints;
    descriptorsRef = computeFP->descriptors.clone();
}

int CandleColors::findColor(Mat img, Mat &imOut)
{
    computeFP = new ComputeFeaturePoints(img, keypoint, descriptor, false);
    printf("Matching %d %d\n", descriptorsRef.cols, computeFP->descriptors.cols);
    if (computeFP->descriptors.cols == 0)
        return 4;
    Matchdescriptors matchdescriptors = Matchdescriptors(descriptor, matcher, descriptorsRef, computeFP->descriptors);
    std::vector< DMatch > good_matches = matchdescriptors.good_matches;
    printf("Matching done\n");

    if (good_matches.size() < 4)
    {
        return 1;
    }

    // Compute Homography
    ComputeHomography computeHomography = ComputeHomography();
    computeHomography.computeHomography(keypointsRef, computeFP->keypoints, good_matches);
    std::vector<Point2f> scene_corners = computeHomography.applyHomography(imRef);

//    if (!computeHomography.validateTransformation()) {
//        return 2;
//    }

    std::vector<Point2f> candles = computeHomography.applyHomography(bougies);
    //-- Show detected matches
    drawMatches( imRef, keypointsRef, img, computeFP->keypoints,
               good_matches, imOut, Scalar::all(-1), Scalar::all(-1),
               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );


    if (good_matches.size() >= 4)
    {
        //-- Draw lines between the corners (the mapped object in the scene - image_2 )
        line( imOut, scene_corners[0] + Point2f( imRef.cols, 0), scene_corners[1] + Point2f( imRef.cols, 0), Scalar( 0, 255, 0), 4 );
        line( imOut, scene_corners[1] + Point2f( imRef.cols, 0), scene_corners[2] + Point2f( imRef.cols, 0), Scalar( 0, 255, 0), 4 );
        line( imOut, scene_corners[2] + Point2f( imRef.cols, 0), scene_corners[3] + Point2f( imRef.cols, 0), Scalar( 0, 255, 0), 4 );
        line( imOut, scene_corners[3] + Point2f( imRef.cols, 0), scene_corners[0] + Point2f( imRef.cols, 0), Scalar( 0, 255, 0), 4 );

    }

    for (int i=0; i<candles.size(); i++)
    {
        candles[i].x += imRef.cols;
        printf("%d %f %f\n", imRef.cols, candles[i].x, candles[i].y);
        circle( imOut, candles[i], 8, Scalar(0,255,0), -1, 8);
    }

    return 0;
}

int CandleColors::findColor2(std::vector<Point2f> calibPoints, Mat& imOut)
{
	std::vector<Point2f> refPoints;
	refPoints.push_back(Point2f(448,66));
	refPoints.push_back(Point2f(249,153));
	refPoints.push_back(Point2f(252, 233));
	refPoints.push_back(Point2f(373, 386));
	ComputeHomography computeHomography = ComputeHomography();
	computeHomography.computeHomography(refPoints, calibPoints);
//	std::vector<Point2f> scene_corners = computeHomography.applyHomography(imRef);

//	if (!computeHomography.validateTransformation()) {
//		return 2;
//	}

	std::vector<Point2f> candles = computeHomography.applyHomography(bougies);
	//-- Show detected matches


	for (int i=0; i<calibPoints.size(); i++)
	{
		printf("Target (%d) %f %f\n", i, calibPoints[i].x, calibPoints[i].y);
	}

	for (int i=0; i<candles.size(); i++)
	{
		printf("Candle (%d) %f %f\n", i, candles[i].x, candles[i].y);
		//circle( imOut, bougies[i], 8, Scalar(255,0,0), -1, -2);
		circle( imOut, candles[i], 5, Scalar(0,255,0), -1, -2);
	}

	return 0;
}
