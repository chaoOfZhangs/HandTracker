/*
 * X11Window.cpp
 *
 *  Created on: Jul 18, 2012
 *      Author: chao
 */

#include "X11Window.h"

#include "stdio.h"

X11Window::X11Window(cv::Mat window, double boundry) :
		AbstractWindow(window, boundry) {

	display = XOpenDisplay(NULL);
	rootWindow = XRootWindow(display, 0);
	XSelectInput(display, rootWindow, KeyReleaseMask);

	XGetWindowAttributes(display, rootWindow, &attr);

	memset(&event, 0x00, sizeof(event));
}

X11Window::~X11Window() {
	display = NULL;
	memset(&event, 0x00, sizeof(event));
}

void X11Window::mouseMove(cv::Point pos) {
	cv::vector<double> scalePos = scaleMousePosition(pos);
	if (scalePos[0] > -1 && scalePos[1] > -1) {
		XWarpPointer(display, None, rootWindow, 0, 0, 0, 0,
				scalePos[0] * attr.width, scalePos[1] * attr.height);
	}
}

void X11Window::mouseClick(int button) {
	event.type = ButtonPress;
	event.xbutton.button = button;
	event.xbutton.same_screen = True;
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)) , &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

	event.xbutton.subwindow = event.xbutton.window;

	while (event.xbutton.subwindow) {
		event.xbutton.window = event.xbutton.subwindow;

		XQueryPointer(display, event.xbutton.window,
				&event.xbutton.root,
				&event.xbutton.subwindow,
				&event.xbutton.x_root,
				&event.xbutton.y_root, &event.xbutton.x,
				&event.xbutton.y, &event.xbutton.state);
	}
	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) {
		printf("XSendEvent key press event failed!\n");
	} else {
		mouseKeyDown = true;
	}
}

void X11Window::mouseRelease() {
	event.type = ButtonRelease;
	event.xbutton.state = 0x100;
	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) {
		fprintf(stderr, "XSendEvent key release event failed!\n");
	} else {
		mouseKeyDown = false;
	}

}

void X11Window::flush() {
	XFlush(display);
}
