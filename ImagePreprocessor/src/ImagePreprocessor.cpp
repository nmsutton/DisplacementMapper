//============================================================================
// Name        : ImagePreprocessor.cpp
// Author      : Nate Sutton
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
// from http://docs.opencv.org/doc/tutorials/introduction/display_image/display_image.html
//============================================================================

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <math.h>
#include <iostream>
#include <string>

using namespace cv;

using namespace std;

double pi = M_PI;
double sigCent = 0.3; // sigmaCenter
double sigSurr = 1.5; // sigmaSurround
double Balance = 5; // Balance between center and surround
double ms = .001; // miliseconds unit
double aCenter = 1/(16*ms); // latency of response
double aSurround = 1/(32*ms); // latency of response
double bCenter = 1/(64*ms); // time of reversal
double bSurround = 1/(64*ms); // time of reversal
double z = 0; // depth dimension
double tauMs = 0;
double maxTau = 200;
double xStart = -2;
double xEnd = 2;
double yStart = -2;
double yEnd = 2;
double imageHeightAndWidth = 512;
double increment = (xEnd-xStart)/imageHeightAndWidth;
double c = 0.02;
String outputImageFile = "./gaborFilterDispMap.bmp";

double time(double a, double b, double tau) {
	double timeFunct = 0;

	timeFunct = ((pow(a, 2)*tau)*exp(-a*tau))-((pow(b,2)*tau)*exp(-b*tau));

	return timeFunct;
}

double diffOfGaussians(double x, double y, double tau) {
	/*
	 * For reference: standard gaussian
	 * https://en.wikipedia.org/wiki/Gaussian_function
	 * a = height of curve peak
	 * mu = mean.  Position of center of peak relative to x
	 * sigma = standard deviation.  width of the "bell"
	 *
	 * f(x) = a*exp(-((x-mu)^2)/((2*sigma)^2))
	 */

	double diffOfGauss = 0; // difference of gaussians

	diffOfGauss = (((time(aCenter, bCenter, tau)/(2*pi*pow(sigCent,2)))*exp(-((pow(x,2)+pow(y,2))/(2*pow(sigCent,2)))))-
			((Balance*(time(aSurround, bSurround, tau))/(2*pi*pow(sigSurr,2)))*exp(-((pow(x,2)+pow(y,2))/(2*pow(sigSurr,2))))));

	//cout << diffOfGauss;cout<<" ";cout<<x;cout<<" ";cout<<y;cout<<" ";cout<<(((time(aCenter, bCenter, tau)/(2*pi*pow(sigCent,2)))*exp(-((pow(x,2)+pow(y,2))/(2*pow(sigCent,2))))));cout<<" ";cout<<(time(aCenter, bCenter, tau));cout<<" ";cout<<exp(-bSurround*tau);cout<<"\n";
	return diffOfGauss;
}

int main(int argc, char** argv) {
	/*
	 * Generate LGN gabor filer displacement map
	 * Parameters:
	 * yD; // y translated to scale used for gabor function
	 * xD; // x translated to scale used for gabor function
	 */
	double xD;
	double yD;
	double conversionConstant = ((xEnd - xStart) / imageHeightAndWidth);
	cout<<"test";
	Mat outputImage;
	outputImage = imread(outputImageFile, CV_LOAD_IMAGE_COLOR);

	//double y = 0;
	//maxTau = 51;
	for (double tau = 0; tau < maxTau; tau++) {
		tauMs = tau * ms;
		double y = imageHeightAndWidth/2;
		//for(double y=0;y<imageHeightAndWidth;y++)
		//{
			for (int x=0;x<imageHeightAndWidth;x++)
			{
				// Difference of gausians
				xD = (x * conversionConstant) + xStart;
				yD = (y * conversionConstant) + yStart;


				z = diffOfGaussians(xD, yD, tauMs);
				//z = z*-1;
				//z = z -
				double greyrange = 255;
				double startingshift = 25;//greyrange/1.5;
				double scalingf = greyrange/90;///greyrange/(4.5+2);
				z = (z*scalingf)+startingshift;

				// write pixels
				//outputImage.at<Vec3b>(y,x) = Vec3b(z,z,z);
				outputImage.at<Vec3b>(tau,x) = Vec3b(z,z,z);
				//outputImage.at<Vec3b>(tau,x) = Vec3b(200,200,200);
				cout << z;cout<<" ";cout<<xD;cout<<" ";cout<<yD;cout<<"\n";
			}
			//z = 150;
			//outputImage.at<Vec3b>(y,x) = Vec3b(150,150,150);
			//////
		//}
		namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
		imshow( "Display Image", outputImage );

		// from http://stackoverflow.com/questions/23997266/opencv-animation
		waitKey(33);
	}

	//imwrite(outputImageFile, outputImage );


	/*namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
	imshow( "Display Image", outputImage );

	waitKey(0);*/

	cout << "done";
	return 0;
}


