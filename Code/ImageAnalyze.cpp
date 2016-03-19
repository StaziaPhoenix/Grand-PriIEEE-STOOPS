#include "ImageAnalyze.hpp"
#include <iostream>

#define DEBUG 1

using namespace std;
using namespace cv;

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
        //cout << i << endl;
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
    
    //cout << "bro" << endl;    

    return firstdetect && seconddetect;    
}

/* --------------------------------
 *	Stazia edited to return the correction angle. 
 *	See notes on dist above.
 * ------------------------------ */
unsigned char ImageAnalyze::errorDetect(){

    thresholdImage();
    analyzeImg(rightlinedetect, leftlinedetect);
    
    int centerline = (leftlinedetect + rightlinedetect)/2;
    int temp = centerline - centermargin;
    if( centerline == centermargin ){
        return 90;
    }else if( centerline < centermargin ){
        return 90+(atan(((temp*1.25)/((rightmargin-centermargin)*dist)))*(180/3.141592)); // see global dist comment
    }else{
        return 90-(atan(((temp*1.25)/((centermargin-rightmargin)*dist)))*(180/3.141592)); // see global dist comment
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

