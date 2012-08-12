/*
 * X11Window.h
 *
 *  Created on: Jul 18, 2012
 *      Author: chao
 */

#ifndef HANDTRACKER_WINDOW_X11WINDOW_H_
#define HANDTRACKER_WINDOW_X11WINDOW_H_

#include "AbstractWindow.h"

#include <vector>

#include "opencv2/opencv.hpp"
#include "X11/X.h"
#include "X11/Xlib.h"
#include "X11/Xutil.h"


class X11Window : public AbstractWindow {
public:
	X11Window(cv::Mat frame, double boundry);
	virtual ~X11Window();
	void mouseMove(cv::Point pos);
	void mouseClick(int button);
	void mouseRelease();
	void flush();
private:
	Display *display;
	Window rootWindow;
	XWindowAttributes attr;

	XEvent event;
};

#endif /* HANDTRACKER_WINDOW_X11WINDOW_H_ */
