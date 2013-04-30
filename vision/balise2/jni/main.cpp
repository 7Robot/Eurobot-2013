#include <jni.h>


#include "computefeaturepoints.h"
#include "matchdescriptors.h"
#include "candlecolors.h"

#include <vector>

#include <opencv2/core/core.hpp>
//
//
#include <android/log.h>

#define LOG_TAG "Msg"
#define printf(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))




using namespace cv;

CandleColors* candleColors;

extern "C" {

JNIEXPORT void JNICALL Java_fr_dallens_balise2_Balise2Activity_initJNI(JNIEnv* env, jobject thiz, jlong addrImRef) {
	Mat& imgRef  = *(Mat*)addrImRef;
	candleColors = new CandleColors(ORBK, ORBD, BRUTEFORCE);
	candleColors->init(imgRef);
	printf("INIT done\n");
}

JNIEXPORT int JNICALL Java_fr_dallens_balise2_Balise2Activity_findColorsJNI(JNIEnv* env, jobject thiz, jlong addrImTar, jlong addrImOut) {
	Mat& imgTar  = *(Mat*)addrImTar;
	Mat& imgOut  = *(Mat*)addrImOut;
	printf("find colors\n");
	return candleColors->findColor(imgTar, imgOut);
}

JNIEXPORT int JNICALL Java_fr_dallens_balise2_Balise2Activity_findColorsJNI2(JNIEnv* env, jobject thiz, jfloat p1x, jfloat p1y, jfloat p2x, jfloat p2y, jfloat p3x, jfloat p3y, jfloat p4x, jfloat p4y, jlong addrImOut) {
	Mat& imgOut  = *(Mat*)addrImOut;
	printf("find colors2\n");
	std::vector<Point2f> targetPoints;
	targetPoints.push_back(Point2f(p1x, p1y));
	targetPoints.push_back(Point2f(p2x, p2y));
	targetPoints.push_back(Point2f(p3x, p3y));
	targetPoints.push_back(Point2f(p4x, p4y));
	return candleColors->findColor2(targetPoints, imgOut);
}

}
