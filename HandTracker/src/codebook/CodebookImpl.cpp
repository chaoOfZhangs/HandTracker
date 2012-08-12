/*
 * CodebookImpl.cpp
 *
 *  Created on: Jul 7, 2012
 *      Author: chao
 */
#include "CodebookImpl.h"

#include "stdio.h"

#include "opencv2/opencv.hpp"
#include "opencv2/legacy/legacy.hpp"

CodebookImpl::CodebookImpl(int numFramesToLearnBG) {
	this->model = cvCreateBGCodeBookModel();

	this->yuvImage = 0;
	this->IMaskCodeBook = 0;
	this->IMaskCodeBookCC = 0;

	this->numFrames = 0;
	this->numFramesToLearnBG = numFramesToLearnBG;
}

CodebookImpl::~CodebookImpl() {
	cvReleaseImage(&yuvImage);
	cvReleaseImage(&IMaskCodeBook);
	cvReleaseImage(&IMaskCodeBookCC);
}

IplImage* CodebookImpl::process(IplImage* image) {
	++numFrames;

	fprintf(stderr, "Num frames:%d \n", numFrames);

	if (numFrames == 1 && image) {

		yuvImage = cvCloneImage(image);
		IMaskCodeBook = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
		IMaskCodeBookCC = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);

		cvSet(IMaskCodeBook, cvScalar(255));

	}


	if (image) {
		// YUV for codebook method
		cvCvtColor(image, yuvImage, CV_BGR2YCrCb);

		// Build the background model
		if (numFrames-1 < numFramesToLearnBG) {
			cvBGCodeBookUpdate(model, yuvImage);
		}

		if (numFrames-1 == numFramesToLearnBG) {
			cvBGCodeBookClearStale(model, model->t/2);
		}

		// Find the foreground if there is any
		if (numFrames-1 >= numFramesToLearnBG) {
			// Find the foreground using the codebook method
			cvBGCodeBookDiff(model, yuvImage, IMaskCodeBook);
			// Visualize bounding boxes and centers (optional)
			cvCopy(IMaskCodeBook, IMaskCodeBookCC);
			cvSegmentFGMask(IMaskCodeBookCC);
		}

	}

	return IMaskCodeBookCC;
}

