/*
 * AbstractWindow.cpp
 *
 *  Created on: Jul 22, 2012
 *      Author: chao
 */

#include "AbstractWindow.h"

AbstractWindow::AbstractWindow(cv::Mat window, double boundry) {
	if (boundry < 0 || boundry > 0.5) {
		boundry = 0.15;
	}

	topBoundry = window.rows * boundry;
	bottomBoundry = window.rows * (1 - boundry);
	leftBoundry = window.cols * boundry;
	rightBoundry = window.cols * (1 - boundry);

	windowWidth = (int) (rightBoundry - leftBoundry);
	windowHeight = (int) (bottomBoundry - topBoundry);

	mouseKeyDown = false;
}

AbstractWindow::~AbstractWindow() {
	// TODO Auto-generated destructor stub
}

cv::vector<double> AbstractWindow::scaleMousePosition(cv::Point mousePos) {
	if (mousePos.x < leftBoundry || mousePos.x > rightBoundry
			|| mousePos.y < topBoundry || mousePos.y > bottomBoundry) {
		return {-1.0, -1.0};
	} else {
		return {(mousePos.x - leftBoundry)/windowWidth, (mousePos.y - topBoundry)/windowHeight};
	}
}

