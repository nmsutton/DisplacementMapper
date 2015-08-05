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

/* Copyright 2015 Nate Sutton
 * 
 * 3d graphics generation from 2d displacement map images created in the 
 * image preprocessor code.  Some content used from the 
 * File for "Textures" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
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
String simulationToRun = "gaborFilter";//"gaborFilter";//"LGNReceptiveField";//"LGNSpaceTimeFixedY";
bool simulationFound = false;

float _angle = 0;            //The rotation of the box

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	}
}

/*
  Parameters for modeling are given such as initialization of texture image variables,
  surface size for 3d displacement mapping, texture scaling, 
  depth of z dimention in 3d, speed of animation, offset of texture placement
*/
char texGroup[200][150]; // texture file name group
String image1 = texGroup[0];  
String image2 = texGroup[1];
String startingDispMapImage = image2;  // starting point image of transition of displacement map
String endingDispMapImage = image1;  // end point image of transition of displacement map
Mat startingDispMap;
Mat endingDispMap;
double timeInMs = 0;
const int incrementValue = 1;
double verticiesInRectangle = 2; // *2 is due to 2 rectangle verticies for each x and y axis used for the later Z level mapping.
const double sizeOfMesh = 40; // Squares in the 3d surface (mesh)
int scalingF = 2;
const double expandMeshSize = 2.0;
double maxYSize = sizeOfMesh*scalingF;
double maxXSize = (sizeOfMesh*scalingF);
int incrementValue2 = 1;
double sizeOfMesh2 = sizeOfMesh*2;
double texYScaling = 1*.9; // scaling of the Y dimention of texture images
double texXScaling = 0.75*.9; // scaling of the X dimention of texture images
int x = 0, y = 0;
float initalZ = 40.0f;
double depthScalingFactor = 0.75; // scaling of the amount of 3d depth
const int xMaxAmount = ceil(sizeOfMesh*(1/incrementValue))*2, yMaxAmount = ceil(sizeOfMesh*(1/incrementValue))*2;
double startingVerZLevels[xMaxAmount][yMaxAmount] = {0};
double endingVerZLevels[xMaxAmount][yMaxAmount] = {0};
double animationDelay = 50.0;
double transitionTime = 200.0;
struct vertsAndTextures { double ULVerInst[3]; double URVerInst[3]; double BLVerInst[3]; double BRVerInst[3];
double ULTexInst[2]; double URTexInst[2]; double BLTexInst[2]; double BRTexInst[2];};
vertsAndTextures vAT3;

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
float initTexXUL = 0.10f;//-0.05f;//0.0f;//
float initTexXBR = 0.10f;//-0.05f;//-0.10f;
float initTexXUR = initTexXUL+texXIncrement;
float initTexXBL = initTexXBR+texXIncrement;
float initTexYBR = 1.0f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYBR2 = 1.0f;//0.9;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYUL = initTexYBR-texYIncrement;
float initTexYBL = 1.0f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYBL2 = 1.0f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYUR = initTexYBL-texYIncrement;
float initVerZUL = -4.50f+initalZ;
float initVerZUR = -4.50f+initalZ;//initVerZUL+verZIncrement;
float initVerZBL = -4.50f+initalZ;
float initVerZBR = -4.50f+initalZ;

float texYWeight = 1.0;
float texXWeight = 1.0;
bool changeTex = false;
int animationSpeed;
float translateX = 0.0, translateY = 0.0, translateZ = 0.0;
float rotationX = 0.0, rotationY = 0.0, rotationZ = 0.0;

// from https://studiofreya.com/cpp/how-to-check-for-nan-inf-ind-in-c/
template<typename T>
bool is_nan( const T &value )
{
	// True if NAN
	return value != value;
}

//texture[200] texGroup2;
Image* texture[200];

