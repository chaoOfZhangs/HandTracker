////============================================================================
//// Name        : HandTracker.cpp
//// Author      : Chao
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================

#include <iostream>
#include "stdio.h"

#include "opencv2/opencv.hpp"
#include "opencv2/legacy/legacy.hpp"

#include "../codebook/CodebookImpl.h"
#include "../contourhull/ContourHull.h"
#include "../util/Utils.h"
#include "../window/X11Window.h"

static const int CONTOUR_AREA_THRESHOLD = 7500;

void findMousePosition(cv::Mat image, cv::Mat &destImage, int &numOfFingers,
		cv::Point &point, cv::vector<double> contourBoundry) {
	destImage = cv::Mat::zeros(image.size(), CV_8UC3);

	cv::rectangle(destImage, cv::Point(contourBoundry[3], contourBoundry[0]), cv::Point(contourBoundry[1], contourBoundry[2]), utils::COLOR_RED);

	cv::vector<cv::vector<cv::Point> > contoursVector;
	cv::vector<cv::vector<int> > hullIntVector;
	cv::vector<cv::vector<cv::Point> > hullPointVector;
	cv::vector<cv::Vec4i> hierarchyVector;
	cv::vector<cv::Vec4i> convexDefectVector;
	int index;
	int contourArea;

	int numFingers = -1;
	cv::Point mousePoint(-1, -1);

	contourHull::findContoursAndHulls(image, contoursVector, hullIntVector, hullPointVector,
			hierarchyVector);

	contourHull::largestContourIndex(contoursVector, index, contourArea);
	contourHull::findConvexityDefects(contoursVector, hullIntVector, convexDefectVector);

	if (contourArea > CONTOUR_AREA_THRESHOLD) {
		cv::drawContours(destImage, contoursVector, index, utils::COLOR_WHITE, 1, 8,
				cv::vector<cv::Vec4i>(), 0, cv::Point());
		cv::drawContours(destImage, hullPointVector, index, utils::COLOR_YELLOW, 1, 8,
				cv::vector<cv::Vec4i>(), 0, cv::Point());

		cv::Point mousePoint1;
		cv::Point mousePoint2;

		numFingers = 0;
		bool mousePointSet = false;
		uint convexDefectSize = convexDefectVector.size();

		for (uint i = 1; i < convexDefectSize; i++) {
			cv::circle(destImage, contoursVector[index][convexDefectVector[i][0]],
					5, utils::COLOR_BLUE);
			cv::circle(destImage, contoursVector[index][convexDefectVector[i][2]],
					5, utils::COLOR_BLUE);

			cv::Point vertex = contoursVector[index][convexDefectVector[i][0]];
			cv::Point point1 = contoursVector[index][convexDefectVector[i - 1][2]];
			cv::Point point2 = contoursVector[index][convexDefectVector[i][2]];

			if (vertex.x > contourBoundry[1] ||
				vertex.x < contourBoundry[3] ||
				vertex.y < contourBoundry[0] ||
				vertex.y > contourBoundry[2]) {
				continue;
			}

			if (utils::angle(vertex, point1, point2) * utils::RADIANS_TO_DEGREES_MULTIPLIER
					< 90) {
				cv::line(destImage, vertex, point1, utils::COLOR_YELLOW, 1);
				cv::line(destImage, vertex, point2, utils::COLOR_YELLOW, 1);

				if (!mousePointSet) {
					mousePoint1 = vertex;
					mousePointSet = true;
				}

				mousePoint2 = vertex;

				numFingers++;
			}
		}

		if (numFingers < 7) {
			mousePoint = utils::midpoint(mousePoint1, mousePoint2);
			cv::circle(destImage, mousePoint, 10, utils::COLOR_VIOLET);
		}

		// Holds the String "Number of Fingers: " and a number up to 64 bits
		char display[40];
		sprintf(display, "Number of Fingers: %u", numFingers);
		cv::putText(destImage, display,
				cv::Point(destImage.cols / 20, destImage.rows / 20),
				cv::FONT_HERSHEY_PLAIN, 1, utils::COLOR_CYAN);
	}

	numOfFingers = numFingers;
	point = mousePoint;

}

int main(int argc, char* argv[]) {
	CodebookImpl *codebook = new CodebookImpl(300);
	AbstractWindow *window;

	CvCapture* cap = cvCaptureFromCAM(1);

	if (!cap) {
		fprintf(stderr, "Error: Capture is NULL \n");
		getchar();
		return -1;
	}

	int numFingers;
	cv::Point mousePoint;

	cv::Mat frame = cvQueryFrame(cap);
	window = new X11Window(frame, 0.15);

	cv::vector<int> frameSize = { frame.cols, frame.rows };
	// Top, right, bottom, and left boundries for recognizing the points for defect points
	cv::vector<double> contourBoundry = { frame.rows * .02, frame.cols * .98,
			frame.rows * .98, frame.cols * .02 };

	for (;;) {
		frame = cvQueryFrame(cap);

		if (frame.empty()) {
			fprintf(stderr, "Error: Frame is NULL \n");
//			getchar();
			break;
		}

		cv::Mat clone = frame.clone();

		cv::blur(clone, clone, cv::Size(7, 7));
		clone = utils::iplImageToMat(codebook->process(utils::matToIplImage(clone)));
		imshow("Codebook", clone);

		cv::blur(clone, clone, cv::Size(7, 7));

		findMousePosition(clone, clone, numFingers, mousePoint, contourBoundry);

		cv::rectangle(clone, cv::Point(window->getLeftBoundry(), window->getTopBoundry()), cv::Point(window->getRightBoundry(), window->getBottomBoundry()), utils::COLOR_GREEN);

		imshow("Contour and Hull", clone);
		imshow("Raw Image", frame);

		if (numFingers < 7) {
			if (window->isMouseDown() && numFingers > 0) {
				window->mouseRelease();
			} else if (!(window->isMouseDown()) && numFingers == 0) {
				window->mouseClick(1);
			}
			window->mouseMove(mousePoint);
			window->flush();
		}

		if (cvWaitKey(33) == 27) {
			break;
		}
	}

	cvReleaseCapture(&cap);

	return 0;
}
