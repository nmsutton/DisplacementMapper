/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Textures" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 * load texture code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/#Compressed_Textures
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"
using namespace cv;

using namespace std;

/*
 * Preprogrammed optional simulation types include:
 * "gaborFilter"
 * "LGNReceptiveField"
 * "LGNSpaceTimeFixedY"
 */
String simulationToRun = "General";//"gaborFilter";//"LGNReceptiveField";//"LGNSpaceTimeFixedY";
bool simulationFound = false;

float _angle = 0;            //The rotation of the box

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	}
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

char texGroup[200][150];
String textureFile1 = texGroup[0];
String textureFile2 = texGroup[1];
char dispMapGroup[200][150];
String image1 = dispMapGroup[0];
String image2 = dispMapGroup[1];
String startingDispMapImage = image2;
String endingDispMapImage = image1;
Mat startingDispMap;
Mat endingDispMap;
//String anchorImage1 = "../../../OpenGL/Media/anchorImageExtra.bmp";
//String anchorImage2 = "../../../OpenGL/Media/anchorImageExtra.bmp";
String anchorImage1 = "/home/nmsutton/Documents/Software/OpenGL/Media/input/dispMaps/idp01.bmp";
String anchorImage2 = "/home/nmsutton/Documents/Software/OpenGL/Media/input/dispMaps/idp02.bmp";
String startingDispMapAnchorImage = anchorImage2;
String endingDispMapAnchorImage = anchorImage1;
const int numberOfAnchors = 2;
Mat startingDispMapAnchor;
Mat endingDispMapAnchor;
double timeInMs = 0.0;
double dispMapChangeCounter = 0.0;
double dispMapFileCounter = 0.0;
double texFileCounter = 0.0;
double dispMapChangeDelay = 5;//15;//15;//5.0;//5;
double numberOfDispMaps = 6.0;//5;//6;
double numberOfTexs = 28.0;

const int incrementValue = 1;

// *2 is due to 2 rectangle verticies for each x and y axis used for the later Z level mapping.
double verticiesInRectangle = 2;
const double sizeOfMesh = 40;//35;//10;//6;//50;
int scalingF = 2;
const double expandMeshSize = 2.0;//2.5;
double maxYSize = sizeOfMesh*scalingF;
double maxXSize = (sizeOfMesh*scalingF);
int incrementValue2 = 1;
double sizeOfMesh2 = sizeOfMesh*2;
double texYScaling = 1*.9;
double texXScaling = 0.75*.9;
int x = 0, y = 0;
float initalZ = 40.0f;
double depthScalingFactor = 0.75;//1.4;//.7;//.025;//.3;//0.1;
const int xMaxAmount = ceil(sizeOfMesh*(1/incrementValue))*2, yMaxAmount = ceil(sizeOfMesh*(1/incrementValue))*2;
double startingVerZLevels[xMaxAmount][yMaxAmount] = {0};
double endingVerZLevels[xMaxAmount][yMaxAmount] = {0};
double animationDelay = 50.0;
double transitionTime = 200.0;//400.0;//200.0;
struct vertsAndTextures { double ULVerInst[3]; double URVerInst[3]; double BLVerInst[3]; double BRVerInst[3];
double ULTexInst[2]; double URTexInst[2]; double BLTexInst[2]; double BRTexInst[2];};
vertsAndTextures vAT3;

double startingDispMapAnchorPoint[numberOfAnchors][2] = {0};
double endingDispMapAnchorPoint[numberOfAnchors][2] = {0};
double imageYPixels = 512;//image.rows;
double imageXPixels = 512;//image.cols;
double lockedDistance = 0.0;

float verXIncrement = 1.5f;//0.5f;//1.5f;
float verYIncrement = 1.5f;//2.0f;//0.5f;//2.0f;
float verZIncrement = 1.0f;//3.5f;//0.5f;//3.5f;
float texXIncrement = (1.07*(1.00f/(sizeOfMesh2*expandMeshSize)))/texXScaling;
float texYIncrement = (.85f/sizeOfMesh2)/texYScaling;

