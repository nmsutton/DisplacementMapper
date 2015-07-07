//============================================================================
// Name        : ImagePreprocessor.cpp
// Author      : Nate Sutton
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
// from http://docs.opencv.org/doc/tutorials/introduction/display_image/display_image.html
// reference http://stackoverflow.com/questions/5721796/how-do-you-implement-the-factorial-function-in-c
//============================================================================

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace cv;

using namespace std;

double pi = M_PI;
double sigCent = 0.3; // sigmaCenter
double sigSurr = 1.5; // sigmaSurround
double Balance = 5.0; // Balance between center and surround
double ms = 0.001; // miliseconds unit
double aCenter = 1.0/(16.0*ms); // latency of response
double aSurround = 1.0/(32.0*ms); // latency of response
double bCenter = 1.0/(64.0*ms); // time of reversal
double bSurround = 1.0/(64.0*ms); // time of reversal
double z = 0.0; // depth dimension
double tauMs = 0.0;
double maxTau = 200.0;
double xStart = -4.0;//-6.0;//-4.0;
double xEnd = 4.0;//6.0;//4.0;
double yStart = -5.0;//-7.0;//-5.0;
double yEnd = 5.0;//7.0;//5.0;
double imageHeightAndWidth = 512.0;
double increment = (xEnd-xStart)/imageHeightAndWidth;

/*double pi = M_PI;
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
double increment = (xEnd-xStart)/imageHeightAndWidth;*/
//double c = 0.02;
// gabor variables
double sigmaX = 1.0;
double sigmaY= 2.0;
double k = (1.0/0.5); // preferred spatial frequency
double phi = 0;//1-pi;//0; // preferred spatial phase
double a = 1.0/15.0;//1.0/20.0;//1.0/15.0;//(1/(15*ms));//20*ms;
// prime functions
double c = 0.02;//(1/.02);//0.02; // converts units of time (ms) and space (degrees). e.g. degrees/time.
double psi = pi/9.0; // space-time rotation angle
//String outputImageFile = "./gaborFilterDispMap.bmp";
//String outputImageFileForSaving = "./media/gaborFilterDispMap";
String outputImageFile = "./blankImage.bmp";
String outputImageFileForSaving = "./diffGST.bmp";

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

