#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/videoio/videoio_c.h"
#include "opencv2/highgui.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core.hpp"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>

using namespace std;
using namespace cv;
using namespace chrono;

int NUM_THREADS = 2;
int FPS = 30;

// General constants
Mat currentFrame;
int frameIndex = 0;
int frame_width = 3840;
int frame_height = 2160;

// Set up reader
VideoCapture vcap(0);
vcap.set(CV_CAP_PROP_FRAME_WIDTH, frame_width);
vcap.set(CV_CAP_PROP_FRAME_HEIGHT, frame_height);
vcap.set(CV_CAP_PROP_FPS, FPS);

// Set up writer
VideoWriter writer("out.avi", CAP_FFMPEG, CV_FOURCC('I', 'Y', 'U', 'V'), 30, Size(frame_width, frame_height), true);

// Vector of images
std::vector<int> v;


void read() {
  Mat frame;
  vcap >> frame;
  currentFrame = frame;
  frameIndex = frameIndex + 1;
  cout << "Read frame" << '\n';
  return;
}

void write() {
  writer.write(currentFrame);
  cout << "Wrote frame " << '\n';
  cout << frameIndex << '\n';
  return;
}


int main(int argc, char const *argv[]) {

  thread readThread(read);
  thread writeThread(write);

  readThread.join();
  writeThread.join();
  return 0;
}
