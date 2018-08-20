#include <opencv2/opencv.hpp>
#include <iostream>
#include "fhog.h"

using namespace cv;
using namespace std;

int main()
{
	int scale = 96;
	//��ȡͼƬ
	Mat img = imread('img path');
	if (img.empty())
	{
		break;
	}
	Mat img_fix;
	resize(img, img_fix, Size(scale, scale)); //��׼��ͼƬ��С

	//��ȡfhog����ͼ
	int cell_size = 4;
	int size_patch[3];
	IplImage z_ipl = img_fix;
	Mat FeaturesMap;
	CvLSVMFeatureMapCaskade *map;
	getFeatureMaps(&z_ipl, cell_size, &map);
	normalizeAndTruncate(map, 0.2f);
	PCAFeatureMaps(map);
	size_patch[0] = map->sizeY;
	size_patch[1] = map->sizeX;
	size_patch[2] = map->numFeatures;
	FeaturesMap = cv::Mat(cv::Size(map->numFeatures, map->sizeX*map->sizeY), CV_32F, map->map);  // Procedure do deal with cv::Mat multichannel bug
	FeaturesMap = FeaturesMap.t();
	freeFeatureMapObject(&map);

	//������������(sizeY*sizeX*numFeatures)*1
	Mat test_line;
	test_line = FeaturesMap.reshape(1, 1); 


	//������ȡ��ϣ����н�һ���Ĳ���





	return 0;
}