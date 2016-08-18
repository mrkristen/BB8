#include"OpenCVImp.h"
#include"Directory.h"
#include"csvGenerator.h"

bool csv_handler::isExist;

void FaceRecognizedInitialise::saveModel()
{
	model->save(cv::String("Model.xml"));
}

FaceRecognizedInitialise::FaceRecognizedInitialise()
{
   model = createLBPHFaceRecognizer();

   model->load(cv::String("Model.xml"));

}

FaceRecognizedInitialise::~FaceRecognizedInitialise()
{
	saveModel();
}

string FaceRecognizedInitialise::predict(Mat &testImage, double &confidence)
{
	int label = -1;
	double cconfidece = 0.0;
	model->predict(testImage, label, cconfidece);

	confidence = cconfidece;

	csv_handler Sameple;
	return Sameple.findName(label);

}

void FaceRecognizedInitialise::trainImages(vector<UMat>& Images  ,string &label)
{

	{
		csv_handler csv;
		csv.createCsv(label);
	}

	if (csv_handler::isExist == false)
	{
		vector<int> allLabels;
		vector<Mat> allImages;

		CkCsv csv;
		if (csv.LoadFile("faces.csv") == false)
			exit(-2);
		csv.put_HasColumnNames(false);

		for (int i = 0; i < csv.get_NumRows(); i++)
		{
			int labeloftheimage = atoi((string(csv.getCell(i, 0)).c_str()));
			Mat img = imread(csv.getCell(i, 2), 0);

			allLabels.push_back(labeloftheimage);
			allImages.push_back(img);
		}

		model->train(allImages, allLabels);
	}
	else
		{
			vector<int> allLabels;
			vector<Mat> allImages;
			
			CkCsv csv;
			if (csv.LoadFile("faces.csv") == false)
				exit(-2);
			csv.put_HasColumnNames(false);

			for (int i = 0; i < Images.size(); i++)
			{
				int labeloftheimage = atoi(csv.getCell(csv.get_NumRows() - 1, 0));
				Mat img;
				Images[i].copyTo(img);

				allImages.push_back(img);
				allLabels.push_back(labeloftheimage);
			}

		model->update(allImages, allLabels);
	}

}


int FaceRecognizedInitialise::loadCascade(std::string location)
{
	face_haar_cascade = location;
	if (!haar_cascade.load(location))
		exit(-1);

	return 1;
}


int FaceRecognizedInitialise::imagepush(UMat face)
{
	faces.push_back(face);

	return faces.size();
}

int FaceRecognizedInitialise::imagesSave(FaceRecognizedInitialise &Obj, string name)
{
	Directory Save;
	string faceDir("faces\\");
	faceDir += name;

	Save.createDirectory(faceDir);

	for (int i = 0; i < faces.size(); i++)
	{
		char buffer[50];
		itoa(i, buffer, 10);
		strcat(buffer, ".jpg");

		imwrite(buffer, faces[i]);
	}

	Save.End();

	Obj.trainImages(faces,name);

	faces.clear();
	
	return 0;
}