float initVerXUL = -2.00f;
float initVerXBR = -2.00f;
float initVerXUR = initVerXUL+verXIncrement;
float initVerXBL = initVerXBR+verXIncrement;
float initTexXUL = 0.90f;//-0.05f;//0.0f;//
float initTexXBR = 0.90f;//-0.05f;//-0.10f;
float initTexXUR = initTexXUL+texXIncrement;
float initTexXBL = initTexXBR+texXIncrement;
float initTexYBR = 0.9f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYBR2 = 0.9f;//0.9;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYUL = initTexYBR-texYIncrement;
float initTexYBL = 0.5f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYBL2 = 0.5f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYUR = initTexYBL-texYIncrement;
float initVerZUL = -4.50f+initalZ;
float initVerZUR = -4.50f+initalZ;//initVerZUL+verZIncrement;
float initVerZBL = -4.50f+initalZ;
float initVerZBR = -4.50f+initalZ;

double borderToCrop = 1;
float texYWeight = 1.0;
float texXWeight = 1.0;
bool changeTex = false;
int animationSpeed;
float translateX = 0.0, translateY = 0.0, translateZ = 0.0;
float rotationX = 0.0, rotationY = 0.0, rotationZ = 0.0;

double weightsBR[yMaxAmount][xMaxAmount] = {1};
double weightsBL[yMaxAmount][xMaxAmount] = {1};
double weightsUL[yMaxAmount][xMaxAmount] = {1};
double weightsUR[yMaxAmount][xMaxAmount] = {1};
double weightsBR2[yMaxAmount][xMaxAmount] = {0};
double weightsBL2[yMaxAmount][xMaxAmount] = {0};
double weightsUL2[yMaxAmount][xMaxAmount] = {0};
double weightsUR2[yMaxAmount][xMaxAmount] = {0};
double weightsZ[yMaxAmount][xMaxAmount] = {0.0};//test_test[yMaxAmount][xMaxAmount] = {1};

// from https://studiofreya.com/cpp/how-to-check-for-nan-inf-ind-in-c/
template<typename T>
bool is_nan( const T &value )
{
	// True if NAN
	return value != value;
}

float mouseX;
float mouseY;
float angle = 0.0f;

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	//dispMapImage = imread(imageName6, CV_LOAD_IMAGE_COLOR);

	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_BGR_EXT,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_BGR_EXT, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture

GLuint loadBMP_custom(const char * imagepath){

	//printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file)							    {printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar(); return 0;}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if ( fread(header, 1, 54, file)!=54 ){
		printf("Not a correct BMP file\n");
		return 0;
	}
	// A BMP files always begins with "BM"
	if ( header[0]!='B' || header[1]!='M' ){
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Make sure this is a 24bpp file
	if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    return 0;}
	if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    return 0;}

	// Read the information about the image
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	// Everything is in memory now, the file wan be closed
	fclose (file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// ... nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data );
	//glGenerateMipmap(GL_TEXTURE_2D);

	// OpenGL has now copied the data. Free our own version
	delete [] data;

	// Return the ID of the texture we just created
	return textureID;
}

void initRendering() {
	//changed
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading

	//texture[(int)timeInMs] = loadBMP(dispMapGroup[(int)timeInMs]);

	//Image* image = loadBMP(dispMapGroup[(int)timeInMs]);
	//delete image;
	//Image* image = loadBMP("idptest.bmp");
	//Image* image = loadBMP(texGroup[(int)texFileCounter]);
	Image* image = loadBMP("vtr.bmp");
	_textureId = loadTexture(image);
	delete image;
}



