#ifndef COMPUTEFEATUREPOINTS_H
#define COMPUTEFEATUREPOINTS_H

#import <opencv2/features2d/features2d.hpp>
#import <vector>

typedef enum {SIFTK = 0, SURFK = 1, BRISKK = 2, ORBK = 3, MSERK = 4, STARK = 5, GFTTDK = 6, DENSEK = 7, FASTK = 8, SBDK = 9, GRIDK = 10} KEYPOINT;
typedef enum {SIFTD = -2, SURFD = -1, BRISKD = 0, ORBD = 1, FREAKD = 2, BRIEFD = 3} DESCRIPTOR;

using namespace cv;

class ComputeFeaturePoints
{
public:
    ComputeFeaturePoints(Mat img, KEYPOINT kpt, DESCRIPTOR desc, bool useColor);



    std::vector<KeyPoint> keypoints;
    Mat descriptors;

 private:
    FeatureDetector* detector;
    DescriptorExtractor* extractor;
};

char* getKeypointName(KEYPOINT kpt);

char* getDescriptorName(DESCRIPTOR desc);

#endif // COMPUTEFEATUREPOINTS_H