unsigned int iter_factorial(unsigned int n)
{
	// http://stackoverflow.com/questions/5721796/how-do-you-implement-the-factorial-function-in-c
    unsigned int ret = 1;
    for(unsigned int i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

double gaborTime(double tau) {
	return a*exp(-(a*tau))*((pow((a*tau),5)/iter_factorial(5))-(pow((a*tau),7)/iter_factorial(7)));
	//return a*exp(-(a*tau))*(pow((a*tau),5)/iter_factorial(5));
}

double gabor(double x, double y) {
	double gabor = 0;

	gabor = (1/(2*pi*sigmaX-sigmaY))*exp(((-(pow(x,2)))/(2*sigmaX,2))-(pow(y,2)/(2*sigmaY,2)))*cos((k*x)-phi);

	return gabor;
}

double xPrime(double x, double tau) {
	return (x*cos(psi))-(c*tau*sin(psi));
}

double tauPrime(double x, double tau) {
	return ((tau*cos(psi))+((x/c)*sin(psi)));
}

int main(int argc, char** argv) {
	/*
	 * Generate LGN gabor filer displacement map
	 * Parameters:
	 * yD; // y translated to scale used for gabor function
	 * xD; // x translated to scale used for gabor function
	 */

	/*double xD;
	double yD;
	double conversionConstant = ((xEnd - xStart) / imageHeightAndWidth);
	Mat outputImage;
	outputImage = imread(outputImageFile, CV_LOAD_IMAGE_COLOR);*/

	/*//double y = 0;
	//maxTau = 1;
	for (double tau = 0; tau < maxTau; tau++) {
		//tauMs = tau * ms;
		//double y = imageHeightAndWidth/2;
		for(double y=0;y<imageHeightAndWidth;y++)
		{
			for (int x=0;x<imageHeightAndWidth;x++)
			{
				// Difference of gausians
				xD = (x * conversionConstant) + xStart;
				yD = (y * conversionConstant) + yStart;

				//z = diffOfGaussians(xD, yD, tauMs);
				double greyrange = 255;
				double startingshift = 50;//greyrange/1.5;
				double scalingf = 1/1.0;///greyrange/(4.5+2);
				//double scalingf = greyrange*1;
				//z = (z*scalingf)+startingshift;

				double gaborSpaceDim = gabor(xPrime(xD,tau), yD);
				double gaborTimeDim = gaborTime(tauPrime(xD,tau));
				//gaborSpaceDim = (gaborSpaceDim/scalingf);
				//gaborTimeDim = (gaborTimeDim/scalingf);

				//z = gaborSpaceDim;//*gaborTimeDim;
				z = gaborSpaceDim*gaborTimeDim;
				//z = z * greyrange;
				//z = z * pow(10, 15.1);
				z = z * pow(10, 5);
				z = z + startingshift;
				if (z > greyrange) {z = greyrange;}
				else if (z < 0) {z = 0;}

				//z = gabor(xD, yD);
				//z = z * (2*pi*sigmaX*sigmaY);

				//z = z*-1;
				//z = z -

				//z = z*-1;

				// write pixels
				outputImage.at<Vec3b>(y,x) = Vec3b(z,z,z);
				//outputImage.at<Vec3b>(tau,x) = Vec3b(z,z,z);
				//outputImage.at<Vec3b>(tau,x) = Vec3b(200,200,200);
				//double x2 = 2;
				//double tau2 = .05;
				//cout << z;cout<<" ";cout<<xD;cout<<" ";cout<<yD;cout<<"\n";
				//cout << z;cout<<" ";cout<<xD;cout<<" ";cout<<yD;cout<<" ";cout<<tau;cout<<" ";cout<<xPrime(xD,tau);cout<<" ";cout<<tauPrime(xD,tau);cout<<"\n";
				//cout << z;cout<<" ";cout<<xD;cout<<" ";cout<<yD;cout<<" ";cout<<tau;cout<<" ";cout<<gabor(xPrime(xD,tau), yD);cout<<" ";cout<<gaborTime(tau);cout<<"\n";
				//cout << z;cout<<" ";cout<<xD;cout<<" ";cout<<yD;cout<<" ";cout<<gaborSpaceDim;cout<<" ";cout<<gaborTimeDim;cout<<"\n";
			}
			//z = 150;
			//outputImage.at<Vec3b>(y,x) = Vec3b(150,150,150);
			//////
		}
		stringstream ss;
		ss << outputImageFileForSaving;
		ss << "_";
		ss << tau;
		ss << ".bmp";

		//char arr [50];
		//int q=4;
		//sprintf (arr, "decimal %d in the array", q);
		//double a=2.132;
		//char arr[sizeof(tau)];
		//memcpy(&arr,&tau,sizeof(tau));

		//char outputImageFileForSaving2[] = outputImageFileForSaving;
		//outputImageFileForSaving = sprintf(outputImageFileForSaving, outputImageFileForSaving+"_%d.bmp", tau);
		//outputImageFileForSaving + "_" + std::to_string(tau) + ".bmp";
		//cout<<ss.str();cout<<" ";cout<<*tauCopy;cout<<"\n";
		imwrite(ss.str(), outputImage );
		namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
		imshow( "Display Image", outputImage );

		// from http://stackoverflow.com/questions/23997266/opencv-animation
		//waitKey(0);
		waitKey(33);
	}*/

	/*for (double tau = 0; tau < maxTau; tau++) {
		tauMs = tau * ms;
		for(double y=0;y<imageHeightAndWidth;y++)
		{
			for (int x=0;x<imageHeightAndWidth;x++)
			{
				// Difference of gausians
				xD = (x * conversionConstant) + xStart;
				yD = (y * conversionConstant) + yStart;


				z = diffOfGaussians(xD, yD, tauMs);
				//z = z*-1;
				//z = z -
				double greyrange = 255;
				double startingshift = 50;//greyrange/1.5;
				//double scalingf = greyrange/90;///greyrange/(4.5+2);
				double scalingf = greyrange/45;///greyrange/(4.5+2);
				z = (z*scalingf)+startingshift;
				//z = z*-1;

				// write pixels
				outputImage.at<Vec3b>(y,x) = Vec3b(z,z,z);
				//outputImage.at<Vec3b>(tau,x) = Vec3b(z,z,z);
				//outputImage.at<Vec3b>(tau,x) = Vec3b(200,200,200);
				//cout << z;cout<<" ";cout<<xD;cout<<" ";cout<<yD;cout<<"\n";
			}
			//z = 150;
			//outputImage.at<Vec3b>(y,x) = Vec3b(150,150,150);
			//////
		}
		stringstream ss;
		ss << outputImageFileForSaving;
		ss << "_";
		ss << tau;
		ss << ".bmp";

		//char arr [50];
		//int q=4;
		//sprintf (arr, "decimal %d in the array", q);
		//double a=2.132;
		//char arr[sizeof(tau)];
		//memcpy(&arr,&tau,sizeof(tau));

		//char outputImageFileForSaving2[] = outputImageFileForSaving;
		//outputImageFileForSaving = sprintf(outputImageFileForSaving, outputImageFileForSaving+"_%d.bmp", tau);
		//outputImageFileForSaving + "_" + std::to_string(tau) + ".bmp";
		//cout<<ss.str();cout<<" ";cout<<*tauCopy;cout<<"\n";
		imwrite(ss.str(), outputImage );


		namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
		imshow( "Display Image", outputImage );

		// from http://stackoverflow.com/questions/23997266/opencv-animation
		waitKey(33);
	}*/

	//double y = 0;
	//maxTau = 51;
	double xStart = -2.0;
	double xEnd = 2.0;
	double yStart = -2.0;
	double yEnd = 2.0;

	double xD;
	double yD;
	double conversionConstant = ((xEnd - xStart) / imageHeightAndWidth);
	Mat outputImage;
	outputImage = imread(outputImageFile, CV_LOAD_IMAGE_COLOR);

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
				double scalingf = greyrange/45;///greyrange/(4.5+2);
				z = (z*scalingf)+startingshift;
				if (z<0) {z = 0;}

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

	imwrite(outputImageFileForSaving, outputImage );


	/*namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
	imshow( "Display Image", outputImage );

	waitKey(0);*/

	cout << "done";
	return 0;
}