void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void createMesh(vertsAndTextures vAT) {
	glTexCoord2f(vAT.ULTexInst[0], vAT.ULTexInst[1]);
	glVertex3f(vAT.ULVerInst[0],vAT.ULVerInst[1],vAT.ULVerInst[2]);
	glTexCoord2f(vAT.URTexInst[0], vAT.URTexInst[1]);
	glVertex3f(vAT.URVerInst[0],vAT.URVerInst[1],vAT.URVerInst[2]);
	glTexCoord2f(vAT.BLTexInst[0], vAT.BLTexInst[1]);
	glVertex3f(vAT.BLVerInst[0],vAT.BLVerInst[1],vAT.BLVerInst[2]);
	glTexCoord2f(vAT.BRTexInst[0], vAT.BRTexInst[1]);
	glVertex3f(vAT.BRVerInst[0],vAT.BRVerInst[1],vAT.BRVerInst[2]);
}

void buildDispMap(Mat startingDispMap, string startingOrEndPoint) {
	double verZLevels[yMaxAmount][xMaxAmount] = {0};
	for (int y = 0; y < yMaxAmount; y += 2) {
		for (int x = 0; x < xMaxAmount; x += 2) {
			// imageYPixels is use to translate rectangles in mesh coord to pixels in input image
			double imageToScenePixelDiff = (imageYPixels/(double)sizeOfMesh)*(1/verticiesInRectangle);
			double translatedX = ceil(x * imageToScenePixelDiff); double translatedY = ceil(y * imageToScenePixelDiff);
			double meshVec_0_0_b = startingDispMap.at<Vec3b>((int)translatedY,(int)translatedX).val[0];
			meshVec_0_0_b = meshVec_0_0_b/4;

			if (x < xMaxAmount) {
				verZLevels[y][x] = meshVec_0_0_b;
			}
			if (x > 0) {
				verZLevels[y][x+1] = meshVec_0_0_b;
			}
			if ((y < yMaxAmount) & (x < xMaxAmount)) {
				verZLevels[y+1][x+1] = meshVec_0_0_b;
			}
			if (y > 0) {
				verZLevels[y+1][x] = meshVec_0_0_b;
			}
			if (dispMapFileCounter != 0.0) {
				//startingVerZLevels[x][y] = (startingVerZLevels[y][x]*depthScalingFactor)*weightsBR[y][x]*0.5;
				//copy(endingVerZLevels[0], endingVerZLevels[yMaxAmount], startingVerZLevels[0]);
			}
		}
	}

	//if ((startingOrEndPoint == "start") & (dispMapFileCounter == 0.0)) {
	if ((startingOrEndPoint == "start")) {
		copy(verZLevels[0], verZLevels[yMaxAmount], startingVerZLevels[0]);
	}
	else if (startingOrEndPoint == "end") {
		copy(verZLevels[0], verZLevels[yMaxAmount], endingVerZLevels[0]);
	};
}

void initWeights() {
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsBR[weightY], xMaxAmount, 1.0);};
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsBL[weightY], xMaxAmount, 1.0);};
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsUL[weightY], xMaxAmount, 1.0);};
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsUR[weightY], xMaxAmount, 1.0);};
	for (int weightZ = 0;weightZ < yMaxAmount;weightZ++) {fill_n(weightsZ[weightZ], xMaxAmount, 1.0);};
}

