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

#define NUM_THREADS 2
#define FPS 30

// General constants
Mat currentFrame;
int frameIndex = 0;
int frame_width = 3840;
int frame_height = 2160;

// Set up reader
VideoCapture vcap(0);
// vcap.set(CV_CAP_PROP_FRAME_WIDTH, frame_width);
// vcap.set(CV_CAP_PROP_FRAME_HEIGHT, frame_height);

// Set up writer
VideoWriter writer("out.avi", CAP_FFMPEG, CV_FOURCC('I', 'Y', 'U', 'V'), 30, Size(frame_width, frame_height), true);


void read() {
  vcap.set(CV_CAP_PROP_FRAME_WIDTH, frame_width);
  vcap.set(CV_CAP_PROP_FRAME_HEIGHT, frame_height);
  // vcap.set(CV_CAP_PROP_FPS, FPS);
  Mat frame;
  vcap >> frame;
  // imshow("image", frame);
  // waitKey(0);
  currentFrame = frame;
  frameIndex = frameIndex + 1;
  cout << "Read frame" << '\n';
}

void write(VideoWriter write) {
  imshow("image", currentFrame);
  waitKey(1);
  writer.write(currentFrame);
  cout << "Wrote frame " << '\n';
  cout << frameIndex << '\n';
}

void update() {
  read();
  write(writer);
  //this_thread::sleep_for(milliseconds(30));
}

int main(int argc, char const *argv[]) {
  /* code */
  int i = 0;
  while (i < 300) {
    update();
    i++;
  }
  //new thread readThread(read);
  //new thread writeThread(write, writer);
  //read();
  //write(writer);
  return 0;
}
