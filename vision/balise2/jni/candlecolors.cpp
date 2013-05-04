#include "candlecolors.h"

#include "computehomography.h"

#include <opencv2/opencv.hpp> // sale
#include "opencv2/highgui/highgui.hpp"



#define LOG_TAG "Msg"

#ifdef __ANDROID__
	#include <android/log.h>
	#define printf(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
    
    
#else
	#include <stdio.h>
#endif

Scalar blue = Scalar(0,0,255);
Scalar red  = Scalar(255,0,0); 

//#define MAX(x, y) (((x) > (y)) ? (x) : (y))
//#define MIN(x, y) (((x) < (y)) ? (x) : (y))

CandleColors::CandleColors(KEYPOINT keypoint, DESCRIPTOR descriptor, MATCHER matcher )
{
    this->keypoint = keypoint;
    this->descriptor = descriptor;
    this->matcher = matcher;

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
        printf("Not enough matches");
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
//    drawMatches( imRef, keypointsRef, img, computeFP->keypoints,
//               good_matches, imOut, Scalar::all(-1), Scalar::all(-1),
//               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );


    if (good_matches.size() >= 4)
    {
        //-- Draw lines between the corners (the mapped object in the scene - image_2 )
//        line( imOut, scene_corners[0] + Point2f( imRef.cols, 0), scene_corners[1] + Point2f( imRef.cols, 0), Scalar( 0, 255, 0), 4 );
//        line( imOut, scene_corners[1] + Point2f( imRef.cols, 0), scene_corners[2] + Point2f( imRef.cols, 0), Scalar( 0, 255, 0), 4 );
//        line( imOut, scene_corners[2] + Point2f( imRef.cols, 0), scene_corners[3] + Point2f( imRef.cols, 0), Scalar( 0, 255, 0), 4 );
//        line( imOut, scene_corners[3] + Point2f( imRef.cols, 0), scene_corners[0] + Point2f( imRef.cols, 0), Scalar( 0, 255, 0), 4 );
        line( imOut, scene_corners[0], scene_corners[1], Scalar( 0, 255, 0), 4 );
        line( imOut, scene_corners[1], scene_corners[2], Scalar( 0, 255, 0), 4 );
        line( imOut, scene_corners[2], scene_corners[3], Scalar( 0, 255, 0), 4 );
        line( imOut, scene_corners[3], scene_corners[0], Scalar( 0, 255, 0), 4 );

    }

    for (unsigned int i=0; i<candles.size(); i++)
    {
//        candles[i].x += imRef.cols;
        printf("Candle pos %d %f %f\n", imRef.cols, candles[i].x, candles[i].y);
        color col = getColor(imOut, candles[i].x, candles[i].y);
        Scalar circleColor;
        if (col==RED)
        	circleColor = red;
        else if (col==BLUE)
        	circleColor = blue;
        else
        	circleColor = Scalar(0,255,0);
        circle( imOut, candles[i], 5, circleColor, -1, 8);

    }

    return 0;
}

int CandleColors::findColor2(std::vector<Point2f> calibPoints, Mat& imOut)
{
	std::vector<Point2f> refPoints;
	refPoints.push_back(Point2f(448, 66));
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


	for (unsigned int i=0; i<calibPoints.size(); i++)
	{
		printf("Target (%d) %f %f\n", i, calibPoints[i].x, calibPoints[i].y);
	}



	for (unsigned int i=0; i<candles.size(); i++)
	    {
	//        candles[i].x += imRef.cols;
	        printf("Candle pos %d %f %f\n", imRef.cols, candles[i].x, candles[i].y);
	        color col = getColor(imOut, candles[i].x, candles[i].y);
	        Scalar circleColor;
	        if (col==RED)
	        	circleColor = red;
	        else if (col==BLUE)
	        	circleColor = blue;
	        else
	        	circleColor = Scalar(0,255,0);
	        circle( imOut, candles[i], 5, circleColor, -1, 8);

	    }

	return 0;
}