void extractAnchorPoint(Mat anchorPointImage, String anchorPointPosition) {
	//cout<<"searching";cout<<anchorPointImage;cout<<"\n";
	// Find anchor points.  Search for pixels that are red B,G,R for OpenGL (1,1,255)
	for(int y=0;y<anchorPointImage.rows;y++)
	{
		for (int x=0;x<anchorPointImage.cols;x++)
		{
			//if ((anchorPointImage.at<Vec3b>(y,x) != Vec3b(0,0,0)) & (anchorFound == false)) {
			int blueLevel = anchorPointImage.at<Vec3b>(y,x).val[0];
			int greenLevel = anchorPointImage.at<Vec3b>(y,x).val[1];
			int redLevel = anchorPointImage.at<Vec3b>(y,x).val[2];
			//cout<<blueLevel;cout<<"|";cout<<greenLevel;cout<<"|";cout<<redLevel;cout<<" ";
			//cout<<blueLevel;cout<<greenLevel;cout<<redLevel;cout<<" ";
			//cout<<redLevel;
			if ((blueLevel <= 50) & (greenLevel <= 50) & (redLevel >= 200)) {
				if (anchorPointPosition=="start") {
					startingDispMapAnchorPoint[0][0]=y;
					startingDispMapAnchorPoint[0][1]=x;
					//cout<<"\n\nstart anchor found\t";cout<<"\n";//cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
				}
				else if (anchorPointPosition=="end") {
					endingDispMapAnchorPoint[0][0]=y;
					endingDispMapAnchorPoint[0][1]=x;
					//cout<<"\n\nend anchor found\t";cout<<"\n";//cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
				}
			}
			if ((blueLevel >= 200) & (greenLevel <= 50) & (redLevel <= 50)  & (numberOfAnchors > 1)) {
				if (anchorPointPosition=="start") {
					startingDispMapAnchorPoint[1][0]=y;
					startingDispMapAnchorPoint[1][1]=x;
					//cout<<"\n\nstart anchor 2 found\t";cout<<"\n";//cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
				}
				else if (anchorPointPosition=="end") {
					endingDispMapAnchorPoint[1][0]=y;
					endingDispMapAnchorPoint[1][1]=x;
					//cout<<"\n\nend anchor 2 found\t";cout<<"\n";//cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
				}
			}
		}
		//cout<<"\n";
	}
	//exit(0);
}

void findAnchorPoints() {
	//cout<<startingDispMapAnchorImage;cout<<"\n";
	startingDispMapAnchor = imread(startingDispMapAnchorImage, CV_LOAD_IMAGE_COLOR);
	endingDispMapAnchor = imread(endingDispMapAnchorImage, CV_LOAD_IMAGE_COLOR);

	extractAnchorPoint(startingDispMapAnchor, "start");
	extractAnchorPoint(endingDispMapAnchor, "end");
}

double xYChangeToAngle(double endY, double startY, double endX, double startX) {
	/*
	 * references:
	 * http://www.dummies.com/how-to/content/how-to-find-the-angle-and-magnitude-of-a-vector.html
	 * http://www.gamedev.net/topic/303625-c-function-for-tan-1/
	 * http://www.cplusplus.com/reference/cmath/atan/
	 */

	double angleParam, result;
	angleParam = ((endY-startY)/(endX-startX));
	result = atan (angleParam) * 180 / M_PI;
	return result;
}

double euclideanDistance(double x1, double x2, double y1, double y2) {
	return sqrt(pow((y2-y1),2)+pow((x2-x1),2));
}

double wobble() {
	double weight = 0.0;
	for (y = 0; y < (maxYSize); y += incrementValue2) {
		for (x = 0; x < maxXSize; x += incrementValue2) {
			weightsZ[y][x] = weightsZ[y][x] + 1.1;
		}
	}

	return weight;
}

void applyDispMap2(int x, int y) {
	/*
		Translate a z movement into the corresponding movement of 4 edge vertices in a
		square in the mesh.

		dispMapChangeCounter = time point along transition from startZ to endZ.

		weight = amount of adjustment to apply
	 */

	// NOTE: weightsZ dummy variable for now

	//dispMapChangeCounter
	// NOTE: check if this ever reaches 1.0 or it always resets before then.
	// Also, animation is fine if it never reaches 1.0?
	double amountTransitioned = (dispMapChangeCounter/dispMapChangeDelay);

	// NOTE: reuse of x,y global variable names, mabie make them non-global
	if (x < (maxXSize-borderToCrop)) {
		vAT3.BRVerInst[2] = (startingVerZLevels[y][x]*amountTransitioned) +
				(endingVerZLevels[y][x]*(1-amountTransitioned)) *
				depthScalingFactor * weightsZ[y][x];
	}
	if ((x > 0) & (x < (maxXSize-borderToCrop))) {
		vAT3.BLVerInst[2] = (startingVerZLevels[y][x+1]*amountTransitioned) +
				(endingVerZLevels[y][x+1]*(1-amountTransitioned)) *
				depthScalingFactor * weightsZ[y][x+1];
	}
	if (y > 0 & y < maxYSize-borderToCrop) {
		weightsUL[y+1][x] = 0;
		vAT3.ULVerInst[2] = (startingVerZLevels[y+1][x]*amountTransitioned) +
				(endingVerZLevels[y+1][x]*(1-amountTransitioned)) *
				depthScalingFactor * weightsZ[y+1][x];
	}
	if ((y < maxYSize-borderToCrop) & (x < (maxXSize-borderToCrop))) {
		weightsUR[y+1][x+1] = 0;
		vAT3.URVerInst[2] = (startingVerZLevels[y+1][x+1]*amountTransitioned) +
				(endingVerZLevels[y+1][x+1]*(1-amountTransitioned)) *
				depthScalingFactor * weightsZ[y+1][x+1];
	}
}

