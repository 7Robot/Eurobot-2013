#include <stdio.h>

#include "matchdescriptors.h"
#include "opencv2/highgui/highgui.hpp"

Matchdescriptors::Matchdescriptors(DESCRIPTOR descriptor, MATCHER matching, Mat descs1, Mat descs2)
{
    descriptors1 = descs1;
    descriptors2 = descs2;
    selectMatcher(matching, descriptor);
    match();
}

void Matchdescriptors::selectMatcher(MATCHER matcher, DESCRIPTOR descriptor) {
    if (matcher == FLANN) {
        this->matcher = new FlannBasedMatcher();
        if (descriptor >= 0) {
            descriptors1.convertTo(descriptors1, CV_32F);
            descriptors2.convertTo(descriptors2, CV_32F);
        }
    }
    else if (matcher == BRUTEFORCE) {
        this->matcher = new BFMatcher(NORM_HAMMING, false);
    }
}

void Matchdescriptors::match() {
    // Bug known: FlannBasedMatcher requieres a float32 Mat in input
    // whereas ORB return int
    //  BFMatcher requires8, when SURF returns float descriptors
    matcher->match( descriptors1, descriptors2, matches );

    double max_dist = 0; double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors1.rows; i++ )
    { double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

//    printf("\n");
//    printf("-- Max dist : %f \n", max_dist );
//    printf("-- Min dist : %f \n", min_dist );

    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
    //-- PS.- radiusMatch can also be used here.

    for( int i = 0; i < descriptors1.rows; i++ )
    {
        if( matches[i].distance < 60 )
        {
            good_matches.push_back( matches[i]);
        }
    }

    printf("Good matches: %ld, %0.2f%%\n", good_matches.size(), 100*(float)good_matches.size()/descriptors1.rows);

}



char* getMatcherName(MATCHER matcher) {
    return (char*[]) {"FLANN", "BRUTEFORCE"}[matcher];
}

