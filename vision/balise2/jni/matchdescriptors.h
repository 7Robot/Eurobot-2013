#ifndef MATCHDESCRIPTORS_H
#define MATCHDESCRIPTORS_H

#include "computefeaturepoints.h"
#include "opencv2/features2d/features2d.hpp"

#include <vector>

typedef enum {FLANN = 0, BRUTEFORCE = 1} MATCHER;

using namespace cv;

class Matchdescriptors
{
public:
    Matchdescriptors(DESCRIPTOR descriptor, MATCHER matcher, Mat descs1, Mat descs2);


    std::vector< DMatch > matches;
    std::vector< DMatch > good_matches;

private:
    DescriptorMatcher* matcher;
    Mat descriptors1;
    Mat descriptors2;

    void match();
    void selectMatcher(MATCHER matcher, DESCRIPTOR descriptor);

};

char* getMatcherName(MATCHER matcher);

#endif // MATCHDESCRIPTORS_H