GLuint LoadTexture2( const char * filename, int width, int height )
{
	GLuint texture;
	unsigned char * data;
	FILE * file;

	//The following code will read in our RAW file
	file = fopen( filename, "rb" );
	if ( file == NULL ) return 0;
	data = (unsigned char *)malloc( width * height * 3 );
	fread( data, width * height * 3, 1, file );
	fclose( file );

	glGenTextures( 1, &texture ); //generate the texture with the loaded data
	glBindTexture( GL_TEXTURE_2D, texture ); //bind the textureto it’s array
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters

	//here we are setting what textures to use and when. The MIN  filter is which quality to show
	//when the texture is near the view, and the MAG filter is which quality to show when the texture
	//is far from the view.

	//The qualities are (in order from worst to best)
	//GL_NEAREST
	//GL_LINEAR
	//GL_LINEAR_MIPMAP_NEAREST
	//GL_LINEAR_MIPMAP_LINEAR

	//And if you go and use extensions, you can use Anisotropic  filtering textures which are of an
	//even better quality, but this will do for now.
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR );

	//Here we are setting the parameter to repeat the texture instead of clamping the texture
	//to the edge of our shape.
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	//Generate the texture with mipmaps
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data ); //free the texture
	return texture; //return whether it was successfull
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading

	texture[(int)timeInMs] = loadBMP(texGroup[(int)timeInMs]);

	Image* image = loadBMP(texGroup[(int)timeInMs]);
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
		}
	}

	if (startingOrEndPoint == "start") {
		copy(verZLevels[0], verZLevels[yMaxAmount], startingVerZLevels[0]);
	}
	else if (startingOrEndPoint == "end") {
		copy(verZLevels[0], verZLevels[yMaxAmount], endingVerZLevels[0]);
	};
}

double weightsBR[yMaxAmount][xMaxAmount] = {1};
double weightsBL[yMaxAmount][xMaxAmount] = {1};
double weightsUL[yMaxAmount][xMaxAmount] = {1};
double weightsUR[yMaxAmount][xMaxAmount] = {1};

void initWeights() {
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsBR[weightY], xMaxAmount, 1.0);};
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsBL[weightY], xMaxAmount, 1.0);};
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsUL[weightY], xMaxAmount, 1.0);};
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsUR[weightY], xMaxAmount, 1.0);};
}

void calculateWeightChange(String verPositionForWeights, bool anchorForTexUpdate, double startY, double startX, double startZ, double endY, double endX, double endZ) {
	/* 
	Z dimention (3d depth) is calculated here and saved in weight 
	groups.  Weights are used as z-dimention values.  
		
	Use self organizing maps to apply disp map movement transition

	from: https://en.wikipedia.org/wiki/Self-organizing_map

	s is the current iteration
	L is the iteration limit
	t is the index of the target input data vector in the input data set \mathbf{D}
	D(t) is a target input data vector
	v is the index of the node in the map
	W_v is the current weight vector of node v
	u is the index of the best matching unit (BMU) in the map
	Θ(u, v, s) is a restraint due to distance from BMU, usually called the neighborhood function, and
	α (s) is a learning restraint due to iteration progress.

	Wv(s + 1) = Wv(s) + Θ(u, v, s) α(s)(D(t) - Wv(s))

	The Self organizing map is applied below in the newWeight variable
	
	*/

	// Current point in most direct motion path using anchor points
	double yDirPath = (startY*(1.0-((1.0/animationDelay)*timeInMs)))+(endY*((1.0/animationDelay)*timeInMs));
	double xDirPath = (startX*(1.0-((1.0/animationDelay)*timeInMs)))+(endX*((1.0/animationDelay)*timeInMs));
	// Euclidean distance from most direct path of motion from starting anchor point to ending anchor point
	double distance = sqrt(pow(yDirPath-(imageYPixels*((double)y/(double)yMaxAmount)),2)+pow(xDirPath-(imageXPixels*((double)x/(double)xMaxAmount)),2));
	yDirPath = endY;
	xDirPath = startX;
	distance = sqrt(pow(yDirPath-(imageYPixels*((double)y/(double)yMaxAmount)),2)+pow(xDirPath-(imageXPixels*((double)x/(double)xMaxAmount)),2));
	if (distance == 0) {distance = .00001;}
	double furthestDistPossible = sqrt(pow(imageYPixels,2)+pow(imageXPixels,2));
	// normalize distance with furthest possible in image giving it a 0-1 range
	double normalizedDistance = (distance/furthestDistPossible);
	double scalingFactor = 0.9;
	double scaledDistance = (1-(normalizedDistance*scalingFactor));
	scaledDistance = (1-(pow(normalizedDistance,.8)));

	double distanceCost = (1-.1);
	double distanceRestraint = scaledDistance*distanceCost;//1.0*distanceCost;//(1-normalizedDistance)*distanceCost;//2.8;//
	double learningRestraint = 1.0;

	double amountTransitioned = ((1.0/animationDelay)*timeInMs)*distanceRestraint;

	// Difference with starting and ending weights
	double startDispMapWeights = 1.0;
	double endDispMapWeights = (endZ*depthScalingFactor)/(startZ*depthScalingFactor);
	// Position is based on transistion degree including distance restraint limit
	double newWeight = ((distanceRestraint*learningRestraint*startDispMapWeights)*(1-amountTransitioned)) +
			((distanceRestraint*learningRestraint*endDispMapWeights)*(amountTransitioned));
	// normalize tex map
	double texTransDelay = timeInMs*(1/(animationDelay*1.5));
	//if (changeTex==false) {texTransDelay = 1-texTransDelay;}
	if (texTransDelay > 1) {texTransDelay = 1;}
	//changeTex
	double newTexY;

	if (is_nan(newWeight)==true) {newWeight = 1.0;}
	if (verPositionForWeights == "BR") {
		weightsBR[y][x] += newWeight;
	}
	else if (verPositionForWeights == "BL") {
		weightsBL[y][x+1] += newWeight;
	}
	else if (verPositionForWeights == "UL") {
		weightsUL[y+1][x] += newWeight;
	}
	else if (verPositionForWeights == "UR") {
		weightsUR[y+1][x+1] += newWeight;
	}
}

