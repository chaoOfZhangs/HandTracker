/*
 * Utils.h
 *
 *  Created on: Jul 14, 2012
 *      Author: chao
 */

#ifndef HANDTRACKER_UTIL_UTILS_H_
#define HANDTRACKER_UTIL_UTILS_H_

#include "opencv2/opencv.hpp"

namespace utils {

const double PI = 3.141592653589793238462643383279502884197;
const double DEGREES_TO_RADIANS_MULTIPLIER = PI / 180;
const double RADIANS_TO_DEGREES_MULTIPLIER = 180 / PI;

const static cv::Scalar COLOR_RED = cv::Scalar(0, 0, 255);
const static cv::Scalar COLOR_GREEN = cv::Scalar(0, 255, 0);
const static cv::Scalar COLOR_BLUE = cv::Scalar(255, 0, 0);
const static cv::Scalar COLOR_CYAN = cv::Scalar(255, 255, 0);
const static cv::Scalar COLOR_VIOLET = cv::Scalar(255, 0, 255);
const static cv::Scalar COLOR_YELLOW = cv::Scalar(0, 255, 255);
const static cv::Scalar COLOR_WHITE = cv::Scalar(255, 255, 255);

double distance(cv::Point point1, cv::Point point2);
double angle(cv::Point vertex, cv::Point point1, cv::Point point2);

cv::Point midpoint(cv::Point point1, cv::Point poin2);

cv::Mat iplImageToMat(IplImage* image);
IplImage* matToIplImage(cv::Mat mat);

} /* namespace utils */
#endif /* HANDTRACKER_UTIL_UTILS_H_ */