void createMeshOfRect() {
	vAT3.ULVerInst[0] = -2.5f;
	vAT3.ULVerInst[1] = -0.5f;
	vAT3.ULVerInst[2] = -4.5f;
	vAT3.ULTexInst[0] = initTexXUL;
	vAT3.ULTexInst[1] = initTexYUL;

	vAT3.URVerInst[0] = -1.0f;
	vAT3.URVerInst[1] = -0.5f;
	vAT3.URVerInst[2] = -4.5f;//-1.5f;
	vAT3.URTexInst[0] = initTexXUR;
	vAT3.URTexInst[1] = initTexYUR;

	vAT3.BLVerInst[0] = -1.0f;
	vAT3.BLVerInst[1] = 1.5f;
	vAT3.BLVerInst[2] = -4.5f;
	vAT3.BLTexInst[0] = initTexXBL;
	vAT3.BLTexInst[1] = initTexYBL;

	vAT3.BRVerInst[0] = -2.5f;
	vAT3.BRVerInst[1] = 1.5f;
	vAT3.BRVerInst[2] = -4.5f;
	vAT3.BRTexInst[0] = initTexXBR;
	vAT3.BRTexInst[1] = initTexYBR;

	wobble();

	for (y = 0; y < (maxYSize); y += incrementValue2) {
		//createMesh(vAT3);
		// Reinitialze X dimension before the x value loop
		vAT3.ULVerInst[0] = initVerXUL;
		vAT3.ULTexInst[0] = initTexXUL;
		vAT3.URVerInst[0] = initVerXUR;
		vAT3.URTexInst[0] = initTexXUR;
		vAT3.BLVerInst[0] = initVerXBL;
		vAT3.BLTexInst[0] = initTexXBL;
		vAT3.BRVerInst[0] = initVerXBR;
		vAT3.BRTexInst[0] = initTexXBR;

		// For y dimension iteration update the y values
		if (y < maxYSize/2) {
			vAT3.ULVerInst[1] -= verYIncrement;
			vAT3.URVerInst[1] -= verYIncrement;
			vAT3.BLVerInst[1] -= verYIncrement;
			vAT3.BRVerInst[1] -= verYIncrement;

			vAT3.ULTexInst[1] -= texYIncrement;
			vAT3.URTexInst[1] -= texYIncrement;
			vAT3.BLTexInst[1] -= texYIncrement;
			vAT3.BRTexInst[1] -= texYIncrement;
		}
		else if (y >= maxYSize/2) {
			vAT3.ULVerInst[1] -= verYIncrement;
			vAT3.URVerInst[1] -= verYIncrement;
			vAT3.BLVerInst[1] -= verYIncrement;
			vAT3.BRVerInst[1] -= verYIncrement;

			vAT3.ULTexInst[1] -= texYIncrement;
			vAT3.URTexInst[1] -= texYIncrement;
			vAT3.BLTexInst[1] -= texYIncrement;
			vAT3.BRTexInst[1] -= texYIncrement;
		}


		for (x = 0; x < maxXSize; x += incrementValue2) {
			if ((x < maxYSize/2) | (x < (maxYSize/2+(maxXSize-maxYSize)) & x > (maxXSize-maxYSize))) {
				vAT3.ULVerInst[0] += verXIncrement;
				vAT3.URVerInst[0] += verXIncrement;
				vAT3.BLVerInst[0] += verXIncrement;
				vAT3.BRVerInst[0] += verXIncrement;

				vAT3.ULTexInst[0] += texXIncrement;
				vAT3.URTexInst[0] += texXIncrement;
				vAT3.BLTexInst[0] += texXIncrement;
				vAT3.BRTexInst[0] += texXIncrement;
			}
			else if ((x >= maxYSize/2 & x < maxYSize) | (x > (maxYSize/2+(maxXSize-maxYSize)) & x < (maxXSize))) {
				vAT3.ULVerInst[0] += verXIncrement;
				vAT3.URVerInst[0] += verXIncrement;
				vAT3.BLVerInst[0] += verXIncrement;
				vAT3.BRVerInst[0] += verXIncrement;

				vAT3.ULTexInst[0] += texXIncrement;
				vAT3.URTexInst[0] += texXIncrement;
				vAT3.BLTexInst[0] += texXIncrement;
				vAT3.BRTexInst[0] += texXIncrement;
			}
			else if (x > (maxYSize) & x < (maxXSize-maxYSize)) {
				vAT3.ULVerInst[0] += verXIncrement;
				vAT3.URVerInst[0] += verXIncrement;
				vAT3.BLVerInst[0] += verXIncrement;
				vAT3.BRVerInst[0] += verXIncrement;

				vAT3.ULTexInst[0] += texXIncrement;
				vAT3.URTexInst[0] += texXIncrement;
				vAT3.BLTexInst[0] += texXIncrement;
				vAT3.BRTexInst[0] += texXIncrement;
			}

			//applyDispMap(maxXSize, maxYSize, borderToCrop);
			applyDispMap2(x, y);

			createMesh(vAT3);
		}
	}
	weightsBR2[yMaxAmount][xMaxAmount] = {0};
	weightsBL2[yMaxAmount][xMaxAmount] = {0};
	weightsUL2[yMaxAmount][xMaxAmount] = {0};
	weightsUR2[yMaxAmount][xMaxAmount] = {0};
	// Reset Z levels
	for (int weightZ = 0;weightZ < yMaxAmount;weightZ++) {fill_n(weightsZ[weightZ], xMaxAmount, 1.0);};
}

