#include <stdio.h>
#include <math.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;


int main(){
	CascadeClassifier face_cascade, eye_cascade;

	if(!face_cascade.load("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml")){
		cout<< " Error while loading cascade file for face" << endl;
	return 1;
	}


	if(!eye_cascade.load("/usr/local/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml")){
        	cout<< " Error while loading cascade file for eye" << endl;
        return 1;
        }	

	VideoCapture capture("rtsp://admin:12345@10.73.73.26/h264/ch1/main/av_stream");
        	if (!capture.isOpened()) {
			cout<<"Error while opening camera"<<endl;
               		return 1;
                }
	Mat src_img, gray_img;
        
//	capture>>src_img;

	vector<Rect> faces, eyes;

	while(1){
		capture>>src_img;
//		waitKey(5);
#if 0
		cvtColor(src_img,gray_img,CV_BGR2GRAY);
		equalizeHist(gray_img,gray_img);
//		face_cascade.detectMultiScale(gray_img, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, cvSize(0,0), cvSize(500,500));
              	face_cascade.detectMultiScale(gray_img, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(50,50));

		for(int i = 0; i<faces.size(); i++){
		
		Point pt1(faces[i].x + faces[i].width, faces[i].y+faces[i].height);
		Point pt2(faces[i].x, faces[i].y);

		Mat faceROI = gray_img(faces[i]);
		eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 3, 0 |CASCADE_SCALE_IMAGE, Size(50,50));
		for(size_t j=0; j<eyes.size(); j++){
			Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height * 0.5);
			int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
			circle(src_img, center, radius, Scalar(255,0,0), 2, 8, 0);
			}
		rectangle(src_img, pt1, pt2, Scalar(0,255,0),2, 8, 0);			
		}
#endif

	imshow("Result", src_img);

	waitKey(3);
//	int c = waitKey(30);
//	if((char)c == 37)
//	break;
	}						
return 0;	
}
