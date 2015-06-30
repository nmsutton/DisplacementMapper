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

float _angle = 0;            //The rotation of the box

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	}
}

String imageName6 = "/home/nmsutton/Documents/Software/OpenGL/Media/GeneralProcessed.bmp";
Mat dispMapImage;

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	dispMapImage = imread(imageName6, CV_LOAD_IMAGE_COLOR);

	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading

	Image* image = loadBMP("/home/nmsutton/Documents/Software/OpenGL/Media/generalImg2.bmp");
	_textureId = loadTexture(image);
	delete image;
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

struct vertsAndTextures { float ULVerInst[3]; float URVerInst[3]; float BLVerInst[3]; float BRVerInst[3];
float ULTexInst[2]; float URTexInst[2]; float BLTexInst[2]; float BRTexInst[2];};

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

void drawScene() {
	/*double grayLevel = 0;
	double priorAdjustedGrayLevel = 0;
	double nextGrayLevel = 0;*/
	double meshVec_neg1_neg1 = 0;
	double meshVec_neg1_0 = 0;
	double meshVec_neg1_1 = 0;
	double meshVec_0_neg1 = 0;
	double meshVec_0_0 = 0;
	double meshVec_0_1 = 0;
	double meshVec_1_neg1 = 0;
	double meshVec_1_0 = 0;
	double meshVec_1_1 = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// camera position mapper
	//glTranslatef(-30.0f, 1.0f, -60.0f);//-150.0f);
	glTranslatef(-25.0f, 11.0f, -90.0f);//-150.0f);

	//GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat ambientLight[] = {200.2f, 200.2f, 200.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glRotatef(-_angle, -0.20f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	glNormal3f(1.0f, 1.0f, 1.0f);

	//glFrustum(-10, 0, 0, 10, -200000, 200000000);

	vertsAndTextures vAT3;

	//double sizeScalingFactor = 5;
	double sizeOfMesh = 10;//6;//50;
	//sizeOfMesh = sizeOfMesh/sizeScalingFactor;
	double sizeOfMesh2 = sizeOfMesh*2;
	//double x = 0, y = 0;
	int x = 0, y = 0;
	double expandMeshSize = 2.0;//2.5;
	float initalZ = 40.0f;
	double depthScalingFactor = .015;//.025;//.3;//0.1;

	float verXIncrement = 1.5f;//0.5f;//1.5f;
	float verYIncrement = 1.5f;//2.0f;//0.5f;//2.0f;
	float verZIncrement = 1.0f;//3.5f;//0.5f;//3.5f;
	//float texXIncrement = 1.1*(1.00f/(sizeOfMesh*expandMeshSize));
	float texXIncrement = 1.07*(1.00f/(sizeOfMesh2*expandMeshSize));
	float texYIncrement = 1.00f/sizeOfMesh2;

	float initVerXUL = -2.50f;
	float initVerXBR = -2.50f;
	float initVerXUR = initVerXUL+verXIncrement;
	float initVerXBL = initVerXBR+verXIncrement;
	float initTexXUL = -0.05f;//-0.05f;//0.0f;//
	float initTexXBR = -0.05f;//-0.05f;//-0.10f;
	float initTexXUR = initTexXUL+texXIncrement;
	float initTexXBL = initTexXBR+texXIncrement;
	float initTexYBR = 1.0f;//1.10f;
	float initTexYUL = initTexYBR-texYIncrement;
	float initTexYBL = 1.0f;//1.10f;
	float initTexYUR = initTexYBL-texYIncrement;
	float initVerZUL = -4.50f+initalZ;
	float initVerZUR = -4.50f+initalZ;//initVerZUL+verZIncrement;
	float initVerZBL = -4.50f+initalZ;
	float initVerZBR = -4.50f+initalZ;

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

	//double incrementValue = 0.5;
	int incrementValue = 1;

	// Build displacement map.  *2 is due to 2 rectangle verticies for each x and y axis used for the later Z level mapping.
	double verticiesInRectangle = 2;
	int xAmount = ceil(sizeOfMesh*expandMeshSize*(1/incrementValue))*2, yAmount = ceil(sizeOfMesh*(1/incrementValue))*2;
	double verZLevels[yAmount][xAmount] = {0};
	for (int y = 0; y < yAmount; y += 2) {
		for (x = 0; x < xAmount; x += 2) {
			double imageToScenePixelDiff = (255/(double)sizeOfMesh)*(1/verticiesInRectangle);
			//double translatedX = x * imageToScenePixelDiff; double translatedY = y * imageToScenePixelDiff;
			double translatedX = ceil(x * imageToScenePixelDiff); double translatedY = ceil(y * imageToScenePixelDiff);
			////cout << "translatedX\t";cout<<translatedX;cout<<"\ttranslatedY\t";cout<<translatedY;cout<<"\n";
			//double nextTranslatedX = (x+incrementValue) * imageToScenePixelDiff; double nextTranslatedY = (y+incrementValue) * imageToScenePixelDiff;
			//double priorTranslatedX = (x-incrementValue) * imageToScenePixelDiff; double priorTranslatedY = (y-incrementValue) * imageToScenePixelDiff;
			double meshVec_0_0_b = dispMapImage.at<Vec3b>((int)translatedY,(int)translatedX).val[0];
			//meshVec_0_0_b = meshVec_0_0_b/3;
			meshVec_0_0_b = meshVec_0_0_b/4;

			//cout<<"\ny: ";cout<<y;cout<<" x: ";cout<<x;cout<<"\n";

			////cout<<"[y+1][x+1]\t";cout<<x+1;cout<<" ";cout<<y+1;cout<<" ";cout<<" meshVec_0_0 ";cout<<meshVec_0_0_b;cout<<"\n";
			if (x < xAmount) {
				verZLevels[y][x] = meshVec_0_0_b;
			}
			if (x > 0) {
				verZLevels[y][x+1] = meshVec_0_0_b;
			}
			if ((y < yAmount) & (x < xAmount)) {
				verZLevels[y+1][x+1] = meshVec_0_0_b;
			}
			if (y > 0) {
				verZLevels[y+1][x] = meshVec_0_0_b;
			}
		}
	}
	//cout << "yAmount\t";cout << yAmount;
	//cout<<"\txAmount\t";cout<<xAmount;
	//cout<<"\n";

	// print out
	/*for (int y = 0; y < yAmount; y += 1) {
		for (x = 0; x < xAmount; x += 1) {
			double imageToScenePixelDiff = (255/(double)sizeOfMesh)*(1/verticiesInRectangle);
			double translatedX = ceil(x * imageToScenePixelDiff); double translatedY = ceil(y * imageToScenePixelDiff);
			double meshVec_0_0_b = dispMapImage.at<Vec3b>((int)translatedY,(int)translatedX).val[0];
			//cout<<"(";cout<<y;cout<<",";cout<<x;cout<<"):";
			cout<<"\t";cout<<meshVec_0_0_b;
		}
		cout<<"\n";
	}
	cout<<"_ _ _\n";*/

	int scalingF = 2;
	int incrementValue2 = 1;
	double maxYSize = sizeOfMesh*scalingF;
	double maxXSize = (sizeOfMesh*expandMeshSize*scalingF);
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

		//if (x==0 & y==0) {createMesh(vAT3);}

		// For y dimension iteration update the y values
		if (y < maxYSize/2) {
			vAT3.ULVerInst[1] -= verYIncrement;
			vAT3.URVerInst[1] -= verYIncrement;
			vAT3.BLVerInst[1] -= verYIncrement;
			vAT3.BRVerInst[1] -= verYIncrement;

			/*vAT3.ULVerInst[2] += verZIncrement;
			vAT3.URVerInst[2] += verZIncrement;
			vAT3.BLVerInst[2] += verZIncrement;
			vAT3.BRVerInst[2] += verZIncrement;*/

			vAT3.ULTexInst[1] -= texYIncrement;
			vAT3.URTexInst[1] -= texYIncrement;
			vAT3.BLTexInst[1] -= texYIncrement;
			vAT3.BRTexInst[1] -= texYIncrement;
		}
		else if (y >= maxYSize/2) {
			//cout<<"y greater";cout<<"\n";
			vAT3.ULVerInst[1] -= verYIncrement;
			vAT3.URVerInst[1] -= verYIncrement;
			vAT3.BLVerInst[1] -= verYIncrement;
			vAT3.BRVerInst[1] -= verYIncrement;

			/*vAT3.ULVerInst[2] -= verZIncrement;
			vAT3.URVerInst[2] -= verZIncrement;
			vAT3.BLVerInst[2] -= verZIncrement;
			vAT3.BRVerInst[2] -= verZIncrement;*/

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

				/*vAT3.ULVerInst[2] += verZIncrement;
				vAT3.URVerInst[2] += verZIncrement;			
				vAT3.BLVerInst[2] += verZIncrement;
				vAT3.BRVerInst[2] += verZIncrement;*/

				vAT3.ULTexInst[0] += texXIncrement;
				vAT3.URTexInst[0] += texXIncrement;
				vAT3.BLTexInst[0] += texXIncrement;
				vAT3.BRTexInst[0] += texXIncrement;
			}
			else if ((x >= maxYSize/2 & x < maxYSize) | (x > (maxYSize/2+(maxXSize-maxYSize)) & x < (maxXSize))) {
				//cout<<"x greater";cout<<"\n";
				vAT3.ULVerInst[0] += verXIncrement;
				vAT3.URVerInst[0] += verXIncrement;
				vAT3.BLVerInst[0] += verXIncrement;
				vAT3.BRVerInst[0] += verXIncrement;

				/*vAT3.ULVerInst[2] -= verZIncrement;
				vAT3.URVerInst[2] -= verZIncrement;
				vAT3.BLVerInst[2] -= verZIncrement;
				vAT3.BRVerInst[2] -= verZIncrement;*/

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

				/*vAT3.ULVerInst[2] -= verZIncrement;
				vAT3.URVerInst[2] -= verZIncrement;			
				vAT3.BLVerInst[2] -= verZIncrement;
				vAT3.BRVerInst[2] -= verZIncrement;*/

				vAT3.ULTexInst[0] += texXIncrement;
				vAT3.URTexInst[0] += texXIncrement;
				vAT3.BLTexInst[0] += texXIncrement;
				vAT3.BRTexInst[0] += texXIncrement;
			}



			// Apply displacement map

			double imageToScenePixelDiff = 255/maxYSize;
			double translatedX = x * imageToScenePixelDiff; double translatedY = y * imageToScenePixelDiff;
			double nextTranslatedX = (x+incrementValue) * imageToScenePixelDiff; double nextTranslatedY = (y+incrementValue) * imageToScenePixelDiff;
			double priorTranslatedX = (x-incrementValue) * imageToScenePixelDiff; double priorTranslatedY = (y-incrementValue) * imageToScenePixelDiff;
			/*grayLevel = dispMapImage.at<Vec3b>(translatedY,translatedX).val[0];
			if (x != (maxYSize-1)*expandMeshSize) {
				nextGrayLevel = dispMapImage.at<Vec3b>(nextTranslatedY,nextTranslatedX).val[0];
			}*/
			// Avoid edge problems
			double tempVal = 0;
			/*if (x >= ((maxYSize-1)*expandMeshSize)) {
				nextTranslatedX = tempVal;//translatedX;
			}
			if (x == 0) {
				priorTranslatedX = tempVal;//translatedX;
			}
			if (y >= ((maxYSize-1))) {
				nextTranslatedY = tempVal;//translatedY;
			}
			if (y == 0) {
				priorTranslatedY = tempVal;//translatedY;
			}*/
			meshVec_neg1_neg1 = dispMapImage.at<Vec3b>(priorTranslatedY,priorTranslatedX).val[0];
			meshVec_neg1_0 = dispMapImage.at<Vec3b>(priorTranslatedY,translatedX).val[0];
			meshVec_neg1_1 = dispMapImage.at<Vec3b>(priorTranslatedY,nextTranslatedX).val[0];
			meshVec_0_neg1 = dispMapImage.at<Vec3b>(translatedY,priorTranslatedX).val[0];
			meshVec_0_0 = dispMapImage.at<Vec3b>(translatedY,translatedX).val[0];
			meshVec_0_1 = dispMapImage.at<Vec3b>(translatedY,nextTranslatedX).val[0];
			meshVec_1_neg1 = dispMapImage.at<Vec3b>(nextTranslatedY,priorTranslatedX).val[0];
			meshVec_1_0 = dispMapImage.at<Vec3b>(nextTranslatedY,translatedX).val[0];
			meshVec_1_1 = dispMapImage.at<Vec3b>(nextTranslatedY,nextTranslatedX).val[0];

			/*double vectorSlope = .25;
			vAT3.ULVerInst[2] = vectorSlope*((meshVec_1_1-meshVec_neg1_neg1)*.5+(meshVec_1_neg1-meshVec_neg1_1)*.5);*/

			/*vAT3.ULVerInst[2] = ((meshVec_neg1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = ((meshVec_neg1_1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = ((meshVec_1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = ((meshVec_1_1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = ((meshVec_0_0)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = ((meshVec_neg1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = ((meshVec_neg1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = ((meshVec_0_0)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = ((meshVec_neg1_1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = ((meshVec_1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = ((meshVec_1_1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = ((meshVec_neg1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = ((meshVec_0_0)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = ((meshVec_0_0)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = ((meshVec_neg1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = ((meshVec_0_0)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = ((meshVec_0_0)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = ((meshVec_neg1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = ((meshVec_neg1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = ((meshVec_neg1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = ((meshVec_neg1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = ((meshVec_0_0)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = ((meshVec_0_0)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = ((meshVec_neg1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = ((meshVec_0_0)*.5+(meshVec_1_1)*.5) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = ((meshVec_0_0)*.5+(meshVec_1_1)*.5) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = ((meshVec_neg1_neg1)*.5+(meshVec_0_0)*.5) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = (meshVec_neg1_neg1) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = (meshVec_neg1_1) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = (meshVec_1_neg1) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = (meshVec_1_1) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = (meshVec_neg1_1) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = (meshVec_neg1_neg1) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = (meshVec_1_neg1) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = (meshVec_1_1) * depthScalingFactor+initalZ;*/

			/*double sharedVert = meshVec_1_1;
			vAT3.ULVerInst[2] = (sharedVert) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = (sharedVert) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = (sharedVert) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = (sharedVert) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = (meshVec_neg1_neg1) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = (meshVec_neg1_0) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = (meshVec_0_neg1) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = (meshVec_0_0) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = (meshVec_0_0) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = (meshVec_0_0) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = (meshVec_1_1) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = (meshVec_1_1) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = (meshVec_0_0) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = (meshVec_1_1) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = (meshVec_1_1) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = (meshVec_0_0) * depthScalingFactor+initalZ;*/
			/*vAT3.ULVerInst[2] = initalZ;//(meshVec_0_0) * depthScalingFactor+initalZ;//bl
			vAT3.URVerInst[2] = initalZ+3;//(meshVec_0_0) * depthScalingFactor+initalZ;//br
			vAT3.BLVerInst[2] = initalZ+3;//(meshVec_0_0) * depthScalingFactor+initalZ;//ur
			vAT3.BRVerInst[2] = initalZ;//(meshVec_0_0) * depthScalingFactor+initalZ;//ul*/
			/*vAT3.ULVerInst[2] = (meshVec_0_0) * depthScalingFactor+initalZ;//bl
			vAT3.URVerInst[2] = (meshVec_1_1) * depthScalingFactor+initalZ;//br
			vAT3.BLVerInst[2] = (meshVec_1_1) * depthScalingFactor+initalZ;//ur
			vAT3.BRVerInst[2] = (meshVec_0_0) * depthScalingFactor+initalZ;//ul*/
			/*vAT3.ULVerInst[2] = (meshVec_0_0) * depthScalingFactor+initalZ;
			vAT3.URVerInst[2] = (meshVec_neg1_neg1) * depthScalingFactor+initalZ;
			vAT3.BLVerInst[2] = (meshVec_0_0) * depthScalingFactor+initalZ;
			vAT3.BRVerInst[2] = (meshVec_0_0) * depthScalingFactor+initalZ;*/

			/*vAT3.ULVerInst[2] = (meshVec_0_0) * depthScalingFactor+initalZ;//bl
			vAT3.URVerInst[2] = (meshVec_0_1) * depthScalingFactor+initalZ;//br
			vAT3.BLVerInst[2] = (meshVec_neg1_0) * depthScalingFactor+initalZ;//ur
			vAT3.BRVerInst[2] = (meshVec_neg1_0) * depthScalingFactor+initalZ;//ul*/

			/*vAT3.ULVerInst[2] = (meshVec_1_0) * depthScalingFactor+initalZ;//bl
			vAT3.URVerInst[2] = ((meshVec_0_1+meshVec_1_0)/2) * depthScalingFactor+initalZ;//br  ((meshVec_0_1+meshVec_1_0)/2)
			vAT3.BLVerInst[2] = (meshVec_0_1) * depthScalingFactor+initalZ;//ur
			vAT3.BRVerInst[2] = ((meshVec_0_neg1+meshVec_neg1_0)/2) * depthScalingFactor+initalZ;//ul*/

			int x2 = x, y2 = y;
			if (x2 < (maxXSize)) {
				vAT3.BRVerInst[2] = verZLevels[y2][x2];//verZLevels[y2][x2] = meshVec_0_0;
			}
			if (x2 > 0) {
				vAT3.BLVerInst[2] = verZLevels[y2][x2+1];//verZLevels[y2][x2+1] = meshVec_0_0;
			}
			if ((y2 < maxYSize-1) & (x2 < (maxXSize-1))) {
				vAT3.URVerInst[2] = verZLevels[y2+1][x2+1];// = meshVec_0_0;
			}
			if (y2 > 0 & y2 < maxYSize-1) {
				vAT3.ULVerInst[2] = verZLevels[y2+1][x2];// = meshVec_0_0;
			}
			/*vAT3.BRVerInst[2] = verZLevels[y2][x2];
			vAT3.BLVerInst[2] = verZLevels[y2][x2+1];
			vAT3.URVerInst[2] = verZLevels[y2+1][x2+1];
			vAT3.ULVerInst[2] = verZLevels[y2+1][x2];*/
			/*vAT3.BRVerInst[2] = 0;
			vAT3.BLVerInst[2] = 0;
			vAT3.URVerInst[2] = 0;
			vAT3.ULVerInst[2] = 0;*/

			/*cout<<"\n_______\n";
			cout<<"x\t";cout<<x;cout<<"\ty\t";cout<<y;cout<<"\n";
			cout<<"\tmeshVec_0_0\t";cout<<meshVec_0_0;
			cout<<"\tmeshVec_0_1\t";cout<<meshVec_0_1;
			cout<<"\tmeshVec_1_0\t";cout<<meshVec_1_0;
			cout<<"\tmeshVec_1_1\t";cout<<meshVec_1_1;*/

			/*if (x > 0 & x< maxXSize*imageToScenePixelDiff) {
			//if (x > 0) {
				//vAT3.ULVerInst[2] = grayLevel*depthScalingFactor+initalZ;
				vAT3.ULVerInst[2] = priorAdjustedGrayLevel+initalZ;
				vAT3.URVerInst[2] = grayLevel*depthScalingFactor+initalZ;
				//vAT3.URVerInst[2] = priorAdjustedGrayLevel+initalZ;
				vAT3.BLVerInst[2] = grayLevel*depthScalingFactor+initalZ;
				//vAT3.BLVerInst[2] = priorAdjustedGrayLevel+initalZ;
				//vAT3.BRVerInst[2] = grayLevel*depthScalingFactor+initalZ;
				vAT3.BRVerInst[2] = priorAdjustedGrayLevel+initalZ;
			}
			else {
				vAT3.ULVerInst[2] = 0+initalZ;
				vAT3.URVerInst[2] = nextGrayLevel*depthScalingFactor+initalZ;
				//vAT3.URVerInst[2] = priorAdjustedGrayLevel+initalZ;
				vAT3.BLVerInst[2] = nextGrayLevel*depthScalingFactor+initalZ;
				//vAT3.BLVerInst[2] = priorAdjustedGrayLevel+initalZ;
				//vAT3.BRVerInst[2] = grayLevel*depthScalingFactor+initalZ;
				vAT3.BRVerInst[2] = 0+initalZ;
			}*/
			//priorAdjustedGrayLevel = grayLevel*depthScalingFactor;


			//cout<<"translatedY\t";cout<<translatedY;cout<<"\ttranslatedX\t";cout<<translatedX;cout<<"\tgrey level\t";cout<<grayLevel;cout<<"\tgrayLevel*depthScalingFactor\t";cout<<grayLevel*depthScalingFactor;cout<<"\n";
			//vAT3.BRVerInst[2] (int)image.at<Vec3b>(y,x).val[0]

			/*cout << "iteration y:";cout<<y;cout<<" x:";cout<<x;cout<<"\n";
			cout<<"maxYSize/2: ";cout<<maxYSize/2;cout<<"\ty>=maxYSize/2:\t";cout<<(y>=maxYSize/2);cout<<"\t(x>=maxYSize/2):\t";cout<<(x>=maxYSize/2);cout<<"\n";
			cout<<"UL_X:   ";cout << vAT3.ULVerInst[0];cout<<"\n";
			cout<<"UL_Y:   ";cout << vAT3.ULVerInst[1];cout<<"\n";
			cout<<"UL_Z:   ";cout << vAT3.ULVerInst[2];cout<<"\n";
			cout<<"UL_texX:   ";cout << vAT3.ULTexInst[0];cout<<"\n";
			cout<<"UL_texY:   ";cout << vAT3.ULTexInst[1];cout<<"\n";

			cout<<"UR_X:   ";cout << vAT3.URVerInst[0];cout<<"\n";
			cout<<"UR_Y:   ";cout << vAT3.URVerInst[1];cout<<"\n";
			cout<<"UR_Z:   ";cout << vAT3.URVerInst[2];cout<<"\n";
			cout<<"UR_texX:   ";cout << vAT3.URTexInst[0];cout<<"\n";
			cout<<"UR_texY:   ";cout << vAT3.URTexInst[1];cout<<"\n";

			cout<<"BL_X:   ";cout << vAT3.BLVerInst[0];cout<<"\n";
			cout<<"BL_Y:   ";cout << vAT3.BLVerInst[1];cout<<"\n";
			cout<<"BL_Z:   ";cout << vAT3.BLVerInst[2];cout<<"\n";
			cout<<"BL_texX:   ";cout << vAT3.BLTexInst[0];cout<<"\n";
			cout<<"BL_texY:   ";cout << vAT3.BLTexInst[1];cout<<"\n";

			cout<<"BR_X:   ";cout << vAT3.BRVerInst[0];cout<<"\n";
			cout<<"BR_Y:   ";cout << vAT3.BRVerInst[1];cout<<"\n";
			cout<<"BR_Z:   ";cout << vAT3.BRVerInst[2];cout<<"\n";
			cout<<"BR_texX:   ";cout << vAT3.BRTexInst[0];cout<<"\n";
			cout<<"BR_texY:   ";cout << vAT3.BRTexInst[1];cout<<"\n";
			cout<<"_____________________\n";*/

			createMesh(vAT3);
			//priorAdjustedGrayLevel = grayLevel*depthScalingFactor;
		}
	}
	glEnd();

	glutSwapBuffers();
}

//Called every 25 milliseconds
void update(int value) {
	_angle += 1.0f;//0.1f;//0.330f;
	if (_angle > 50) {
		_angle -= 100;
	}
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow("Textures - videotutorialsrock.com");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	_angle = -45.330f;//25.330f;
	glutTimerFunc(25, update, 0);

	glutMainLoop();
	return 0;
}









