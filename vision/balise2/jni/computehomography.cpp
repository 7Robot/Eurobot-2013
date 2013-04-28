#include "computehomography.h"

#include "opencv2/calib3d/calib3d.hpp"

#include <stdio.h>


ComputeHomography::ComputeHomography()
{
    homographyMatrixInit    = true;
    queryPictureCornersInit = false;
}


/// @pre : good_matches.size() contains at least 4 elements
void ComputeHomography::computeHomography(vector<KeyPoint> keypoints1, vector<KeyPoint> keypoints2, std::vector< DMatch > good_matches)
{
    assert(good_matches.size() > 3);
    std::vector<Point2f> queryImGoodKpt;
    std::vector<Point2f> trainImGoodKpt;
    homographyMatrix = Mat();
    for( int i = 0; i < good_matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        queryImGoodKpt.push_back( keypoints1[ good_matches[i].queryIdx ].pt );
        trainImGoodKpt.push_back( keypoints2[ good_matches[i].trainIdx ].pt );
    }
    
    computeHomographyCommon(queryImGoodKpt, trainImGoodKpt);
}

void ComputeHomography::computeHomography(vector<Point2f> keypoints1, vector<Point2f> keypoints2)
{
    computeHomographyCommon(keypoints1, keypoints2);
}

void ComputeHomography::computeHomographyCommon(vector<Point2f> keypoints1, vector<Point2f> keypoints2)
{
    assert(keypoints1.size() > 3);
    homographyMatrix = Mat();
    homographyMatrix = cv::findHomography( keypoints1, keypoints2, CV_RANSAC, 3);
    homographyMatrixInit = true;
}

/// @pre : this->homographyMatrix computed with computeHomography
std::vector<Point2f> ComputeHomography::applyHomography(Mat referencePicture)
{
    assert(homographyMatrixInit);
    return applyHomography(referencePicture.cols, referencePicture.rows);
}

/// @pre : this->homographyMatrix computed with computeHomography
std::vector<Point2f> ComputeHomography::applyHomography(int width, int height)
{
    assert(homographyMatrixInit);
    
    referencePictureCorners = std::vector<Point2f>();
    referencePictureCorners.push_back(cvPoint(0,0));
    referencePictureCorners.push_back(cvPoint(width,0));
    referencePictureCorners.push_back(cvPoint(width, height));
    referencePictureCorners.push_back(cvPoint(0, height));
//    printf("****** %d %d \n", width, height);

    return applyHomography(referencePictureCorners);
}

std::vector<Point2f> ComputeHomography::applyHomography(std::vector<Point2f> corners)
{
    queryPictureCorners = std::vector<Point2f>(4);
    perspectiveTransform(corners, queryPictureCorners, homographyMatrix);
    queryPictureCornersInit = true;
    return queryPictureCorners;
}

/// @pre : this->queryPictureCorners computed with applyHomography
/// @return : the error of between the expected result and the computed one.
float ComputeHomography::expectedResultComparison(std::vector<Point2f> expectedQueryPictureCorners)
{
    assert(queryPictureCornersInit);
    
    error = 0;
    for (int i=0; i<4; i++) {
        double diff = norm(expectedQueryPictureCorners[i] - queryPictureCorners[i]);
        error += diff;
    }
    printf("Error: %f\n", error);
    return error;
}

/// @pre : this->queryPictureCorners computed with applyHomography
/// @return : false if the application of the homography gives an acceptable result
///           true  if the angles of the detected picture look inconsitent
bool ComputeHomography::validateTransformation()
{
    assert(queryPictureCornersInit);
    
    float angle[4];
    for (int i=0; i<3; i++)
    {
        angle[i] = 3.14159;
        
        Point2f side0 = queryPictureCorners[i+1] - queryPictureCorners[i];
        Point2f side1 = queryPictureCorners[(i+2)%4] - queryPictureCorners[i+1];
        
        
        float denom = norm(side0)*norm(side1);
        if (abs(denom) > 1e-5)
        {
            float dotProduct = side0.x*side1.x + side0.y*side1.y;
            angle[i]  = acos(dotProduct/denom);
        }
        float det = side0.x*side1.y - side0.y*side1.x;
        if (det<0)
            angle[i] = -angle[i];
    }
    
    angle[3] = 6.28319 - angle[0] - angle[1] - angle[2];
    
    for (int i=0; i<4; i++)
    {
        // abs(angle[i] - 90) > 60 <=>
        //        printf("angle %f \n", angle[i]);
        if (angle[i] > 2.61799 || angle[i] < 0.52360)
        {
            printf("Unvalidated homography transfo %d %f\n", i, angle[i]);
            for (int j = 0 ; j<4; j++)
                printf("%f %f\n", queryPictureCorners[j].x, queryPictureCorners[j].y);
            return false;
        }
    }
    
    return true;
}