void applyDispMap(double maxXSize, double maxYSize, double borderToCrop) {
	/*
	* Each vertex in the squares of the 3d surface are positioned here
	*/

	double range = 20;
	if (x < (maxXSize-borderToCrop)) {

		weightsBR[y][x] = 0;
		for (int anchorIndex = 0;anchorIndex < numberOfAnchors; anchorIndex++) {
			calculateWeightChange("BR", true, startingDispMapAnchorPoint[anchorIndex][0], startingDispMapAnchorPoint[anchorIndex][1],
					startingVerZLevels[y][x], endingDispMapAnchorPoint[anchorIndex][0], endingDispMapAnchorPoint[anchorIndex][1], endingVerZLevels[y][x]);
		}
		vAT3.BRVerInst[2] = (startingVerZLevels[y][x]*depthScalingFactor)*weightsBR[y][x];
	}
	if ((x > 0) & (x < (maxXSize-borderToCrop))) {
		weightsBL[y][x+1] = 0;
		for (int anchorIndex = 0;anchorIndex < numberOfAnchors; anchorIndex++) {
			calculateWeightChange("BL", true, startingDispMapAnchorPoint[anchorIndex][0], startingDispMapAnchorPoint[anchorIndex][1],
					startingVerZLevels[y][x+1], endingDispMapAnchorPoint[anchorIndex][0], endingDispMapAnchorPoint[anchorIndex][1], endingVerZLevels[y][x+1]);
		}
		vAT3.BLVerInst[2] = (startingVerZLevels[y][x+1]*depthScalingFactor)*weightsBL[y][x+1];
	}
	if (y > 0 & y < maxYSize-borderToCrop) {
		weightsUL[y+1][x] = 0;
		for (int anchorIndex = 0;anchorIndex < numberOfAnchors; anchorIndex++) {
			calculateWeightChange("UL", true, startingDispMapAnchorPoint[anchorIndex][0], startingDispMapAnchorPoint[anchorIndex][1],
					startingVerZLevels[y+1][x], endingDispMapAnchorPoint[anchorIndex][0], endingDispMapAnchorPoint[anchorIndex][1], endingVerZLevels[y+1][x]);
		}
		vAT3.ULVerInst[2] = (startingVerZLevels[y+1][x]*depthScalingFactor)*weightsUL[y+1][x];
	}
	if ((y < maxYSize-borderToCrop) & (x < (maxXSize-borderToCrop))) {
		weightsUR[y+1][x+1] = 0;
		for (int anchorIndex = 0;anchorIndex < numberOfAnchors; anchorIndex++) {
			calculateWeightChange("UR", true, startingDispMapAnchorPoint[anchorIndex][0], startingDispMapAnchorPoint[anchorIndex][1],
					startingVerZLevels[y+1][x+1], endingDispMapAnchorPoint[anchorIndex][0], endingDispMapAnchorPoint[anchorIndex][1], endingVerZLevels[y+1][x+1]);
		}
		vAT3.URVerInst[2] = (startingVerZLevels[y+1][x+1]*depthScalingFactor)*weightsUR[y+1][x+1];
	}
}

