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
String simulationToRun = "gaborFilter";//"gaborFilter";//"LGNReceptiveField";//"LGNSpaceTimeFixedY";
bool simulationFound = false;

float _angle = 0;            //The rotation of the box

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	}
}

//const char texGroup[200][150] = {"../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_0.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_1.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_2.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_3.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_4.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_5.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_6.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_7.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_8.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_9.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_10.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_11.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_12.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_13.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_14.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_15.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_16.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_17.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_18.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_19.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_20.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_21.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_22.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_23.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_24.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_25.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_26.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_27.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_28.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_29.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_30.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_31.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_32.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_33.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_34.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_35.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_36.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_37.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_38.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_39.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_40.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_41.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_42.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_43.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_44.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_45.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_46.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_47.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_48.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_49.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_50.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_51.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_52.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_53.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_54.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_55.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_56.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_57.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_58.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_59.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_60.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_61.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_62.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_63.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_64.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_65.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_66.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_67.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_68.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_69.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_70.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_71.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_72.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_73.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_74.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_75.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_76.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_77.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_78.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_79.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_80.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_81.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_82.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_83.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_84.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_85.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_86.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_87.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_88.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_89.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_90.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_91.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_92.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_93.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_94.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_95.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_96.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_97.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_98.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_99.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_100.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_101.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_102.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_103.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_104.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_105.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_106.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_107.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_108.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_109.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_110.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_111.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_112.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_113.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_114.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_115.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_116.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_117.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_118.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_119.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_120.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_121.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_122.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_123.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_124.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_125.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_126.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_127.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_128.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_129.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_130.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_131.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_132.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_133.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_134.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_135.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_136.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_137.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_138.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_139.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_140.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_141.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_142.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_143.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_144.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_145.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_146.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_147.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_148.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_149.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_150.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_151.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_152.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_153.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_154.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_155.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_156.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_157.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_158.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_159.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_160.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_161.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_162.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_163.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_164.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_165.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_166.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_167.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_168.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_169.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_170.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_171.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_172.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_173.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_174.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_175.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_176.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_177.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_178.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_179.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_180.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_181.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_182.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_183.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_184.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_185.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_186.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_187.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_188.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_189.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_190.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_191.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_192.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_193.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_194.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_195.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_196.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_197.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_198.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_199.bmp"};
//const char texGroup[200][150] = {"../../../OpenGL/Media/diffGaus/plot1/diffGaus_0.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_1.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_2.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_3.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_4.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_5.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_6.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_7.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_8.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_9.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_10.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_11.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_12.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_13.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_14.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_15.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_16.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_17.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_18.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_19.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_20.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_21.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_22.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_23.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_24.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_25.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_26.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_27.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_28.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_29.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_30.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_31.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_32.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_33.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_34.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_35.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_36.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_37.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_38.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_39.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_40.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_41.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_42.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_43.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_44.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_45.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_46.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_47.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_48.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_49.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_50.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_51.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_52.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_53.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_54.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_55.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_56.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_57.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_58.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_59.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_60.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_61.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_62.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_63.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_64.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_65.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_66.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_67.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_68.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_69.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_70.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_71.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_72.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_73.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_74.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_75.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_76.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_77.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_78.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_79.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_80.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_81.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_82.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_83.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_84.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_85.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_86.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_87.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_88.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_89.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_90.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_91.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_92.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_93.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_94.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_95.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_96.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_97.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_98.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_99.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_100.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_101.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_102.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_103.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_104.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_105.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_106.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_107.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_108.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_109.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_110.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_111.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_112.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_113.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_114.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_115.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_116.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_117.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_118.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_119.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_120.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_121.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_122.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_123.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_124.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_125.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_126.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_127.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_128.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_129.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_130.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_131.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_132.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_133.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_134.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_135.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_136.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_137.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_138.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_139.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_140.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_141.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_142.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_143.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_144.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_145.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_146.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_147.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_148.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_149.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_150.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_151.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_152.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_153.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_154.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_155.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_156.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_157.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_158.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_159.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_160.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_161.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_162.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_163.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_164.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_165.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_166.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_167.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_168.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_169.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_170.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_171.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_172.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_173.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_174.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_175.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_176.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_177.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_178.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_179.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_180.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_181.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_182.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_183.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_184.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_185.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_186.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_187.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_188.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_189.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_190.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_191.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_192.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_193.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_194.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_195.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_196.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_197.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_198.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_199.bmp"};
char texGroup[200][150];// = {"../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp"};
String image1 = texGroup[0];
String image2 = texGroup[1];
String startingDispMapImage = image2;
String endingDispMapImage = image1;
Mat startingDispMap;
Mat endingDispMap;
String anchorImage1 = "../../../OpenGL/Media/gaborAnchorImageExtra.bmp";
String anchorImage2 = "../../../OpenGL/Media/gaborAnchorImageExtra.bmp";
String startingDispMapAnchorImage = anchorImage2;
String endingDispMapAnchorImage = anchorImage1;
const int numberOfAnchors = 1;
Mat startingDispMapAnchor;
Mat endingDispMapAnchor;
double timeInMs = 0;

