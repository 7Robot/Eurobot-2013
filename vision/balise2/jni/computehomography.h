#ifndef COMPUTEHOMOGRAPHY_H
#define COMPUTEHOMOGRAPHY_H

#include <opencv2/features2d/features2d.hpp>
#include <vector>

using namespace cv;

class ComputeHomography
{
public:
    
    // Constructors
    ComputeHomography();
    
    // Public methods, sorted by order of normal execution
    void computeHomography(vector<KeyPoint> keypoints1, vector<KeyPoint> keypoints2, std::vector< DMatch > good_matches);
    void computeHomography(vector<Point2f> keypoints1, vector<Point2f> keypoints2);
    std::vector<Point2f> applyHomography(int width, int height);
    std::vector<Point2f> applyHomography(Mat referencePicture);
    std::vector<Point2f> applyHomography(std::vector<Point2f> corners);
    float expectedResultComparison(std::vector<Point2f> expectedQueryPictureCorners);
    bool validateTransformation();
    std::vector<Point2f> queryPictureCorners;
    
    
private:
    // Private methods
    void computeHomographyCommon(vector<Point2f> keypoints1, vector<Point2f> keypoints2);
    
    // Private attributes
    double error;
    Mat homographyMatrix;
    std::vector<Point2f> referencePictureCorners; // cv::perspectiveTransform() requires a vector
    bool homographyMatrixInit;
    bool queryPictureCornersInit;
};

#endif // COMPUTEHOMOGRAPHY_H
