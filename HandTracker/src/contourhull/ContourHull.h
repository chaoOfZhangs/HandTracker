/*
 * ContourHull.h
 *
 *  Created on: Jul 3, 2012
 *      Author: chao
 */
#ifndef HANDTRACKER_CONTOURHULL_CONTOURHULL_H_
#define HANDTRACKER_CONTOURHULL_CONTOURHULL_H_

#include "opencv2/opencv.hpp"

namespace contourHull {

void findContoursAndHulls(cv::Mat image, cv::vector<cv::vector<cv::Point> > &contoursVector,
		cv::vector<cv::vector<int> > &hullIntVector,
		cv::vector<cv::vector<cv::Point> > &hullPointVector,
		cv::vector<cv::Vec4i> &hierarchyVector);

void largestContourIndex(cv::vector<cv::vector<cv::Point> > contoursVector, int &index, int &area);

void findConvexityDefects(cv::vector<cv::vector<cv::Point> > contoursVector,
		cv::vector<cv::vector<int> > hullIntVector, cv::vector<cv::Vec4i> &convexDefectVector);
}

#endif /* HANDTRACKER_CONTOURHULL_CONTOURHULL_H_ */
