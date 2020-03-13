#include "opencv2/opencv.hpp"
#include <bits/stdc++.h>

using namespace std;
using namespace cv;

int main(){

  // Create a VideoCapture object and use camera to capture the video
  VideoCapture cap(0); 

  // Check if camera opened successfully
  if(!cap.isOpened())
  {
    cout << "Error opening video stream" << endl; 
    return -1; 
  } 

  // Default resolution of the frame is obtained.The default resolution is system dependent. 
  int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH); 
  int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); 
  
  // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
  VideoWriter video("outcpp.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height)); 
  time_t start,end;
  time(&start);
  while(1)
  { 
    Mat frame; 
    
    // Capture frame-by-frame 
    cap >> frame;
 
    // If the frame is empty, break immediately
    if (frame.empty())
      break;
    // split it into 3 channels
    vector<Mat>gray;
    split(frame,gray);
    Mat hsv;
    cvtColor(frame,hsv,COLOR_BGR2GRAY);
    
    auto red=gray[2];

    imshow( "Frame", frame );
    for(int i=1;i<31;i+=2){
      GaussianBlur(hsv,frame,Size(i,i),64,8);
    }
    
    // Display the resulting frame    
    imshow("Modified frame",frame);
    //frame=noisy_image;
    // Write the frame into the file 'outcpp.avi'
    video.write(frame);
 
    // Press  ESC on keyboard to  exit
    char c = (char)waitKey(1);
    if( c == 27 ) 
      break;
    // 10 sec to exit
    time(&end);
    double dif=difftime(end,start);
    if(dif==10){
      cout<<"DONE "<<dif<<"\n";
      break;
    }
  }

  // When everything done, release the video capture and write object
  cap.release();
  video.release();

  // Closes all the windows
  destroyAllWindows();
  return 0;
}