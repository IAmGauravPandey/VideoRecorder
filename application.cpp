#include "opencv2/opencv.hpp"
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
using namespace cv;

bool videoRecorder(string videoname){
    videoname+=".avi";
    VideoCapture cap(0); 
  // Check if camera opened successfully
  if(!cap.isOpened())
  {
    cout << "Error opening video stream" << endl; 
    return 0; 
  } 
  // Default resolution of the frame is obtained.The default resolution is system dependent. 
  int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH); 
  int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); 
  
  // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
  VideoWriter video(videoname,CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height)); 
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
      break;
    }
  }
  // When everything done, release the video capture and write object
  cap.release();
  video.release();
  // Closes all the windows
  destroyAllWindows();
  return 1;
}
vector<pair<string,string>>userInfo;

bool Authenticate(string Username,string Password){
    for(auto user:userInfo){
        if(user.first==Username and user.second==Password){
                return true;
            }
    }
    return false;
}

bool Login(){
    string userName;
    string userPassword;
    int loginAttempt = 0;
    bool login=false;
    while (loginAttempt < 5)
    {
        cout << "Please enter your user name: ";
        cin >> userName;
        cout << "Please enter your user password: ";
        cin >> userPassword;
        if(Authenticate(userName,userPassword)){
            cout<<"Welcome "<<userName<<"\n";
            cout << "Thank you for logging in.\n";
            login=true;
            break;
        }
        else
        {
            cout << "Invalid login attempt. Please try again.\n" << '\n';
            loginAttempt++;
        }
    }
    if (loginAttempt == 5)
    {
            cout << "Too many login attempts! The program will now terminate.\n";
            return false;
    }
    if(login)return true;
    return false;
}
int main(){
    userInfo.pb({"inkers","inkers"});
    userInfo.pb({"gaurav","gaurav"});
    userInfo.pb({"demo","demo"});
    cout<<"For Demo use 'demo' as username and 'demo' as password\n";
    if(!Login()){
        return 0;
    }
    vector<string>videoList;
    while(1){
        cout<<"Press q to quit or r to record a video from webcam\n";
        char input;
        cin>>input;
        if(input=='q'){
            cout<<"Thank You for using our Service.\n";
            return 0;
        }
        if(input=='r'){
            string videoname;
            cout<<"Enter the Name of the recorded video.\n";
            cin>>videoname;
            if(videoRecorder(videoname)){
                videoList.pb(videoname);
            }
        }
        cout<<"List of the videos of you have recorded.\n";
        for(auto video:videoList){
            cout<<video<<"\n";
        }
    }
}