const float BOX_SIZE = 7.0f;
void drawScene() {
	startingDispMap = imread(startingDispMapImage, CV_LOAD_IMAGE_COLOR);
	endingDispMap = imread(endingDispMapImage, CV_LOAD_IMAGE_COLOR);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// camera position mapper
	glTranslatef(translateX, translateY, translateZ);

	//GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat ambientLight[] = {1000.2f, 1000.2f, 1000.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = {200.7f, 200.7f, 200.7f, 1.0f};
	GLfloat directedLightPos[] = {-210.0f, 215.0f, 220.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
	//GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	//GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	//GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glRotatef(-_angle, rotationX, rotationY, rotationZ);

	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, _textureId)
	/*Image* image = loadBMP("idptest.bmp");
	_textureId = loadTexture(image);
	delete image;
	glBindTexture(GL_TEXTURE_2D, "vtr.bmp");*/
	//numberOfTexs
	//glBindTexture( GL_TEXTURE_2D, LoadTexture2(texGroup[(int)timeInMs], 512, 512) );
	//glBindTexture( GL_TEXTURE_2D, LoadTexture2(texGroup[(int)texFileCounter], 512, 512) );
	//glBindTexture( GL_TEXTURE_2D, LoadTexture2("vtr.bmp", 512, 512) );
	//glBindTexture( GL_TEXTURE_2D, LoadTexture2("MyRawImage.raw", 512, 512) );
	//glBindTexture( GL_TEXTURE_2D, loadTexture(texGroup[(int)texFileCounter], 512, 512) );

	//GLuint Texture = loadDDS(texGroup[(int)texFileCounter]);
	//GLuint Texture = loadDDS("newVtr.dds");
	//GLuint Texture = loadBMP_custom("vtr.bmp");
	//glBindTexture(GL_TEXTURE_2D, Texture);
	//GLuint NormalTexture = loadBMP_custom("vtr.bmp");
	glBindTexture(GL_TEXTURE_2D, loadBMP_custom(texGroup[(int)texFileCounter]));

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor3f(1.0f, 1.0f, 1.0f);
	//glColor3f(1.0f, 0.45, 0.0f);
	glBegin(GL_QUADS);

	glNormal3f(1.0f, 1.0f, 1.0f);

	// Build displacement map.
	buildDispMap(startingDispMap, "start");
	buildDispMap(endingDispMap, "end");

	// Update Anchor points
	findAnchorPoints();

	// Generate mesh with disp mapping
	createMeshOfRect();

	glEnd();

	glutSwapBuffers();
}

