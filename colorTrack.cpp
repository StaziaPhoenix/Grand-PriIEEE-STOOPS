#include <iostream>
 
//#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
// 1/5 of image size x middle, 1/7 of image size y bottom
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

 int main( int argc, char** argv ){
    VideoCapture cap(0); 

    if ( !cap.isOpened() ){
         cout << "Cannot open the web cam" << endl;
         return -1;
    }
    
    cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);
//    namedWindow("Control", CV_WINDOW_AUTOSIZE); 

    int iLowH = 0;
    int iHighH = 179;

    int iLowS = 0; 
    int iHighS = 62;
   
    int iLowV = 182;
    int iHighV = 255;

    /*
    cvCreateTrackbar("LowH", "Control", &iLowH, 179);  //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);
   
    cvCreateTrackbar("LowS", "Control", &iLowS, 255); // Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);
   
    cvCreateTrackbar("LowV", "Control", &iLowV, 255);//  Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);
    */
 
    while (true){
        Mat imgOriginal;
        bool bSuccess = cap.read(imgOriginal);  
        
        if (!bSuccess) {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }
        Mat imgHSV;
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

        Mat imgThresholded;
        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5))); 
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5))); 
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5))); 
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        
        unsigned char * ptr = imgThresholded.ptr<unsigned char>(206);
        
        Mat hist(256, 320, CV_8UC1, Scalar(255,0,0));
        for(int i = 0; i < 640; ++i){
            if(ptr[i] > 0){
                line(hist, Point(i, 255), Point(i, 64), Scalar(0, 255, 0), 1, 8);
                //cout << ">" << i << endl;
            }

            if(ptr[i] == 0){
                line(hist, Point(i, 255), Point(i, 128), Scalar(0, 255, 0), 1, 8);
               // cout << "==" << i <<  endl;
            }
        } 
        
        /*for(int i = 0; i < imgThresholded.cols; ++i){
            printf("%d", ptr[i]);
        } */
        imshow("Thresholded Image", imgThresholded); 
        imshow("Original", imgOriginal);
        imshow("Original", hist);
        if (waitKey(30) == 27) {
            cout << "esc key is pressed by user" << endl;
            break; 
        }
    } 
    //imwrite("edges.png", imgThresholded);
    //imwrite("capture.png", imgOriginal);
    //imwrite("hist.png", hist);
    return 0;
}