void createMeshOfRect() {
	/*
	*  Squares in the surface used for 3d model representation are positioned and
	*  depth is added to them here.
	*/

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

	for (y = 0; y < (maxYSize); y += incrementValue2) {
		//createMesh(vAT3);
		// Reinitialze X dimension before the x value loop.  First vertices positions than texture of squares
		vAT3.ULVerInst[0] = initVerXUL;
		vAT3.URVerInst[0] = initVerXUR;		
		vAT3.BLVerInst[0] = initVerXBL;i
		vAT3.BRVerInst[0] = initVerXBR;
		vAT3.ULTexInst[0] = initTexXUL;
		vAT3.URTexInst[0] = initTexXUR;
		vAT3.BLTexInst[0] = initTexXBL;
		vAT3.BRTexInst[0] = initTexXBR;

		// For y dimension iteration update the y values
		vAT3.ULVerInst[1] -= verYIncrement;
		vAT3.URVerInst[1] -= verYIncrement;
		vAT3.BLVerInst[1] -= verYIncrement;
		vAT3.BRVerInst[1] -= verYIncrement;

		vAT3.ULTexInst[1] -= texYIncrement;
		vAT3.URTexInst[1] -= texYIncrement;
		vAT3.BLTexInst[1] -= texYIncrement;
		vAT3.BRTexInst[1] -= texYIncrement;


		for (x = 0; x < maxXSize; x += incrementValue2) {
			vAT3.ULVerInst[0] += verXIncrement;
			vAT3.URVerInst[0] += verXIncrement;
			vAT3.BLVerInst[0] += verXIncrement;
			vAT3.BRVerInst[0] += verXIncrement;

			vAT3.ULTexInst[0] += texXIncrement;
			vAT3.URTexInst[0] += texXIncrement;
			vAT3.BLTexInst[0] += texXIncrement;
			vAT3.BRTexInst[0] += texXIncrement;

			double borderToCrop = 1;
			applyDispMap(maxXSize, maxYSize, borderToCrop);

			createMesh(vAT3);
		}
	}
}

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

	glRotatef(-_angle, rotationX, rotationY, rotationZ);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, LoadTexture2(texGroup[(int)timeInMs], 512, 512) );

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	glNormal3f(1.0f, 1.0f, 1.0f);

	// Build displacement map.
	buildDispMap(startingDispMap, "start");
	buildDispMap(endingDispMap, "end");

	// Generate mesh with disp mapping
	createMeshOfRect();

	glEnd();

	glutSwapBuffers();
}

//Called every 25 milliseconds
void update(int value) {
	timeInMs += 1.0;
	if (timeInMs == transitionTime) {timeInMs = 0;}

	startingDispMapImage = texGroup[(int)timeInMs];
	if (timeInMs < (transitionTime-1)) {
		endingDispMapImage = texGroup[(int)timeInMs+1];
	}
	else {
		endingDispMapImage = texGroup[0];
	}

	changeTex = true;
	glutPostRedisplay();
	glutTimerFunc(animationSpeed, update, 0);
}

