/*
 * AbstractWindow.h
 *
 *  Created on: Jul 22, 2012
 *      Author: chao
 */

#ifndef HANDTRACKER_WINDOW_ABSTRACTWINDOW_H_
#define HANDTRACKER_WINDOW_ABSTRACTWINDOW_H_

#include "opencv2/opencv.hpp"

class AbstractWindow {
public:
	AbstractWindow(cv::Mat window, double boundry);
	virtual ~AbstractWindow();

	double getTopBoundry() {return topBoundry;};
	double getBottomBoundry() {return bottomBoundry;};
	double getLeftBoundry() {return leftBoundry;};
	double getRightBoundry() {return rightBoundry;};

	bool isMouseDown() {return mouseKeyDown;};

	virtual void mouseMove(cv::Point mousePos) = 0;
	virtual void mouseClick(int button) = 0;
	virtual void mouseRelease() = 0;
	virtual void flush() = 0;

protected:
	double topBoundry;
	double bottomBoundry;
	double leftBoundry;
	double rightBoundry;

	int windowWidth;
	int windowHeight;

	bool mouseKeyDown;

	cv::vector<double> scaleMousePosition(cv::Point mousePos);

};

#endif /* HANDTRACKER_WINDOW_ABSTRACTWINDOW_H_ */
