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

int main(int argc, char** argv) {
	//! [load]

	String imageName5 = "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/src/blank.jpg";
	String imageName6 = "/home/nmsutton/Documents/Software/OpenGL/Media/general3.bmp";
	Mat image;
	image = imread(imageName6, CV_LOAD_IMAGE_COLOR);

	// Find anchor points
	bool anchorXAxisFound = false;
	int leftAnchorXAxis[2] = {0,0};
	int rightAnchorXAxis[2] = {0,0};
	int topAnchorYAxis[2] = {0,0};
	int bottomAnchorYAxis[2] = {0,0};
	for(int y=0;y<image.rows;y++)
	{
		for (int x=0;x<image.cols;x++)
		{
			if ((image.at<Vec3b>(y,x) == Vec3b(0,0,0) & anchorXAxisFound == false) &
					((x+11) < image.cols)) {
				for (int x2=x+100;x2<(image.cols/2);x2++) {
					// find first occuring limited line segment.
					if (image.at<Vec3b>(y,x2) == Vec3b(0,0,0) & anchorXAxisFound == false) {
						for (int x3=x;x3<x2;x3++) {
							//if ((x3%5==0) & (anchorXAxisFound == false)) {
							//if (anchorXAxisFound == false) {
							image.at<Vec3b>(y,x3) = Vec3b(255,255,0);
							//}
						}
						anchorXAxisFound = true;
						// establish X anchors and point of top of anchor Y axis
						leftAnchorXAxis[0] = y;
						leftAnchorXAxis[1] = x;
						rightAnchorXAxis[0] = y;
						rightAnchorXAxis[1] = x2;
						topAnchorYAxis[0] = y;
						topAnchorYAxis[1] = (x2 - x)/2;
					}
				}
			}
			// create anchor y axis
			if (x == topAnchorYAxis[1]) {
				int targetX = topAnchorYAxis[1];
				for(int y2=(y+20);y2<image.rows;y2++) {
					if (image.at<Vec3b>(y2,targetX) == Vec3b(0,0,0)) {
						bottomAnchorYAxis[0] = y2;
						bottomAnchorYAxis[1] = targetX;
					}
				}
				// draw anchor y axis
				for(int y2=y;y2<bottomAnchorYAxis[0];y2++) {
					image.at<Vec3b>(y2,targetX) = Vec3b(255,0,0);
				}
			}
		}
	}

	// Create displacement map from anchor points
	double yGrayLevel = 0;
	double xGrayLevel = 0;
	double mu = 3.0;
	double muX = 2.0;
	double sigma = 1.1;
	double normalizedY = -1.0;
	double yScaleConvertedGrey = 0.0;
	double yScaleConvertedGreyTemp = 0.0;
	double normalizedX = -30.0;
	double xScaleConvertedGrey = 0.0;
	double pi = M_PI;
	double baseAdjustment = -15.0;//-20;//10;
	double yDouble = 0.0;
	int rotatedX = 0.0, rotatedY = 0.0;
	int rotationAngle = 45.0;

	for(int y=0;y<image.rows;y++)
	{
		//yGrayLevel += 1;//255/image.rows;
		normalizedY += 6.0/255.0;

		// applying gausian
		yGrayLevel = (1.0/(sigma*pow((2.0*pi),0.5)))*(exp(-(pow((normalizedY-mu),2.0)/pow((2*sigma),2.0))));

		yScaleConvertedGrey = yGrayLevel * 255.0/2.0 + baseAdjustment;

		// adjust for top section
		//if (y < (bottomAnchorYAxis[0]-(topAnchorYAxis[0]))) {
		//if (y > 50) {
		yDouble = y;
		yScaleConvertedGrey += (1/((yDouble*.007)+.5))*15;//50;//-= (6.0/255.0)*30;
		//}
		if (y > 49) {
			//baseAdjustment = -20;
		}

		if (y > bottomAnchorYAxis[0]) {
			//yScaleConvertedGrey -= (150 - ((y-244)*16));//4;//8;
			yScaleConvertedGrey -= ((y-244)*1.9);//4;//8;
			//if (yScaleConvertedGrey > 2.001) {yScaleConvertedGrey = 2;}
			if (yScaleConvertedGrey < 0) {yScaleConvertedGrey = 0;}
			//cout<<"y: ";cout<<y;cout<<"  ";cout << yScaleConvertedGrey;cout << "\n";
			//cout << "y:\t";cout<<y;
		}
		yScaleConvertedGreyTemp = yScaleConvertedGrey;

		normalizedX = 0.0;
		for (int x=0;x<image.cols;x++)
		{
			normalizedX += 6.0/255.0;

			xGrayLevel = (1.0/(sigma*pow((2.0*pi),0.5)))*(exp(-(pow((normalizedX-muX),2.0)/pow((2*sigma),2.0))));

			xScaleConvertedGrey = xGrayLevel * 255.0/2.0 + baseAdjustment;

			xScaleConvertedGrey += x*.1;

			//if (x < leftAnchorXAxis[1]) {
			if (image.at<Vec3b>(y,x) == Vec3b(255,255,255)) {
				//if (image.at<Vec3b>(y,x) == Vec3b(0,0,0)) {
				//cout << "leftAnchorXAxis[1]:\t";
				//cout << leftAnchorXAxis[1];cout<<"\n";
				//xScaleConvertedGrey -= (100 - x);
				//xScaleConvertedGrey = -4000;
				//yScaleConvertedGrey = -4000;
				//xScaleConvertedGrey -= (100 - x*15);
				yScaleConvertedGrey = 0;
				//xScaleConvertedGrey = 300;
			}
			else {
				yScaleConvertedGrey = yScaleConvertedGreyTemp;
			}

			if (x < 30) {
				if (xScaleConvertedGrey < 0) {xScaleConvertedGrey = 0;}
				//cout << leftAnchorXAxis[1];//xScaleConvertedGrey;
				//cout << " ";
			}

			image.at<Vec3b>(y,x) = Vec3b(yScaleConvertedGrey+xScaleConvertedGrey,yScaleConvertedGrey+xScaleConvertedGrey,yScaleConvertedGrey+xScaleConvertedGrey);

			// Mirror image verically
			if (x > (image.cols/2)) {
				image.at<Vec3b>(y,x) = image.at<Vec3b>(y,(image.cols-x));
			}
			//cout<<(int)image.at<Vec3b>(y,x).val[0];cout<<"\n";
		}
	}


	/*cout<<"rows";
	cout<<image.rows;
	cout<<"\n";
	cout<<"cols";
	cout<<image.cols;
	cout<<"\n";*/
	//After changing
	//cv::imshow("After",img);
	imwrite( "/home/nmsutton/Documents/Software/OpenGL/Media/GeneralProcessed.bmp", image );

	namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
	imshow( "Display Image", image );

	waitKey(0);



	/*if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        //cv::waitKey(5000);
        return -1;
    }

    //! [window]
    //namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    int cvNamedWindow(const char* name, int flags=CV_WINDOW_AUTOSIZE );
    //! [window]

    //! [imshow]
    //imshow( "Display window", image );                // Show our image inside it.
    void cvShowImage(const char* name, const CvArr* image);
    //! [imshow]

    //! [wait]
    //waitKey(0); // Wait for a keystroke in the window
    //int cvWaitKey(int delay=0 );
    cv::waitKey(5000);
    int cvWaitKey(int delay=5000 );
    //! [wait]*/
	cout << "done";
	return 0;
}
