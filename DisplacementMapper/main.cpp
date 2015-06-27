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



#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"

using namespace std;

float _angle = 0;            //The rotation of the box

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	}
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-10.0f, 1.0f, -50.0f);

	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
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

	/*int adjuster1 = 1.0,adjuster2 = 1.0;
	glTexCoord2f(0.00f*adjuster1, 0.660f*adjuster2);
	glVertex3f(-2.5f, -0.5f, -4.5f);
	glTexCoord2f(0.3300f*adjuster1, 0.660f*adjuster2);
	glVertex3f(-1.0f, -0.5f, -1.5f);
	glTexCoord2f(0.3300f*adjuster1, 1.00f*adjuster2);
	glVertex3f(-1.0f, 1.5f, -4.5f);
	glTexCoord2f(0.00f*adjuster1, 1.00f*adjuster2);
	glVertex3f(-2.5f, 1.5f, -4.5f);*/

	vertsAndTextures vAT3;
	/*vAT3.ULVerInst[0] = -2.5f;
	vAT3.ULVerInst[1] = -0.5f;
	vAT3.ULVerInst[2] = -4.5f;
	vAT3.ULTexInst[0] = 0.00f;
	vAT3.ULTexInst[1] = 0.66f;

	vAT3.URVerInst[0] = -1.0f;
	vAT3.URVerInst[1] = -0.5f;
	vAT3.URVerInst[2] = -4.5f;//-1.5f;
	vAT3.URTexInst[0] = 0.33f;
	vAT3.URTexInst[1] = 0.66f;

	vAT3.BLVerInst[0] = -1.0f;
	vAT3.BLVerInst[1] = 1.5f;
	vAT3.BLVerInst[2] = -4.5f;
	vAT3.BLTexInst[0] = 0.33f;
	vAT3.BLTexInst[1] = 1.00f;

	vAT3.BRVerInst[0] = -2.5f;
	vAT3.BRVerInst[1] = 1.5f;
	vAT3.BRVerInst[2] = -4.5f;
	vAT3.BRTexInst[0] = 0.00f;
	vAT3.BRTexInst[1] = 1.00f;*/

	//createMesh(vAT3);

	int sizeOfMesh = 10;
	int x = 0, y = 0;
	int expandMeshSize = 2.5;

	float verXIncrement = 1.5f;//0.5f;//1.5f;
	float verYIncrement = 1.5f;//2.0f;//0.5f;//2.0f;
	float verZIncrement = 1.0f;//3.5f;//0.5f;//3.5f;
	float texXIncrement = 1.00f/(sizeOfMesh*expandMeshSize);
	float texYIncrement = 1.00f/sizeOfMesh;

	float initVerXUL = -2.50f;
	float initVerXBR = -2.50f;
	float initVerXUR = initVerXUL+verXIncrement;
	float initVerXBL = initVerXBR+verXIncrement;
	float initTexXUL = 0.00f;
	float initTexXBR = 0.00f;
	float initTexXUR = initTexXUL+texXIncrement;
	float initTexXBL = initTexXBR+texXIncrement;
	float initTexYBR = 1.00f;
	float initTexYUL = initTexYBR-texYIncrement;
	float initTexYBL = 1.00f;
	float initTexYUR = initTexYBL-texYIncrement;
	float initVerZUL = -4.50f;
	float initVerZUR = -4.50f;//initVerZUL+verZIncrement;
	float initVerZBL = -4.50f;
	float initVerZBR = -4.50f;

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

	for (y = 0; y < sizeOfMesh; y++) {
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
		if (y < sizeOfMesh/2) {
			vAT3.ULVerInst[1] -= verYIncrement;
			vAT3.URVerInst[1] -= verYIncrement;
			vAT3.BLVerInst[1] -= verYIncrement;
			vAT3.BRVerInst[1] -= verYIncrement;

			vAT3.ULVerInst[2] += verZIncrement;
			vAT3.URVerInst[2] += verZIncrement;
			vAT3.BLVerInst[2] += verZIncrement;
			vAT3.BRVerInst[2] += verZIncrement;

			vAT3.ULTexInst[1] -= texYIncrement;
			vAT3.URTexInst[1] -= texYIncrement;
			vAT3.BLTexInst[1] -= texYIncrement;
			vAT3.BRTexInst[1] -= texYIncrement;
		}
		else if (y >= sizeOfMesh/2) {
			//cout<<"y greater";cout<<"\n";
			vAT3.ULVerInst[1] -= verYIncrement;
			vAT3.URVerInst[1] -= verYIncrement;
			vAT3.BLVerInst[1] -= verYIncrement;
			vAT3.BRVerInst[1] -= verYIncrement;

			vAT3.ULVerInst[2] -= verZIncrement;
			vAT3.URVerInst[2] -= verZIncrement;
			vAT3.BLVerInst[2] -= verZIncrement;
			vAT3.BRVerInst[2] -= verZIncrement;

			vAT3.ULTexInst[1] -= texYIncrement;
			vAT3.URTexInst[1] -= texYIncrement;
			vAT3.BLTexInst[1] -= texYIncrement;
			vAT3.BRTexInst[1] -= texYIncrement;
		}


		for (x = 0; x < sizeOfMesh*expandMeshSize; x++) {
			if ((x < sizeOfMesh/2) | (x < (sizeOfMesh/2+(sizeOfMesh*expandMeshSize-sizeOfMesh)) & x > (sizeOfMesh*expandMeshSize-sizeOfMesh))) {
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
			else if ((x >= sizeOfMesh/2 & x < sizeOfMesh) | (x > (sizeOfMesh/2+(sizeOfMesh*expandMeshSize-sizeOfMesh)) & x < (sizeOfMesh*expandMeshSize))) {
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
			else if (x > (sizeOfMesh) & x < (sizeOfMesh*expandMeshSize-sizeOfMesh)) {
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

			/*cout << "iteration y:";cout<<y;cout<<" x:";cout<<x;cout<<"\n";
			cout<<"sizeOfMesh/2: ";cout<<sizeOfMesh/2;cout<<"\ty>=sizeOfMesh/2:\t";cout<<(y>=sizeOfMesh/2);cout<<"\t(x>=sizeOfMesh/2):\t";cout<<(x>=sizeOfMesh/2);cout<<"\n";
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
		}
	}
	glEnd();

	glutSwapBuffers();
}

//Called every 25 milliseconds
void update(int value) {
	_angle += 0.330f;
	if (_angle > 50) {
		_angle -= 50;
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
	glutTimerFunc(25, update, 0);

	glutMainLoop();
	return 0;
}