const int incrementValue = 1;

// *2 is due to 2 rectangle verticies for each x and y axis used for the later Z level mapping.
double verticiesInRectangle = 2;
double sizeOfMesh = 40;//35;//10;//6;//50;
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
const double maxMeshSizeAllowed = 200;
int xMaxAmount = ceil(sizeOfMesh*(1/incrementValue))*2, yMaxAmount = ceil(sizeOfMesh*(1/incrementValue))*2;
const int xMaxAmountForArray = ceil(maxMeshSizeAllowed*(1/incrementValue))*2, yMaxAmountForArray = ceil(maxMeshSizeAllowed*(1/incrementValue))*2;
double startingVerZLevels[xMaxAmountForArray][yMaxAmountForArray] = {0};
double endingVerZLevels[xMaxAmountForArray][yMaxAmountForArray] = {0};
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
//float texXIncrement = 1.1*(1.00f/(sizeOfMesh*expandMeshSize));
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

// from https://studiofreya.com/cpp/how-to-check-for-nan-inf-ind-in-c/
template<typename T>
bool is_nan( const T &value )
{
	// True if NAN
	return value != value;
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	//dispMapImage = imread(imageName6, CV_LOAD_IMAGE_COLOR);

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
		//startingVerZLevels = verZLevels;
		copy(verZLevels[0], verZLevels[yMaxAmount], startingVerZLevels[0]);
	}
	else if (startingOrEndPoint == "end") {
		//endingVerZLevels = verZLevels;
		copy(verZLevels[0], verZLevels[yMaxAmount], endingVerZLevels[0]);
	};
}

double weightsBR[yMaxAmountForArray][xMaxAmountForArray] = {1};
double weightsBL[yMaxAmountForArray][xMaxAmountForArray] = {1};
double weightsUL[yMaxAmountForArray][xMaxAmountForArray] = {1};
double weightsUR[yMaxAmountForArray][xMaxAmountForArray] = {1};

void initWeights() {
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsBR[weightY], xMaxAmount, 1.0);};
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsBL[weightY], xMaxAmount, 1.0);};
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsUL[weightY], xMaxAmount, 1.0);};
	for (int weightY = 0;weightY < yMaxAmount;weightY++) {fill_n(weightsUR[weightY], xMaxAmount, 1.0);};
}