double dispMapChangeSine = 1.0;
//Called every 25 milliseconds
void update(int value) {
	timeInMs += 1.0;
	texFileCounter += (1.0*dispMapChangeSine)*(numberOfTexs/(numberOfDispMaps*dispMapChangeDelay));
	dispMapChangeCounter += 1.0;
	if (timeInMs == transitionTime) {timeInMs = 0;}

	if (dispMapChangeCounter == dispMapChangeDelay) {
		//copy(endingVerZLevels[0], endingVerZLevels[yMaxAmount], startingVerZLevels[0]);
		dispMapFileCounter += 1.0*dispMapChangeSine;

		startingDispMapImage = dispMapGroup[(int)dispMapFileCounter];
		if ((dispMapChangeSine==1.0)&(dispMapFileCounter+1) < numberOfDispMaps) {
			endingDispMapImage = dispMapGroup[(int)dispMapFileCounter+1];
		}
		else if ((dispMapChangeSine==-1.0)&(dispMapFileCounter-1) > -1.0) {
			endingDispMapImage = dispMapGroup[(int)dispMapFileCounter-1];
		}
		else {
			if (dispMapChangeSine==1.0) {
				dispMapFileCounter = numberOfDispMaps-1;
				texFileCounter = numberOfTexs - 1;
				endingDispMapImage = dispMapGroup[(int)numberOfDispMaps-2];
				dispMapChangeSine = dispMapChangeSine * -1;
			}
			else if (dispMapChangeSine==-1.0) {
				dispMapFileCounter = 0;
				texFileCounter = 0;
				endingDispMapImage = dispMapGroup[1];
				dispMapChangeSine = dispMapChangeSine * -1;
			}
		}
		startingDispMapAnchorImage = startingDispMapImage;
		endingDispMapAnchorImage = endingDispMapImage;
		dispMapChangeCounter = 0;}

	changeTex = true;
	glutPostRedisplay();
	glutTimerFunc(animationSpeed, update, 0);
}

