/*
 * ContourHull.cpp
 *
 *  Created on: Jul 3, 2012
 *      Author: chao
 */
#include "ContourHull.h"

namespace contourHull {

void findContoursAndHulls(cv::Mat image, cv::vector<cv::vector<cv::Point> > &contoursVector,
		cv::vector<cv::vector<int> > &hullIntVector,
		cv::vector<cv::vector<cv::Point> > &hullPointVector,
		cv::vector<cv::Vec4i> &hierarchyVector) {
	cv::vector<cv::vector<cv::Point> > contours;
	cv::vector<cv::Vec4i> hierarchy;

	// Find contours
	findContours(image, contours, hierarchy, CV_RETR_LIST,
			CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	// Find convex hull object for each contour
	cv::vector<cv::vector<int> > hullInt(contours.size());
	cv::vector<cv::vector<cv::Point> > hullPoint(contours.size());

	for (uint i = 0; i < contours.size(); i++) {
		cv::convexHull(cv::Mat(contours[i]), hullInt[i]);
		cv::convexHull(cv::Mat(contours[i]), hullPoint[i]);
	}

	contoursVector = contours;
	hullIntVector = hullInt;
	hullPointVector = hullPoint;
	hierarchyVector = hierarchy;
}

void largestContourIndex(cv::vector<cv::vector<cv::Point> > contoursVector, int &index, int &area) {
	int contoursVectorSize = contoursVector.size();
	int largestIndex = 0;
	int largestArea = 0;

	for (int i = 0; i < contoursVectorSize; i++) {
		int area = fabs(cv::contourArea(cv::Mat(contoursVector[i])));

		if (area > largestArea) {
			largestIndex = i;
			largestArea = area;
		}
	}

	index = largestIndex;
	area = largestArea;
}

void findConvexityDefects(cv::vector<cv::vector<cv::Point> > contoursVector,
		cv::vector<cv::vector<int> > hullIntVector, cv::vector<cv::Vec4i> &convexDefectVector) {
	cv::vector<cv::Vec4i> convexDefects;
	int contoursVectorSize = contoursVector.size();

	for (int i = 0; i < contoursVectorSize; i++) {
		convexityDefects(contoursVector[i], hullIntVector[i], convexDefects);
	}

	convexDefectVector = convexDefects;
}
} // namespace contourHull