void extractAnchorPoint(Mat anchorPointImage, String anchorPointPosition) {
	// Find anchor points.  Search for pixels that are red B,G,R for OpenGL (1,1,255)
	bool anchorFound1 = false;
	for(int y=0;y<anchorPointImage.rows;y++)
	{
		for (int x=0;x<anchorPointImage.cols;x++)
		{
			//if ((anchorPointImage.at<Vec3b>(y,x) != Vec3b(0,0,0)) & (anchorFound == false)) {
			int blueLevel = anchorPointImage.at<Vec3b>(y,x).val[0];
			int greenLevel = anchorPointImage.at<Vec3b>(y,x).val[1];
			int redLevel = anchorPointImage.at<Vec3b>(y,x).val[2];
			if ((blueLevel <= 50) & (greenLevel <= 50) & (redLevel >= 200)) {
				if ((anchorPointPosition=="start") & (anchorFound1 == false)) {
					startingDispMapAnchorPoint[0][0]=y;
					startingDispMapAnchorPoint[0][1]=x;
					anchorFound1 = true;
					//out<<"\n\nstart anchor found\t";cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
				}
				else if ((anchorPointPosition=="start") & (anchorFound1 == true) & numberOfAnchors > 1){
					startingDispMapAnchorPoint[1][0]=y;
					startingDispMapAnchorPoint[1][1]=x;
					//cout<<"\n\nstart anchor 2 found\t";cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
				}
				else if ((anchorPointPosition=="end") & (anchorFound1 == false)) {
					anchorFound1 = true;
					endingDispMapAnchorPoint[0][0]=y;
					endingDispMapAnchorPoint[0][1]=x;
					//cout<<"\n\nend anchor found\t";cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
				}
				else if ((anchorPointPosition=="end") & (anchorFound1 == true) & numberOfAnchors > 1) {
					endingDispMapAnchorPoint[1][0]=y;
					endingDispMapAnchorPoint[1][1]=x;
					//cout<<"\n\nend anchor 2 found\t";cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
				}
			}
		}
	}
}

void findAnchorPoints() {
	startingDispMapAnchor = imread(startingDispMapAnchorImage, CV_LOAD_IMAGE_COLOR);
	endingDispMapAnchor = imread(endingDispMapAnchorImage, CV_LOAD_IMAGE_COLOR);

	extractAnchorPoint(startingDispMapAnchor, "start");
	extractAnchorPoint(endingDispMapAnchor, "end");
}

