//
// Created by hamidm9 on 6/4/23.
//

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/features2d.hpp>
#include "detectPlates.h"

void detectRoundPlates(const std::string& imageAdress)
{
    cv::Mat image = cv::imread(imageAdress);

    // Convert the image to grayscale
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // Apply Gaussian blur to reduce noise
    cv::GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0);

    // Apply Hough Circle Transform
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(grayImage, circles, cv::HOUGH_GRADIENT, 1, 50, 240, 60, 200, 600);
    //-------------------------------------------------------------------------1---------100--------50---------30------------10------------50

    // Draw the detected circles on the image
    for (const auto& circle : circles)
    {
        cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
        int radius = cvRound(circle[2]);
        cv::circle(image, center, radius, cv::Scalar(0, 255, 0), 2);
    }

    // Show the result image
    cv::imshow("Detected Plates", image);
    cv::waitKey(0);
}
