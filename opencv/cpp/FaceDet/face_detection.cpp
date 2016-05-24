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
#include <ctime>

using namespace cv;
using namespace std;


int main(){
	CascadeClassifier face_cascade, eye_cascade;
        namedWindow("Result");	//To show resulatnt image in this window.
	namedWindow("Crop");	//To show cropped image in this window.

//	if(!face_cascade.load("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml")){
	if(!face_cascade.load("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml")){
		cout<< " Error while loading cascade file for face" << endl;
	return 1;
	}


	if(!eye_cascade.load("/usr/local/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml")){
        	cout<< " Error while loading cascade file for eye" << endl;
        return 1;
        }	

	VideoCapture capture("rtsp://admin:12345@10.73.73.26/h264/ch1/main/av_stream?tcp");
        	if (!capture.isOpened()) {
			cout<<"Error while opening camera"<<endl;
               		return 1;
                }
//	capture.set(CV_CAP_PROP_BUFFERSIZE, 500);
	Mat src_img, gray_img;
        
//	capture>>src_img;

	vector<Rect> faces, eyes;
	bool count = true;
	Rect crop;	//To create resize the grabbed faces and store the result  in this variable.
	int faceCount = 0;
	char imageToSave[50];	
	string folderName = "Faces";
	string folderRemoveCommand = "rm -rf" + folderName;
        system(folderRemoveCommand.c_str());	//Remove the folder if already present
	string folderCreateCommand = "mkdir " + folderName;
	system(folderCreateCommand.c_str());	//Create the folder if not present.

	
	while(capture.read(src_img)){
//for(;;){
//              capture.retrieve(src_img);
//                capture>>src_img;
//              bool gsuccess = capture.grab();
//              capture.retrive(src_img);

//                bool bSuccess = capture.read(src_img); // read a new frame from video
//                if (!bSuccess) //if not success, break loop
//                {
//                        cout << "Cannot read the frame from video file" << endl;
//                        break;
//                }

//              iwaitKey(5);
clock_t begin = clock();
#if 1
//if(count){
//clock_t begin = clock();


                cvtColor(src_img,gray_img,CV_BGR2GRAY);
                equalizeHist(gray_img,gray_img);
//              face_cascade.detectMultiScale(gray_img, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, cvSize(0,0), cvSize(500,500));
               face_cascade.detectMultiScale(gray_img, faces, 1.11, 4, 0 | CASCADE_SCALE_IMAGE, Size(10,10));

                for(int i = 0; i<faces.size(); i++){

                Point pt1(faces[i].x + faces[i].width, faces[i].y+faces[i].height);
                Point pt2(faces[i].x, faces[i].y);

                Mat faceROI = gray_img(faces[i]);
		if(!faces.empty()){

//To grab faces and store in separate jpg files.
                if((faces[i].y - 20) >= 0)
                faces[i].y -= 20;

                faces[i].width +=20;
                faces[i].height+=20;

                //Grab faces in sepaate matrix
                Mat crop_img = src_img(faces[i]);

                imshow("Crop", crop_img);
                //Write in jpg file grabbed face
                faceCount +=1;
                sprintf(imageToSave,"%s//face%d.jpg",folderName.c_str(),faceCount);
                imwrite(imageToSave, crop_img);



                eye_cascade.detectMultiScale(faceROI, eyes, 1.11, 3, 0 |CASCADE_SCALE_IMAGE, Size(10,10));
                for(size_t j=0; j<eyes.size(); j++){
                        Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height * 0.5);
                        int radius = cvRound((eyes[j].width + eyes[i].height) * 0.25);
                        circle(src_img, center, radius, Scalar(255,0,0), 2, 8, 0);
                        }
//                if(!eyes.empty())i
//To show the rectangle on face
                rectangle(src_img, pt1, pt2, Scalar(0,255,0),2, 8, 0);
		}
                }
//count = false;

//}
//else{
//count = true;
//}
#endif
        if(!src_img.empty())
        imshow("Result", src_img);

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout<<"elasped Time-"<<elapsed_secs << endl;

	waitKey(1);
//	int c = waitKey(30);
//	if((char)c == 37)
//	break;
	}						
	
    //destroy GUI windows
    destroyAllWindows();

    //delete capture object
    capture.release();

return 0;	
}
