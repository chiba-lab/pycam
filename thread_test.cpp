#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/videoio/videoio_c.h"
#include "opencv2/highgui.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core.hpp"
#include <iostream>
#include <stdio.h>
#include <thread>

using namespace std;
using namespace cv;

#define NUM_THREADS 2
#define FPS 30

public:
	std::vector<Mat> frames;

struct Frame {
	Mat frame;
	int frame_index;
};


void read(int index) {
	VideoCapture cap(index, CAP_ANY);
	while (true) {
		Mat frame;
		(*cap) >> frame;
		frames.
	}






	// Frame outputFrame;
	// Mat frame;
	// vcap >> frame;
	// cout << "Read new frame!" << endl;
	// frame_pointer->frame_index = frame_pointer->frame_index + 1;
}

void write(VideoWriter *video, Frame *frame_pointer) {
	video->write(frame_pointer->frame);
	cout << "Wrote new frame!" << endl;
}

int main() {
	VideoCapture vcap(0, CAP_ANY);
	cout << vcap.getBackendName() << endl;
	if (!vcap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	//int frame_width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);
	//int frame_height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int frame_width = 3840;
	int frame_height = 2160;
	vcap.set(CV_CAP_PROP_FRAME_WIDTH, frame_width);
	vcap.set(CV_CAP_PROP_FRAME_HEIGHT, frame_height);
	VideoWriter video("out.avi", CAP_FFMPEG, CV_FOURCC('I', 'Y', 'U', 'V'), 30, Size(frame_width, frame_height), true);
	cout << video.getBackendName() << endl;
	video.set(VIDEOWRITER_PROP_NSTRIPES, -1);

	thread threads[NUM_THREADS];
	Frame f;
	f.frame_index = 0;
	// Testing on 10 iterations
	//int index;
	//int num_iterations = 10;
	//for (index = 0; index < num_iterations; index++) {
	//	cout << "This is iteration " << index << endl;
	//}
	thread read_thread(read, *vcap, *f);
}