void loadSimParameters(String simulationToRun) {
	// Parameters for gabor filter and LGN receptive field
	if (simulationToRun == "gaborFilter") {
		stringstream ss;
		for (int i = 0; i < 200; i++) {
			ss.str( std::string() );
			ss.clear();
			ss << "../../../OpenGL/Media/gabor/gaborFilterDispMap_";
			ss << i;
			ss << ".bmp";
			std::string s = ss.str();
			const char* p = s.c_str();
			strcpy(texGroup[i], p);
		}

		image1 = texGroup[0];
		image2 = texGroup[1];
		startingDispMapImage = image2;
		endingDispMapImage = image1;

		translateX = -60.0f; translateY = 15.0f; translateZ = -180.0f;

		rotationX = -400.00f; rotationY = 50.0f; rotationZ = 20.0f;

		_angle = -70.330f;

		depthScalingFactor = 0.75;//1.4;//.7;//.025;//.3;//0.1;

		animationDelay = 50.0;
		transitionTime = 200.0;//400.0;//200.0;

		texXIncrement = (1.07*(1.00f/(sizeOfMesh2*expandMeshSize)))/texXScaling;
		texYIncrement = (.85f/sizeOfMesh2)/texYScaling;

		initTexXUL = 0.10f;//-0.05f;//0.0f;//
		initTexXBR = 0.10f;//-0.05f;//-0.10f;
		initTexXUR = initTexXUL+texXIncrement;
		initTexXBL = initTexXBR+texXIncrement;
		initTexYBR = 1.0f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYBR2 = 1.0f;//0.9;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYUL = initTexYBR-texYIncrement;
		initTexYBL = 1.0f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYBL2 = 1.0f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYUR = initTexYBL-texYIncrement;

		animationSpeed = 100;

		simulationFound = true;
	}
	else if (simulationToRun == "LGNReceptiveField") {
		stringstream ss;
		for (int i = 0; i < 200; i++) {
			ss.str( std::string() );
			ss.clear();
			ss << "../../../OpenGL/Media/diffGaus/plot1/diffGaus_";
			ss << i;
			ss << ".bmp";
			std::string s = ss.str();
			const char* p = s.c_str();
			strcpy(texGroup[i], p);
		}

		image1 = texGroup[0];
		image2 = texGroup[1];
		startingDispMapImage = image2;
		endingDispMapImage = image1;

		translateX = -110.0f; translateY = 15.0f; translateZ = -100.0f;

		rotationX = -200.00f; rotationY = 60.0f; rotationZ = 120.0f;

		_angle = -60.330f;

		double depthScalingFactor = 0.75;//1.4;//.7;//.025;//.3;//0.1;

		double animationDelay = 50.0;
		double transitionTime = 200.0;//400.0;//200.0;

		float texXIncrement = (1.07*(1.00f/(sizeOfMesh2*expandMeshSize)))/texXScaling;
		float texYIncrement = (1.00f/sizeOfMesh2)/texYScaling;

		float initTexXUL = 0.10f;//-0.05f;//0.0f;//
		float initTexXBR = 0.10f;//-0.05f;//-0.10f;
		float initTexXUR = initTexXUL+texXIncrement;
		float initTexXBL = initTexXBR+texXIncrement;
		float initTexYBR = 1.10f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
		float initTexYBR2 = 1.10f;//0.9;//0.64f;//1.0f;//1.10f;0.64f;//
		float initTexYUL = initTexYBR-texYIncrement;
		float initTexYBL = 1.10f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
		float initTexYBL2 = 1.10f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
		float initTexYUR = initTexYBL-texYIncrement;

		animationSpeed = 100;
		simulationFound = true;
	}
	else if (simulationToRun == "LGNSpaceTimeFixedY") {
		for (int i = 0; i < 200; i++) {
			strcpy(texGroup[i], "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp");
		}

		image1 = texGroup[0];
		image2 = texGroup[1];
		startingDispMapImage = image2;
		endingDispMapImage = image1;

		translateX = -60.0f; translateY = -35.0f; translateZ = -100.0f;

		rotationX = -30.00f; rotationY = 30.0f; rotationZ = 100.0f;

		_angle = -84.330f;

		depthScalingFactor = 0.75;//1.4;//.7;//.025;//.3;//0.1;

		animationDelay = 50.0;
		transitionTime = 200.0;//400.0;//200.0;

		texXIncrement = (1.07*(1.00f/(sizeOfMesh2*expandMeshSize)))/texXScaling;
		texYIncrement = (.85f/sizeOfMesh2)/texYScaling;

		initTexXUL = 0.10f;//-0.05f;//0.0f;//
		initTexXBR = 0.10f;//-0.05f;//-0.10f;
		initTexXUR = initTexXUL+texXIncrement;
		initTexXBL = initTexXBR+texXIncrement;
		initTexYBR = 1.0f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYBR2 = 1.0f;//0.9;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYUL = initTexYBR-texYIncrement;
		initTexYBL = 1.0f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYBL2 = 1.0f;//0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
		initTexYUR = initTexYBL-texYIncrement;

		animationSpeed = 100;

		simulationFound = true;
	}
	else {
		cerr<<"\n--Error--\nIncorrect simulation type specified\n--Error--\n\n";
	}
}

int main(int argc, char** argv) {
	/*
	 * Creation of 3d graphics based on displacement maps using 2d disp maps.  If a known simulation
	 * is found than a window is generated.  Methods are called to render the graphics including resizing.
	 * The animation is repeated including updating 3d surface content.
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

		glutCreateWindow("Visual neuron receptor field simulation"); // Initialize window
		initWeights(); // Calculate depth (z dimention) for 3d graphics
		initRendering(); // Render graphics

		glutDisplayFunc(drawScene);
		glutKeyboardFunc(handleKeypress);
		glutReshapeFunc(handleResize);
		glutTimerFunc(animationSpeed, update, 0); // Animate through repeating updates to scene

		glutMainLoop();
	};

	cout << "done";

	return 0;
}
