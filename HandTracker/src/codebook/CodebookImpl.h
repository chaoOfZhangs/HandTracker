/*
 * CodebookImpl.h
 *
 *  Created on: Jul 7, 2012
 *      Author: chao
 */

#ifndef HANDTRACKER_CODEBOOK_CODEBOOKIMPL_H_
#define HANDTRACKER_CODEBOOK_CODEBOOKIMPL_H_

#include "opencv2/opencv.hpp"
#include "opencv2/legacy/legacy.hpp"

class CodebookImpl {

public:
	CodebookImpl(int numFramesToLearnBG=300);
	virtual ~CodebookImpl();
	IplImage* process(IplImage* image);

private:
	CvBGCodeBookModel *model;

	IplImage *yuvImage;
	IplImage *IMaskCodeBook;
	IplImage *IMaskCodeBookCC;

	int numFrames;
	int numFramesToLearnBG;
};

#endif /* HANDTRACKER_CODEBOOK_CODEBOOKIMPL_H_ */