color CandleColors::getColor(Mat img, int x, int y)
{
	const int radius = 10;
    printf("img %d %d %d %d %d\n", img.depth(), img.type(), img.channels(), CV_8U, CV_32F);
	printf("box %d %d %d %d %d %d\n", x, y, MIN(MAX(0,x-radius),img.cols-2*radius), MIN(MAX(0,y-radius),img.rows-2*radius), 2*radius, 2*radius);
	printf("img %d %d, %d %d\n", img.cols, img.rows, MIN(MAX(0,x-radius),img.cols-2*radius)+2*radius, MIN(MAX(0,y-radius),img.rows-2*radius)+2*radius);
    
	cv::Rect const mask(MIN(MAX(0,x-radius),img.cols-2*radius), MIN(MAX(0,y-radius),img.rows-2*radius), 2*radius, 2*radius);
	cv::Mat roi = img(mask);
	Mat imgHSV = roi.clone();
	cvtColor(roi, imgHSV, CV_RGB2HSV);
    //~ imshow( "Good Matches & Object detection", roi );
    //~ waitKey(0);
	Mat blue = Mat(roi.cols, roi.rows, CV_8UC1);
	Mat red1 = Mat(roi.cols, roi.rows, CV_8UC1);
    Mat red2 = Mat(roi.cols, roi.rows, CV_8UC1);
    // Gimp    h : 0 --> 360 , s : 0 --> 100 , v : 0 --> 100
    // OpenCV  h : 0 --> 180 , s : 0 --> 255 , v : 0 --> 255
	inRange(imgHSV, Scalar(70, 109, 109), Scalar(130,255,255), blue);
	inRange(imgHSV, Scalar(171, 109, 109), Scalar(180,255,255), red1);
    inRange(imgHSV, Scalar(0, 109, 109), Scalar(5,255,255), red2);
    
    //~ imshow( "Good Matches & Object detection", blue );
    //~ waitKey(0);
    //~ imshow( "Good Matches & Object detection", red );
    //~ waitKey(0);
    
	Scalar sblue = sum(blue);
	Scalar sred = sum(red1)+sum(red2);
	printf("blue %f, red %f", sblue.val[0], sred.val[0]);
	if (sblue.val[0] > 2*sred.val[0])
		return BLUE;
	else if (2*sblue.val[0] < sred.val[0])
		return RED;
	else
		return UNKNOWN;

}

void CandleColors::setPosition(int position)
{
	this->position = position;
	bougies = vector<Point2f>(0);
	printf("Setting position %d\n", position);
	if (position==4)
	{
		// Haut
		bougies.push_back(Point2f(380 , 116));
		bougies.push_back(Point2f(380 , 150));
		bougies.push_back(Point2f(380 , 189));
		bougies.push_back(Point2f(378 , 225));
		bougies.push_back(Point2f(374 , 256));
		// Bas
		bougies.push_back(Point2f(412 , 91));
		bougies.push_back(Point2f(416 , 116));
		bougies.push_back(Point2f(413 , 146));
		bougies.push_back(Point2f(415 , 184));
		bougies.push_back(Point2f(410 , 220));
		bougies.push_back(Point2f(411 , 251));
		bougies.push_back(Point2f(407 , 271));

	}
	else if (position==3)
	{
		// Haut
		bougies.push_back(Point2f(183 , 215));
		bougies.push_back(Point2f(218 , 217));
		bougies.push_back(Point2f(259 , 217));
		bougies.push_back(Point2f(296 , 213));
		bougies.push_back(Point2f(323 , 210));
		// Bas
		bougies.push_back(Point2f(157 , 249));
		bougies.push_back(Point2f(183 , 250));
		bougies.push_back(Point2f(216 , 254));
		bougies.push_back(Point2f(253 , 253));
		bougies.push_back(Point2f(286 , 247));
		bougies.push_back(Point2f(317 , 242));
		bougies.push_back(Point2f(344 , 239));
	}
}