void loadSimParameters(String simulationToRun) {
	// Parameters for simulations
	if (simulationToRun == "General") {
		stringstream ss;
		// Load disp maps
		for (int i = 0; i < numberOfDispMaps; i++) {
			ss.str( std::string() );
			ss.clear();
			ss << "../../../../OpenGL/Media/input/dispMaps/idp0";//"../../../OpenGL/Media/input/backup/idp0";
			ss << i;
			ss << ".bmp";
			std::string s = ss.str();
			const char* p = s.c_str();
			strcpy(dispMapGroup[i], p);
		}
		// Load textures
		for (int i = 0; i < numberOfTexs; i++) {
			ss.str( std::string() );
			ss.clear();
			//ss << "../../../OpenGL/Media/input/textures/idp0";
			ss << "../../../../OpenGL/Media/input/backup6/idp0";
			ss << i;
			ss << ".bmp";
			std::string s = ss.str();
			const char* p = s.c_str();
			strcpy(texGroup[i], p);
		}

		image1 = dispMapGroup[0];
		image2 = dispMapGroup[1];
		startingDispMapImage = image2;
		endingDispMapImage = image1;

		translateX = -60.0f; translateY = 61.0f; translateZ = -180.0f;

		rotationX = -100.20f; rotationY = 201.0f; rotationZ = 45.0f;

		_angle = 30.0f;//30.00f;//45.330f;//0.0f;

		depthScalingFactor = 0.75;//1.4;//.7;//.025;//.3;//0.1;

		animationDelay = 100.0;
		transitionTime = 100.0;//200.0;//400.0;//200.0;

		texXIncrement = (1.60*(1.00f/(sizeOfMesh2*expandMeshSize)))/texXScaling;
		texYIncrement = (0.73f/sizeOfMesh2)/texYScaling;

		double xShift = 0.84f;
		initTexXUL = xShift;//-0.05f;//0.0f;//
		initTexXBR = xShift;//-0.05f;//-0.10f;
		initTexXUR = initTexXUL+texXIncrement;
		initTexXBL = initTexXBR+texXIncrement;
		double yShift = 0.68f;
		initTexYBR = yShift;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYBR2 = yShift;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYUL = initTexYBR-texYIncrement;
		initTexYBL = yShift;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYBL2 = yShift;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYUR = initTexYBL-texYIncrement;

		animationSpeed = 100;

		simulationFound = true;
	}
	else {
		cerr<<"\n--Error--\nIncorrect simulation type specified\n--Error--\n\n";
	}
}

void mouse(int button, int state, int x, int y)
{
	/*
	 * Reference http://www.glprogramming.com/red/chapter01.html
	 */
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            //glutIdleFunc(spinDisplay);
        	 cout<<"left\n";
         break;
      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN)
            //glutIdleFunc(NULL);
        	 cout<<"middle\n";
         break;
      default:
         break;
   }
}

void mouseMove(int x, int y)
{
    mouseX = -1.0 + 2.0 * x / 320 ;
    mouseY = 1.0 - 2.0 * y / 320 ;

    //angle = 90 + atan2(pos.y-mouseY, pos.x-mouseX) * 180 / 3.1415926;

    std::cout << mouseX << ", " << mouseY << std::endl;
    std::cout << x << ", " << y << std::endl;
    std::cout << angle << std::endl;
}

int main(int argc, char** argv) {
	/*
	 * Creation of 3d graphics based on displacement maps using 2d disp maps.
	 *
	 * references:
	 * http://stackoverflow.com/questions/8765574/how-to-put-stringstream-contents-into-char-type-instead-string-type
	 * http://stackoverflow.com/questions/2848087/how-to-clear-stringstream
	 */

	cout<<"\n\nImages used for the simulation need to be in a folder one level below this program in the file system.  \n";
	cout<<"The folder is named \"OpenGL/Media/\".  See image variable names to set or change where images are located.\n";
	cout<<"Images used come from the image preprocessor program which generates 2d dispacement maps according to the\n";
	cout<<"experiment being simulated.\n\n";

	cout<<"Please use an available simulation type:\n\"gaborFilter\"\n\"LGNReceptiveField\"\n\"LGNSpaceTimeFixedY\"\n\n";

	loadSimParameters(simulationToRun);

	if (simulationFound) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(400, 400);

		glutCreateWindow("Textures - videotutorialsrock.com");
		initWeights();
		//findAnchorPoints();
		glutMouseFunc(mouse);

		glutMotionFunc(mouseMove);

		initRendering();

		glutDisplayFunc(drawScene);
		glutKeyboardFunc(handleKeypress);
		glutReshapeFunc(handleResize);
		glutTimerFunc(animationSpeed, update, 0);

		glutMainLoop();
	};

	cout << "done";

	return 0;
}
