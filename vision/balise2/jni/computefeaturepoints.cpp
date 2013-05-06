#include "computefeaturepoints.h"

#import <opencv2/legacy/compat.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <stdio.h>


ComputeFeaturePoints::ComputeFeaturePoints(Mat img, KEYPOINT kpt, DESCRIPTOR desc, bool useColor)
{
   if (kpt == BRISKK) {
        BRISK* briskdetector = new BRISK(30, 3, 1.0f);
        detector = briskdetector;
    }
    else if (kpt == ORBK) {
        ORB* orbdetector = new ORB(400);
        detector = orbdetector;
    }
    else if (kpt == MSERK) {
        detector = new MSER();
    }
    else if (kpt == STARK) {
        detector = new StarDetector();
    }
    else if (kpt == GFTTDK) {
        detector = new GFTTDetector();
    }
    else if (kpt == DENSEK) {
        detector = new DenseFeatureDetector();
    }
    else if (kpt == GRIDK) {
        detector = new GridAdaptedFeatureDetector();
    }
    else if (kpt == FASTK) {
//        detector =  new FastFeatureDetector(120);
        detector =  new DynamicAdaptedFeatureDetector (new FastAdjuster(80,true, 70, 120), 350, 450, 2);
    }
    else {
        printf("Unknown detector %d.", kpt);
    }
    
    if(desc == BRISKD) {
        BRISK* briskExtractor = new BRISK();
        extractor = briskExtractor;
    }
    else if (desc == ORBD) {
        extractor = (new OrbDescriptorExtractor());;
    }
    else if (desc == FREAKD) {
        FREAK* freakExtractor = new FREAK();
        extractor = freakExtractor;
    }
    else if (desc == BRIEFD) {
        extractor = new BriefDescriptorExtractor();
    }
    else {
        printf("Unknown extractor %d.", desc);
    }
    
    if (useColor) {
        extractor = new OpponentColorDescriptorExtractor(extractor);
    }
    
    detector->detect( img, keypoints);
    
    printf("%Keypoints: %ld\n", keypoints.size());
    fflush(stdout);
    
    extractor->compute(img, keypoints, descriptors);
    
    
    printf("Descriptors: %ld x %ld\n", descriptors.rows, descriptors.cols);
    fflush(stdout);
}

char* getKeypointName(KEYPOINT kpt) {
    return (char*[]) {"SIFT", "SURF", "BRISK", "ORB", "MSER", "STAR", "GFTTD", "DENSE", "FAST", "SBD", "GRID"}[kpt];
}


char* getDescriptorName(DESCRIPTOR desc) {
    return (char*[]) {"SIFT", "SURF", "BRISK", "ORB", "FREAK"}[desc+2];
}
