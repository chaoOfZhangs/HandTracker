/*
 * Utils.cpp
 *
 *  Created on: Jul 14, 2012
 *      Author: chao
 */

#include "Utils.h"

#include "opencv2/opencv.hpp"

namespace utils {

double distance(cv::Point point1, cv::Point point2) {
	double x1 = point1.x;
	double y1 = point1.y;

	double x2 = point2.x;
	double y2 = point2.y;

	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double angle(cv::Point vertex, cv::Point point1, cv::Point point2) {
	double numerator = pow(utils::distance(vertex, point1), 2)
			+ pow(utils::distance(vertex, point2), 2)
			- pow(utils::distance(point1, point2), 2);

	double denominator = 2 * utils::distance(vertex, point1) * utils::distance(vertex, point2);

	return acos(numerator / denominator);
}

cv::Point midpoint(cv::Point point1, cv::Point point2) {
	cv::Point ret((point1.x + point2.x)/2, (point1.y + point2.y)/2);
	return ret;
}

cv::Mat iplImageToMat(IplImage* image) {
	cv::Mat mat(image);
	return mat;
}

IplImage* matToIplImage(cv::Mat mat) {
	IplImage* img = new IplImage(mat);
	return img;
}


} /* namespace utils */
