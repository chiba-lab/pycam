#include "opencv2/opencv.hpp"
#include <iostream>
#include <thread>

using namespace std;
using namespace cv;

int main(){

    VideoCapture vcap(0); 
      if(!vcap.isOpened()){
             cout << "Error opening video stream or file" << endl;
             return -1;
      }

   // only gets lower res right now, will change to 4K
	int frame_width = 3840;
	int frame_height = 2160;
	vcap.set(CV_CAP_PROP_FRAME_WIDTH, frame_width);
	vcap.set(CV_CAP_PROP_FRAME_HEIGHT, frame_height);
   VideoWriter video("out.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height),true);

   Mat currFrame;

   thread readThread(read, vcap);
   thread writeThread(currFrame, video);
}

void read(VideoCapture& vcap) {
  vcap >> frame;
  currFrame = frame;
}

void write(Mat& frame, VideoWriter& video){
  video.write(frame);
  imshow("Frame", frame);
  char c = (char)waitKey(33);
  if( c == 27 ) break;
}
