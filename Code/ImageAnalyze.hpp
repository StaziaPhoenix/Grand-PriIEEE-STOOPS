#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <stdlib.h>
#include <iostream>

#define __STDC_CONSTANT_MACROS
using namespace std;
using namespace cv;

class ImageAnalyze{        
private:
    short imgwidth;
    short imgheight;
    VideoCapture cap;
    Mat imgThresholded;    
    Mat imgOriginal;

    unsigned char iLowH;
    unsigned char iHighH;
    unsigned char iLowS;
    unsigned char iHighS;
    unsigned char iLowV;
    unsigned char iHighV;
    
    int leftmargin;
    int rightmargin; 
    int centermargin;
    int rightlinedetect;
    int leftlinedetect;
    float dist;    

    bool thresholdImage();
    bool analyzeImg( int & rightline, int & leftline);

public:

    explicit ImageAnalyze(const short width = 320, const short height = 240, 
                   const char vidport = 0): cap(0){
        if(!cap.isOpened()){
            cout << "Cannot open webcam" << endl;
            exit(EXIT_FAILURE);
        }
        cout << "contructing" << endl;    
        imgwidth = width;
        imgheight = height;
        
        cap.set(CV_CAP_PROP_FRAME_WIDTH, imgwidth);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, imgheight);

        iLowH = 0;
        iHighH = 179;
        iLowS = 0;
        iHighS = 62;
        iLowV = 182;
        iHighV = 255;

        dist = (9)*tan(62);
        rightlinedetect = 0;
        leftlinedetect = 0;
        
        thresholdImage();
        analyzeImg( rightmargin, leftmargin);
        
        centermargin = (leftmargin + rightmargin)/2;    
        cout << leftmargin << " " << rightmargin << " ";
        cout << centermargin << endl;
    }

    short getRLineDetect() const;
    short getLLineDetect() const;

    unsigned char errorDetect(); 
    
};
