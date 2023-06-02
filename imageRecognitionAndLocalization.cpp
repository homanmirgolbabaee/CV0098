//
// Created by hamidm9 on 5/31/23.
//

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/features2d.hpp>
#include "imageRecognitionAndLocalization.h"

// Function to perform food recognition and localization using ORB
void recognizeFoodORB(const std::string& beforeImageAddress, const std::string&  afterImageAddress)
{
    //read input images
    cv::Mat beforeImage = cv::imread(beforeImageAddress);
    cv::Mat afterImage = cv::imread(afterImageAddress);

    // Detect keypoints and extract descriptors using ORB
    cv::Ptr<cv::Feature2D> orb = cv::ORB::create();
    std::vector<cv::KeyPoint> keypointsBefore, keypointsAfter;
    cv::Mat descriptorsBefore, descriptorsAfter;
    orb->detectAndCompute(beforeImage, cv::noArray(), keypointsBefore, descriptorsBefore);
    orb->detectAndCompute(afterImage, cv::noArray(), keypointsAfter, descriptorsAfter);

    // Match the descriptors
    cv::BFMatcher matcher(cv::NORM_HAMMING);
    std::vector<cv::DMatch> matches;
    matcher.match(descriptorsBefore, descriptorsAfter, matches);

    // Filter matches based on distance
    double distanceThreshold = 70.0; // Adjust this value as needed
    std::vector<cv::DMatch> filteredMatches;
    for (const auto& match : matches)
    {
        if (match.distance < distanceThreshold)
        {
            filteredMatches.push_back(match);
        }
    }

    // Draw matched keypoints
    cv::Mat resultImage;
    cv::drawMatches(beforeImage, keypointsBefore, afterImage, keypointsAfter,
                    filteredMatches, resultImage, cv::Scalar::all(-1),
                    cv::Scalar::all(-1), std::vector<char>(),
                    cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // Display the result image
    cv::imshow("Food Recognition (ORB)", resultImage);
    cv::waitKey(0);
}