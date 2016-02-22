#include "ImageAnalyze.hpp"
#include <iostream>

#define DEBUG 1

using namespace std;
using namespace cv;


int dist = 24*tan(45);  // trash value. dist of scanline from car is
                        // h*tan(theta), where h is camera height from 
                        // ground (cm) and theta is camera angle from vertical.
                        // However, this yields in cm and is compared with
                        // # of pixels. How should we convert between px and cm?
                        // TODO Check webcam resolution, do rough & test estimate

bool ImageAnalyze::thresholdImage(){
    bool bSuccess = cap.read(imgOriginal);

    if(!bSuccess){
        cout << "Cannot read a frame from video stream" << endl;
        return bSuccess;
    }

    Mat imgHSV;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

    imgThresholded;
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), 
            imgThresholded);
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, 
          Size(5, 5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, 
          Size(5, 5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, 
          Size(5, 5)));
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, 
          Size(5, 5)));
    
    return bSuccess;
}

bool ImageAnalyze::analyzeImg(int & rightline, int & leftline) {
    
    unsigned char * ptr = imgThresholded.ptr<unsigned char>(45);
    bool firstdetect = false;
    bool seconddetect = false;
    

    //problematic when line start before left or after right edge. think about 
    //this later
    for(int i = 0; i < ( imgThresholded.cols - 1); ++i){ 
        cout << i << endl;
        if((!firstdetect || !seconddetect) && (ptr[i] - ptr[i+1]) ){
            if( !firstdetect ){
                rightline = i + 1;
                firstdetect = true;
            }else{
                leftline = i;
                seconddetect = true;
            }
        }
                
        if( 0 ){
            cout << ptr[i] << endl;
            cout << "firstdetect " << firstdetect << " seconddetect " << 
                    seconddetect << endl;
            
            Mat hist(256, imgwidth, CV_8UC1, Scalar(255, 255, 255));
            for(int i = 0; i < imgwidth; ++i){
                line(hist, Point(i, 128), Point(i, 128-ptr[i]), Scalar(0, 255, 0));
            }
    
            imwrite("edges.png", imgThresholded);
            imwrite("capture.png", imgOriginal);
        }
    }
    
            imwrite("edges.png", imgThresholded);
            imwrite("capture.png", imgOriginal);
    
    cout << "bro" << endl;    

    return firstdetect && seconddetect;    
}

/* --------------------------------
 *	Stazia edited to return the correction angle. 
 *	See notes on dist above.
 * ------------------------------ */
short ImageAnalyze::errorDetect(){

    thresholdImage();
    analyzeImg(rightlinedetect, leftlinedetect);
    
    int centerline = (leftlinedetect + rightlinedetect)/2;
    if( centerline == centermargin ){
        return 0;
    }else if( centerline < centermargin ){
        return 90-atan((centerline - centermargin)/dist); // see global dist comment
    }else{
        return 90+atan((centerline - centermargin)/dist); // see global dist comment
    }
}

short ImageAnalyze::getRLineDetect() const{
    if( !rightlinedetect && !leftlinedetect ){
        if( DEBUG ){
            cout << "Error could not be analyzed" << endl;
        }
        return 0;
    }
    
    return rightlinedetect;
}

short ImageAnalyze::getLLineDetect() const{
    if( !rightlinedetect && !leftlinedetect ){
        if( DEBUG ){
            cout << "Error could not be analyzed" << endl;
        }
        return 0;
    }
     
    return leftlinedetect;
}

