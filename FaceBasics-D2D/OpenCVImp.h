#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include <Windows.h>


using namespace cv;
using namespace cv::face;
using namespace std;


class FaceRecognizedInitialise
{
public:
		
	static string face_haar_cascade;
	static CascadeClassifier haar_cascade;
	Ptr<FaceRecognizer> model;
	

	static int im_width
		, im_height;

private:
	static vector<UMat> faces;

public:
	static int loadCascade(std::string location);

	static int imagepush(UMat face);

	static int imagesSave(FaceRecognizedInitialise &Obj, string name);
     
	FaceRecognizedInitialise();

	void trainImages(vector<UMat>& Images, string& label);

	void saveModel();

	std::string predict(Mat &testImage, double &confidence);

	~FaceRecognizedInitialise();
};


/*
string fn_haar = string(argv[1]);
string fn_csv = string(argv[2]);
int deviceId = atoi(argv[3]);
// These vectors hold the images and corresponding labels:
vector<Mat> images;
vector<int> labels;
// Read in the data (fails if no valid input filename is given, but you'll get an error message):
try {
	read_csv(fn_csv, images, labels);
}
catch (cv::Exception& e) {
	cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
	// nothing more we can do
	exit(1);
}
// Get the height from the first image. We'll need this
// later in code to reshape the images to their original
// size AND we need to reshape incoming faces to this size:
int im_width = images[0].cols;
int im_height = images[0].rows;
// Create a FaceRecognizer and train it on the given images:
Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
model->train(images, labels);
// That's it for learning the Face Recognition model. You now
// need to create the classifier for the task of Face Detection.
// We are going to use the haar cascade you have specified in the
// command line arguments:
//
cv2.CascadeClassifier haar_cascade;
haar_cascade.load(fn_haar);
// Get a handle to the Video device:
VideoCapture cap(deviceId);
// Check if we can use this device at all:
if (!cap.isOpened()) {
	cerr << "Capture Device ID " << deviceId << "cannot be opened." << endl;
	return -1;
}*/