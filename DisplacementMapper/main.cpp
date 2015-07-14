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
double dispMapChangeDelay = 15;//15;//5.0;//5;
double numberOfDispMaps = 6.0;//5;//6;

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

// from https://studiofreya.com/cpp/how-to-check-for-nan-inf-ind-in-c/
template<typename T>
bool is_nan( const T &value )
{
	// True if NAN
	return value != value;
}

//Makes the image into a texture, and returns the id of the texture
/*GLuint loadTexture(Image* image) {
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

GLuint _textureId; //The id of the texture*/



//texture[200] texGroup2;
//Image* texture[200];

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
	//changed
	/*glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading

	//texture[(int)timeInMs] = loadBMP(dispMapGroup[(int)timeInMs]);

	//Image* image = loadBMP(dispMapGroup[(int)timeInMs]);
	//delete image;
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

void calculateWeightChange(String verPositionForWeights, bool anchorForTexUpdate, double startY, double startX, double startZ, double endY, double endX, double endZ) {
	double dispMapChangeCounterWobbling = dispMapChangeCounter*1.0;//2.0;//1.5;//3.0;//1.2;
	// Current point in most direct motion path using anchor points
	double yDirPath = (startY*(1.0-((1.0/dispMapChangeDelay)*dispMapChangeCounterWobbling)))+(endY*((1.0/dispMapChangeDelay)*dispMapChangeCounterWobbling));
	double xDirPath = (startX*(1.0-((1.0/dispMapChangeDelay)*dispMapChangeCounterWobbling)))+(endX*((1.0/dispMapChangeDelay)*dispMapChangeCounterWobbling));
	// Euclidean distance from most direct path of motion from starting anchor point to ending anchor point
	double distance = sqrt(pow(yDirPath-(imageYPixels*((double)y/(double)yMaxAmount)),2)+pow(xDirPath-(imageXPixels*((double)x/(double)xMaxAmount)),2));
	if (dispMapChangeCounterWobbling <= dispMapChangeDelay) {
		lockedDistance = distance;
	}
	else {
		yDirPath = endY;
		xDirPath = startX;
		distance = sqrt(pow(yDirPath-(imageYPixels*((double)y/(double)yMaxAmount)),2)+pow(xDirPath-(imageXPixels*((double)x/(double)xMaxAmount)),2));
	}
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

	double dispMapChangeCounterWobbling2 = dispMapChangeCounterWobbling*2.0;//dispMapChangeCounter*2.0;

	double amountTransitioned = ((1.0/dispMapChangeDelay)*dispMapChangeCounterWobbling);//*distanceRestraint;
	double amountTransitioned2 = ((1.0/dispMapChangeDelay)*dispMapChangeCounterWobbling2);//*distanceRestraint;
	double intialWobbleAllowed = 0.4;//0.3;//5.0;//
	double wobbleIncrement = 1.0;//2.0;//.95;//3.0;//.95;
	double maxWobbles = ceil(intialWobbleAllowed/wobbleIncrement)+1;//*intialWobbleAllowed;
	double wobbleForwardOrBack = 1.0;//-1.0;
	double numberOfWobbles = 0.0;

	for (double i = 1; i <= maxWobbles;i++) {
		if (amountTransitioned2>=((1+intialWobbleAllowed)+(wobbleIncrement*i))) {
			wobbleForwardOrBack = wobbleForwardOrBack * -1;
			numberOfWobbles += 1;
		}
	}

	double wobble = 0;
	double wobbleResistance = 0;

	double diminishingEffect = (1-((1/((dispMapChangeDelay/3.0)))*(dispMapChangeCounterWobbling2-dispMapChangeDelay)));
	if (amountTransitioned2 > (1+intialWobbleAllowed)) {
		wobble = ((sin(((dispMapChangeCounterWobbling2-dispMapChangeDelay)/10)*M_PI)*intialWobbleAllowed)*(diminishingEffect*1.0));
		//wobbleResistance = (dispMapChangeCounter/((dispMapChangeDelay/4.0)));
		wobbleResistance = pow((dispMapChangeCounter/dispMapChangeDelay),2);
		//if (wobbleResistance > 1.0) {wobbleResistance = 0.25;}
		if (wobbleResistance > 1.0) {wobbleResistance = (dispMapChangeDelay/dispMapChangeCounter);}
		amountTransitioned += ( wobble * wobbleResistance );
		//amountTransitioned += ( wobble * .8 );
		//amountTransitioned = 1+wobble;
		//cout<<"++++++++++++++++\n";

		/*change in x, change in y.  keep track of z difference.  for greater change in z, create corresponding extended change in x and y.
		 * account for x and y and scale difference from normal ending z amount by the trajectory of the x and y change, using the amount of z change.
		 * new weight should be added and not =?
		 */
		/* effect surrounding weights
		 */
		double dispMChangeAngle = xYChangeToAngle(endY, startY, endX, startX);
		double pixelToOriginAngle = 0;
		double pixelToOriginDistance = 0;
		double trajectoryOfEffect = 0;
		double surroundingCircumference = 3;
		double effectDistance = (endZ/startZ);// amount of depth change
		double angleWobbleScaling = 0.0;//70.0;//3.0;

		for (double pixelY = (-surroundingCircumference+(floor(surroundingCircumference/2))); pixelY < surroundingCircumference; pixelY+=1.0) {
			for (double pixelX = (-surroundingCircumference+(floor(surroundingCircumference/2))); pixelY < surroundingCircumference; pixelY+=1.0) {
				pixelToOriginAngle = xYChangeToAngle(pixelY, 0.0, pixelX, 0.0);
				trajectoryOfEffect = 0.5+cos(dispMChangeAngle - pixelToOriginAngle);
				pixelToOriginDistance = euclideanDistance(pixelY, 0.0, pixelX, 0.0);
				//amountTransitioned = amountTransitioned * trajectoryOfEffect;
				//amountTransitioned -= ((sin(((dispMapChangeCounterWobbling-dispMapChangeDelay)/10)*M_PI)*intialWobbleAllowed)*(diminishingEffect*1.0)) * trajectoryOfEffect;

				// avoid out of bounds error
				if ((x-surroundingCircumference > 0) & (y-surroundingCircumference > 0) & (x+surroundingCircumference < imageXPixels) & (y+surroundingCircumference > imageYPixels)) {
					if (verPositionForWeights == "BR") {
						weightsBR[(int)pixelY][(int)pixelX] -= angleWobbleScaling * (1-(pixelToOriginDistance/surroundingCircumference)) * wobble * trajectoryOfEffect;
					}
					else if (verPositionForWeights == "BL") {
						weightsBL[(int)pixelY][(int)pixelX+1] -= angleWobbleScaling * (1-(pixelToOriginDistance/surroundingCircumference)) * wobble * trajectoryOfEffect;
					}
					else if (verPositionForWeights == "UL") {
						weightsUL[(int)pixelY+1][(int)pixelX] -= angleWobbleScaling * (1-(pixelToOriginDistance/surroundingCircumference)) * wobble * trajectoryOfEffect;
					}
					else if (verPositionForWeights == "UR") {
						weightsUR[(int)pixelY+1][(int)pixelX+1] -= angleWobbleScaling * (1-(pixelToOriginDistance/surroundingCircumference)) * wobble * trajectoryOfEffect;
					}
				}
			}
		}
		//distance*(1/(endZ/startZ))
	}

	// Difference with starting and ending weights
	double startDispMapWeights = 1.0;
	double endDispMapWeights = (endZ*depthScalingFactor)/(startZ*depthScalingFactor);
	// Position is based on transistion degree including distance restraint limit
	double newWeight = ((distanceRestraint*learningRestraint*startDispMapWeights)*(1-amountTransitioned)) +
			((distanceRestraint*learningRestraint*endDispMapWeights)*(amountTransitioned));
	// normalize tex map with
	double yTexScalingFactor = 2.62649350649;//-2.1484375;
	double texTransDelay = dispMapChangeCounterWobbling*(1/(dispMapChangeDelay*1.5));
	//if (changeTex==false) {texTransDelay = 1-texTransDelay;}
	if (texTransDelay > 1) {texTransDelay = 1;}
	//changeTex
	double newTexY;

	if (is_nan(newWeight)==true) {newWeight = 1.0;}
	if (verPositionForWeights == "BR") {
		weightsBR[y][x] += newWeight;
		// Movement guided by anchor points disabled
		/*if (anchorForTexUpdate == true) {
			if (changeTex == true) {initTexYBR = (initTexYBR2*(1-texTransDelay))+((initTexYBR2*(1.04 / initTexYBR2))*texTransDelay);
			initTexYBL = (initTexYBR2*(1-texTransDelay))+((initTexYBL2*(1.04 / initTexYBL2))*texTransDelay);
			initTexYUL = initTexYBR-texYIncrement;initTexYUR = initTexYBL-texYIncrement;}

			if (changeTex == false) {initTexYBR = (initTexYBR2*(texTransDelay))+((initTexYBR2*(1.04 / initTexYBR2))*(1-texTransDelay));
			initTexYBL = (initTexYBR2*(texTransDelay))+((initTexYBL2*(1.04 / initTexYBL2))*(1-texTransDelay));
			initTexYUL = initTexYBR-texYIncrement;initTexYUR = initTexYBL-texYIncrement;}
		}*/
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

			double borderToCrop = 1;
			applyDispMap(maxXSize, maxYSize, borderToCrop);

			createMesh(vAT3);
		}
	}
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
	//GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	/*GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);*/
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	//glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glRotatef(-_angle, rotationX, rotationY, rotationZ);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, LoadTexture2(texGroup[(int)timeInMs], 512, 512) );

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glColor3f(1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 0.45, 0.0f);
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
	if (timeInMs == transitionTime) {timeInMs = 0;}

	dispMapChangeCounter += 1.0;
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
				endingDispMapImage = dispMapGroup[(int)numberOfDispMaps-2];
				dispMapChangeSine = dispMapChangeSine * -1;
			}
			else if (dispMapChangeSine==-1.0) {
				dispMapFileCounter = 0;
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
			ss << "../../../OpenGL/Media/input/dispMaps/idp0";//"../../../OpenGL/Media/input/backup/idp0";
			ss << i;
			ss << ".bmp";
			std::string s = ss.str();
			const char* p = s.c_str();
			strcpy(dispMapGroup[i], p);
		}
		// Load textures
		for (int i = 0; i < 28; i++) {
			ss.str( std::string() );
			ss.clear();
			ss << "../../../OpenGL/Media/input/textures/idp0";
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

		_angle = 0.0f;//30.00f;//45.330f;//0.0f;

		depthScalingFactor = 0.75;//1.4;//.7;//.025;//.3;//0.1;

		animationDelay = 50.0;
		transitionTime = 28.0;//200.0;//400.0;//200.0;

		texXIncrement = (1.10*(1.00f/(sizeOfMesh2*expandMeshSize)))/texXScaling;
		texYIncrement = (0.6f/sizeOfMesh2)/texYScaling;

		double xShift = 0.95f;
		initTexXUL = xShift;//-0.05f;//0.0f;//
		initTexXBR = xShift;//-0.05f;//-0.10f;
		initTexXUR = initTexXUL+texXIncrement;
		initTexXBL = initTexXBR+texXIncrement;
		double yShift = 0.65f;
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