void calculateWeightChange(String verPositionForWeights, bool anchorForTexUpdate, double startY, double startX, double startZ, double endY, double endX, double endZ) {
	// Current point in most direct motion path using anchor points
	double yDirPath = (startY*(1.0-((1.0/animationDelay)*timeInMs)))+(endY*((1.0/animationDelay)*timeInMs));
	double xDirPath = (startX*(1.0-((1.0/animationDelay)*timeInMs)))+(endX*((1.0/animationDelay)*timeInMs));
	// Euclidean distance from most direct path of motion from starting anchor point to ending anchor point
	double distance = sqrt(pow(yDirPath-(imageYPixels*((double)y/(double)yMaxAmount)),2)+pow(xDirPath-(imageXPixels*((double)x/(double)xMaxAmount)),2));
	if (timeInMs <= animationDelay) {
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

	double amountTransitioned = ((1.0/animationDelay)*timeInMs)*distanceRestraint;
	double amountTransitioned2 = ((1.0/animationDelay)*timeInMs)*distanceRestraint;
	double intialWobbleAllowed = 0.3;
	double wobbleIncrement = .95;
	double maxWobbles = ceil(intialWobbleAllowed/wobbleIncrement)+1;//*intialWobbleAllowed;
	double wobbleForwardOrBack = 1.0;//-1.0;
	double numberOfWobbles = 0.0;

	for (double i = 1; i <= maxWobbles;i++) {
		if (amountTransitioned2>=((1+intialWobbleAllowed)+(wobbleIncrement*i))) {
			wobbleForwardOrBack = wobbleForwardOrBack * -1;
			numberOfWobbles += 1;
		}
	}

	double diminishingEffect = (1-((1/(transitionTime-animationDelay))*(timeInMs-animationDelay)));
	if (amountTransitioned2 > (1+intialWobbleAllowed)) {

		amountTransitioned = 1+((sin(((timeInMs-animationDelay)/10)*M_PI)*intialWobbleAllowed)*(diminishingEffect*1.0));
	}

	// Difference with starting and ending weights
	double startDispMapWeights = 1.0;
	double endDispMapWeights = (endZ*depthScalingFactor)/(startZ*depthScalingFactor);
	// Position is based on transistion degree including distance restraint limit
	double newWeight = ((distanceRestraint*learningRestraint*startDispMapWeights)*(1-amountTransitioned)) +
			((distanceRestraint*learningRestraint*endDispMapWeights)*(amountTransitioned));
	// normalize tex map with
	double yTexScalingFactor = 2.62649350649;//-2.1484375;
	double texTransDelay = timeInMs*(1/(animationDelay*1.5));
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
	// Use self organizing maps to apply disp map movement transition

	/*
	s is the current iteration
	L is the iteration limit
	t is the index of the target input data vector in the input data set \mathbf{D}
	D(t) is a target input data vector
	v is the index of the node in the map
	W_v is the current weight vector of node v
	u is the index of the best matching unit (BMU) in the map
	Θ(u, v, s) is a restraint due to distance from BMU, usually called the neighborhood function, and
	α (s) is a learning restraint due to iteration progress.*/



	// Wv(s + 1) = Wv(s) + Θ(u, v, s) α(s)(D(t) - Wv(s))

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

void drawScene() {
	startingDispMap = imread(startingDispMapImage, CV_LOAD_IMAGE_COLOR);
	endingDispMap = imread(endingDispMapImage, CV_LOAD_IMAGE_COLOR);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// camera position mapper
	glTranslatef(-60.0f, -35.0f, -100.0f);//-150.0f);

	//GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat ambientLight[] = {1000.2f, 1000.2f, 1000.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = {200.7f, 200.7f, 200.7f, 1.0f};
	GLfloat directedLightPos[] = {-210.0f, 215.0f, 220.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glRotatef(-_angle+10, -30.00f, 30.0f, 100.0f);

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
	cout<<timeInMs;cout<<"\n";
	glutPostRedisplay();
	glutTimerFunc(animationSpeed, update, 0);
}

void create3dGraphics(int argc, char** argv) {

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
		//startingDispMap;
		//endingDispMap;

		// camera position mapper
		glTranslatef(-60.0f, -35.0f, -100.0f);//-150.0f);

		glRotatef(-_angle+10, -30.00f, 30.0f, 100.0f);

		sizeOfMesh = 40;//35;//10;//6;//50;

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
		_angle = -84.330f;
		simulationFound = true;
		//const char texGroup[200][150] = {"../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_0.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_1.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_2.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_3.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_4.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_5.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_6.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_7.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_8.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_9.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_10.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_11.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_12.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_13.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_14.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_15.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_16.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_17.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_18.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_19.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_20.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_21.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_22.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_23.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_24.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_25.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_26.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_27.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_28.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_29.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_30.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_31.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_32.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_33.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_34.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_35.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_36.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_37.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_38.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_39.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_40.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_41.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_42.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_43.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_44.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_45.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_46.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_47.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_48.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_49.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_50.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_51.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_52.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_53.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_54.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_55.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_56.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_57.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_58.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_59.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_60.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_61.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_62.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_63.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_64.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_65.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_66.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_67.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_68.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_69.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_70.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_71.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_72.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_73.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_74.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_75.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_76.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_77.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_78.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_79.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_80.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_81.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_82.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_83.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_84.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_85.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_86.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_87.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_88.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_89.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_90.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_91.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_92.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_93.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_94.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_95.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_96.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_97.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_98.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_99.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_100.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_101.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_102.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_103.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_104.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_105.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_106.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_107.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_108.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_109.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_110.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_111.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_112.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_113.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_114.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_115.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_116.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_117.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_118.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_119.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_120.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_121.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_122.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_123.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_124.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_125.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_126.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_127.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_128.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_129.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_130.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_131.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_132.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_133.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_134.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_135.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_136.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_137.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_138.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_139.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_140.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_141.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_142.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_143.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_144.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_145.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_146.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_147.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_148.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_149.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_150.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_151.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_152.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_153.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_154.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_155.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_156.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_157.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_158.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_159.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_160.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_161.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_162.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_163.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_164.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_165.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_166.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_167.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_168.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_169.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_170.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_171.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_172.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_173.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_174.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_175.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_176.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_177.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_178.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_179.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_180.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_181.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_182.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_183.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_184.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_185.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_186.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_187.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_188.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_189.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_190.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_191.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_192.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_193.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_194.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_195.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_196.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_197.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_198.bmp", "../../../OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_199.bmp"};
		simulationFound = true;
	}
	else if (simulationToRun == "LGNReceptiveField") {
		//const char texGroup[200][150] = {"../../../OpenGL/Media/diffGaus/plot1/diffGaus_0.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_1.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_2.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_3.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_4.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_5.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_6.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_7.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_8.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_9.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_10.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_11.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_12.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_13.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_14.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_15.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_16.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_17.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_18.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_19.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_20.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_21.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_22.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_23.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_24.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_25.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_26.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_27.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_28.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_29.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_30.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_31.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_32.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_33.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_34.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_35.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_36.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_37.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_38.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_39.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_40.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_41.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_42.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_43.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_44.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_45.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_46.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_47.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_48.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_49.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_50.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_51.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_52.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_53.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_54.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_55.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_56.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_57.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_58.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_59.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_60.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_61.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_62.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_63.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_64.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_65.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_66.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_67.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_68.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_69.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_70.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_71.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_72.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_73.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_74.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_75.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_76.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_77.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_78.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_79.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_80.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_81.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_82.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_83.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_84.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_85.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_86.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_87.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_88.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_89.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_90.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_91.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_92.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_93.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_94.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_95.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_96.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_97.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_98.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_99.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_100.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_101.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_102.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_103.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_104.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_105.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_106.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_107.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_108.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_109.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_110.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_111.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_112.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_113.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_114.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_115.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_116.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_117.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_118.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_119.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_120.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_121.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_122.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_123.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_124.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_125.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_126.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_127.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_128.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_129.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_130.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_131.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_132.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_133.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_134.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_135.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_136.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_137.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_138.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_139.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_140.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_141.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_142.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_143.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_144.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_145.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_146.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_147.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_148.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_149.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_150.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_151.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_152.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_153.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_154.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_155.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_156.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_157.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_158.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_159.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_160.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_161.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_162.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_163.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_164.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_165.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_166.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_167.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_168.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_169.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_170.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_171.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_172.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_173.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_174.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_175.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_176.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_177.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_178.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_179.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_180.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_181.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_182.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_183.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_184.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_185.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_186.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_187.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_188.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_189.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_190.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_191.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_192.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_193.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_194.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_195.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_196.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_197.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_198.bmp", "../../../OpenGL/Media/diffGaus/plot1/diffGaus_199.bmp"};
		simulationFound = true;
	}
	else if (simulationToRun == "LGNSpaceTimeFixedY") {
		for (int i = 0; i < 200; i++) {
			//texGroup[i] = "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp";
			strcpy(texGroup[i], "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp");
		}
		//texGroup[200][150] =  = {"../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp", "../../../OpenGL/Media/diffGaus/diffGSTScaled.bmp"};

		image1 = texGroup[0];
		image2 = texGroup[1];
		startingDispMapImage = image2;
		endingDispMapImage = image1;
		//startingDispMap;
		//endingDispMap;

		// camera position mapper
		glTranslatef(-60.0f, -35.0f, -100.0f);//-150.0f);

		glRotatef(-_angle+10, -30.00f, 30.0f, 100.0f);

		sizeOfMesh = 40;//35;//10;//6;//50;

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
		_angle = -84.330f;
		simulationFound = true;
	}
	else {
		cerr<<"\n--Error--\nIncorrect simulation type specified\n--Error--\n\n";
	}

	if (simulationFound) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(400, 400);

		glutCreateWindow("Textures - videotutorialsrock.com");
		initWeights();
		findAnchorPoints();

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
