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
const char texGroup[200][150] = {"/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_0.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_1.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_2.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_3.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_4.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_5.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_6.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_7.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_8.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_9.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_10.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_11.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_12.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_13.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_14.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_15.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_16.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_17.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_18.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_19.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_20.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_21.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_22.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_23.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_24.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_25.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_26.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_27.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_28.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_29.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_30.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_31.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_32.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_33.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_34.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_35.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_36.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_37.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_38.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_39.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_40.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_41.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_42.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_43.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_44.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_45.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_46.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_47.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_48.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_49.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_50.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_51.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_52.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_53.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_54.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_55.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_56.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_57.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_58.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_59.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_60.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_61.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_62.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_63.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_64.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_65.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_66.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_67.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_68.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_69.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_70.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_71.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_72.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_73.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_74.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_75.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_76.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_77.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_78.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_79.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_80.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_81.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_82.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_83.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_84.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_85.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_86.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_87.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_88.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_89.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_90.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_91.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_92.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_93.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_94.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_95.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_96.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_97.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_98.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_99.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_100.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_101.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_102.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_103.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_104.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_105.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_106.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_107.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_108.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_109.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_110.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_111.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_112.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_113.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_114.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_115.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_116.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_117.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_118.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_119.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_120.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_121.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_122.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_123.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_124.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_125.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_126.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_127.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_128.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_129.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_130.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_131.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_132.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_133.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_134.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_135.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_136.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_137.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_138.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_139.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_140.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_141.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_142.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_143.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_144.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_145.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_146.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_147.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_148.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_149.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_150.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_151.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_152.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_153.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_154.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_155.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_156.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_157.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_158.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_159.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_160.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_161.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_162.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_163.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_164.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_165.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_166.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_167.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_168.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_169.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_170.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_171.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_172.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_173.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_174.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_175.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_176.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_177.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_178.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_179.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_180.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_181.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_182.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_183.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_184.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_185.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_186.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_187.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_188.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_189.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_190.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_191.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_192.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_193.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_194.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_195.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_196.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_197.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_198.bmp", "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_199.bmp"};
//String image1 = "/home/nmsutton/Documents/Software/OpenGL/Media/gaborFilter1.bmp";//"/home/nmsutton/Documents/Software/OpenGL/Media/GeneralProcessed90_512.bmp";
//String image2 = "/home/nmsutton/Documents/Software/OpenGL/Media/gaborFilter2.bmp";//"/home/nmsutton/Documents/Software/OpenGL/Media/GeneralProcessed90UpSft_512.bmp";
String image1 = texGroup[0];
String image2 = texGroup[1];
String startingDispMapImage = image2;
String endingDispMapImage = image1;
Mat startingDispMap;
Mat endingDispMap;
String anchorImage1 = "/home/nmsutton/Documents/Software/OpenGL/Media/gaborAnchorImageExtra.bmp";
String anchorImage2 = "/home/nmsutton/Documents/Software/OpenGL/Media/gaborAnchorImageExtra.bmp";
String startingDispMapAnchorImage = anchorImage2;
String endingDispMapAnchorImage = anchorImage1;
const int numberOfAnchors = 1;
Mat startingDispMapAnchor;
Mat endingDispMapAnchor;
double timeInMs = 0;

const int incrementValue = 1;

// *2 is due to 2 rectangle verticies for each x and y axis used for the later Z level mapping.
double verticiesInRectangle = 2;
const double sizeOfMesh = 20;//10;//6;//50;
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
double depthScalingFactor = .7;//.025;//.3;//0.1;
const int xMaxAmount = ceil(sizeOfMesh*(1/incrementValue))*2, yMaxAmount = ceil(sizeOfMesh*(1/incrementValue))*2;
double startingVerZLevels[yMaxAmount][xMaxAmount] = {0};
double endingVerZLevels[yMaxAmount][xMaxAmount] = {0};
double animationDelay = 50.0;
double transitionTime = 200.0;//400.0;//200.0;
struct vertsAndTextures { double ULVerInst[3]; double URVerInst[3]; double BLVerInst[3]; double BRVerInst[3];
double ULTexInst[2]; double URTexInst[2]; double BLTexInst[2]; double BRTexInst[2];};
vertsAndTextures vAT3;
/*double startingDispMapAnchorPoint1[2] = {0,0};
double startingDispMapAnchorPoint2[2] = {0,0};
double endingDispMapAnchorPoint1[2] = {0,0};
double endingDispMapAnchorPoint2[2] = {0,0};*/

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
float texYIncrement = (1.00f/sizeOfMesh2)/texYScaling;

float initVerXUL = -2.50f;
float initVerXBR = -2.50f;
float initVerXUR = initVerXUL+verXIncrement;
float initVerXBL = initVerXBR+verXIncrement;
float initTexXUL = 0.10f;//-0.05f;//0.0f;//
float initTexXBR = 0.10f;//-0.05f;//-0.10f;
float initTexXUR = initTexXUL+texXIncrement;
float initTexXBL = initTexXBR+texXIncrement;
float initTexYBR = 0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYBR2 = 0.9;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYUL = initTexYBR-texYIncrement;
float initTexYBL = 0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYBL2 = 0.9f;//0.64f;//1.0f;//1.10f;0.64f;//
float initTexYUR = initTexYBL-texYIncrement;
float initVerZUL = -4.50f+initalZ;
float initVerZUR = -4.50f+initalZ;//initVerZUL+verZIncrement;
float initVerZBL = -4.50f+initalZ;
float initVerZBR = -4.50f+initalZ;

float texYWeight = 1.0;
float texXWeight = 1.0;
bool changeTex = false;

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

	texture[(int)timeInMs] = loadBMP(texGroup[(int)timeInMs]);//LoadTextureRAW( “textures/1.raw”, 256, 256 );

	/*String inputTexture = "/home/nmsutton/Documents/Software/OpenGL/DisplacementMapper/ImagePreprocessor/media/gaborFilterDispMap_";
	stringstream ss;
	ss << inputTexture;
	ss << timeInMs;
	ss << ".bmp";
	texGroup[(int)timeInMs] = ss.str();
	const char *test2[50];
	const char test3[50];
	*test2 = &test3;*/

	//Image* image = loadBMP("/home/nmsutton/Documents/Software/OpenGL/Media/ColorTex.bmp");//loadBMP("/home/nmsutton/Documents/Software/OpenGL/Media/gaborFilter1.bmp");//loadBMP("/home/nmsutton/Documents/Software/OpenGL/Media/generalImg3.bmp");
	//Image* image = loadBMP(texGroup[(int)timeInMs]);//loadBMP(ss.str());//loadBMP("/home/nmsutton/Documents/Software/OpenGL/Media/gaborFilter1.bmp");//loadBMP("/home/nmsutton/Documents/Software/OpenGL/Media/generalImg3.bmp");
	Image* image = loadBMP(texGroup[(int)timeInMs]);//loadBMP(ss.str());//loadBMP("/home/nmsutton/Documents/Software/OpenGL/Media/gaborFilter1.bmp");//loadBMP("/home/nmsutton/Documents/Software/OpenGL/Media/generalImg3.bmp");
	//_textureId = loadTexture(image);
	//_textureId = loadTexture(texture[(int)timeInMs]);
	delete image;
	//glBindTexture( GL_TEXTURE_2D, texture[(int)frame] );
	//LoadTexture2(texGroup[(int)timeInMs], 512, 512);
	//glBindTexture( GL_TEXTURE_2D, LoadTexture2(texGroup[(int)timeInMs], 512, 512) );
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

void extractAnchorPoint(Mat anchorPointImage, String anchorPointPosition) {
	//cout<<"search started\n";
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
					cout<<"\n\nstart anchor found\t";cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
				}
				else if ((anchorPointPosition=="start") & (anchorFound1 == true) & numberOfAnchors > 1){
					startingDispMapAnchorPoint[1][0]=y;
					startingDispMapAnchorPoint[1][1]=x;
					cout<<"\n\nstart anchor 2 found\t";cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
				}
				else if ((anchorPointPosition=="end") & (anchorFound1 == false)) {
					anchorFound1 = true;
					endingDispMapAnchorPoint[0][0]=y;
					endingDispMapAnchorPoint[0][1]=x;
					cout<<"\n\nend anchor found\t";cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
				}
				else if ((anchorPointPosition=="end") & (anchorFound1 == true) & numberOfAnchors > 1) {
					endingDispMapAnchorPoint[1][0]=y;
					endingDispMapAnchorPoint[1][1]=x;
					cout<<"\n\nend anchor 2 found\t";cout<<anchorPointImage.at<Vec3b>(y,x);cout<<"\t";cout<<y;cout<<" ";cout<<x;cout<<"\n";
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
	/*double startY = startingDispMapAnchorPoint1[0];
	double startX = startingDispMapAnchorPoint1[1];
	double endY = endingDispMapAnchorPoint1[0];
	double endX = endingDispMapAnchorPoint1[1];*/
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
		//distance = lockedDistance;
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
	//double wobblePastMax = 0.8;
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

	//cout<<"amountTransitioned2 ";cout<<amountTransitioned2;cout<<" wobbleForwardOrBack ";cout<<wobbleForwardOrBack;cout<<" numberOfWobbles ";cout<<numberOfWobbles;cout<<"\n";

	// Difference with starting and ending weights
	double startDispMapWeights = 1.0;
	double endDispMapWeights = (endZ*depthScalingFactor)/(startZ*depthScalingFactor);
	// Position is based on transistion degree including distance restraint limit
	double newWeight = ((distanceRestraint*learningRestraint*startDispMapWeights)*(1-amountTransitioned)) +
			((distanceRestraint*learningRestraint*endDispMapWeights)*(amountTransitioned));
	/*double newTexY = ((startY)*(1-amountTransitioned)) +
			((endY)*(amountTransitioned));*/
	// normalize tex map with
	double yTexScalingFactor = 2.62649350649;//-2.1484375;
	double texTransDelay = timeInMs*(1/(animationDelay*1.5));
	//if (changeTex==false) {texTransDelay = 1-texTransDelay;}
	if (texTransDelay > 1) {texTransDelay = 1;}
	//changeTex
	double newTexY;
	//double newTexY = (1.0*(1-amountTransitioned))+((((endY-startY)/imageYPixels)*yTexScalingFactor)*amountTransitioned);//(1-amountTransitioned));


	//double newTexY = (1.0*(1-texTransDelay))+((((((endY-startY)/imageYPixels)*yTexScalingFactor) / initTexYBR))*texTransDelay);//(1-amountTransitioned));  //(((endY-startY)/imageYPixels)*yTexScalingFactor)
	//if (changeTex==true) {newTexY = (1.0*(texTransDelay))+((((((endY-startY)/imageYPixels)*yTexScalingFactor) / initTexYBR))*(1-texTransDelay));}

	//if (changeTex==false) {newTexY = (.78 / initTexYBR);}
	//else {newTexY = 1.0;}

	//startY
	/*if (timeInMs == 2) {
		cout<<newWeight;cout<<" ";
	}*/
	if (is_nan(newWeight)==true) {newWeight = 1.0;}
	if (verPositionForWeights == "BR") {
		weightsBR[y][x] += newWeight;
		//initTexYBR = (newTexY*.1);
		//initTexYBR = .64f;//(newTexY*.1);
		if (anchorForTexUpdate == true) {
			/*if (changeTex == true) {initTexYBR = (initTexYBR2*(1-texTransDelay))+((initTexYBR2*(1.04 / initTexYBR2))*texTransDelay);
			initTexYBL = (initTexYBR2*(1-texTransDelay))+((initTexYBL2*(1.04 / initTexYBL2))*texTransDelay);
			initTexYUL = initTexYBR-texYIncrement;initTexYUR = initTexYBL-texYIncrement;}

			if (changeTex == false) {initTexYBR = (initTexYBR2*(texTransDelay))+((initTexYBR2*(1.04 / initTexYBR2))*(1-texTransDelay));
			initTexYBL = (initTexYBR2*(texTransDelay))+((initTexYBL2*(1.04 / initTexYBL2))*(1-texTransDelay));
			initTexYUL = initTexYBR-texYIncrement;initTexYUR = initTexYBL-texYIncrement;}*/

			//cout<<changeTex;cout<<"\n";
		}
	}
	else if (verPositionForWeights == "BL") {
		weightsBL[y][x+1] += newWeight;
		//initTexYBL = .64f;//(newTexY*.1);
		//texYWeight = (.64 / initTexYBR);
	}
	else if (verPositionForWeights == "UL") {
		weightsUL[y+1][x] += newWeight;
		//float initTexYUL = initTexYBR-texYIncrement;
		//texYWeight = (.64 / initTexYBR);
	}
	else if (verPositionForWeights == "UR") {
		weightsUR[y+1][x+1] += newWeight;
		//float initTexYUR = initTexYBL-texYIncrement;
		//texYWeight = (.64 / initTexYBR);
	}

	/*if ((y==(15))&(x==15)&timeInMs == 15) {
		//cout<<"weightsUL[y+1][x]\t";cout<<weightsUL[y+1][x];cout<<"\ty x: ";cout<<y;cout<<" ";cout<<x;cout<<"\n";
		cout<<"\n";
		for(int y3=0;y3<yMaxAmount;y3++)
		{
			for (int x3=0;x3<xMaxAmount;x3++)
			{
				cout<<weightsUL[y][x];cout<<" ";
			}
			cout<<"\n";
		}
		cout<<"\n";
	}*/
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
		///cout<<"weightsBR[5][5]\t";cout<<weightsBR[5][5];cout<<"\n";
		//cout<<"weightsBR[y][x]\t";cout<<weightsBR[y][x];cout<<"\ty x: ";cout<<y;cout<<" ";cout<<x;cout<<"\n";
		//((startingVerZLevels[y][x]*depthScalingFactor)*(1.0-((1.0/animationDelay)*timeInMs))) + ((endingVerZLevels[y][x]*depthScalingFactor)*((1.0/animationDelay)*timeInMs));//verZLevels[y][x] = meshVec_0_0;
		//cout<<"timeInMs:\t";cout<<timeInMs;cout<<"\t(1-(1/50*timeInMs))\t";cout<<(double)(1.0-((1.0/50.0)*timeInMs));cout << "\tvAT3.BRVerInst[2]:\t";cout<<vAT3.BRVerInst[2];cout<<"\n";
	}
	if ((x > 0) & (x < (maxXSize-borderToCrop))) {
		/*if ((abs((((double)x/(double)xMaxAmount) * imageXPixels) - endingDispMapAnchorPoint1[1]) <= range) & (abs((((double)y/(double)yMaxAmount) * imageYPixels) - endingDispMapAnchorPoint1[0]) <= range)) {
		//if (true) {
			//weightsBL[y][x+1] = (((startingVerZLevels[y][x+1]*depthScalingFactor)*(1.0-((1.0/animationDelay)*timeInMs))) + ((endingVerZLevels[y][x+1]*depthScalingFactor)*((1.0/animationDelay)*timeInMs)))/(startingVerZLevels[y][x+1]*depthScalingFactor);
		}*/
		weightsBL[y][x+1] = 0;
		for (int anchorIndex = 0;anchorIndex < numberOfAnchors; anchorIndex++) {
			calculateWeightChange("BL", true, startingDispMapAnchorPoint[anchorIndex][0], startingDispMapAnchorPoint[anchorIndex][1],
					startingVerZLevels[y][x+1], endingDispMapAnchorPoint[anchorIndex][0], endingDispMapAnchorPoint[anchorIndex][1], endingVerZLevels[y][x+1]);
		}
		vAT3.BLVerInst[2] = (startingVerZLevels[y][x+1]*depthScalingFactor)*weightsBL[y][x+1];
		//((startingVerZLevels[y][x+1]*depthScalingFactor)*(1.0-((1.0/animationDelay)*timeInMs))) + ((endingVerZLevels[y][x+1]*depthScalingFactor)*((1.0/animationDelay)*timeInMs));//verZLevels[y][x+1] = meshVec_0_0;
	}
	if (y > 0 & y < maxYSize-borderToCrop) {
		//if ((abs((((double)x/(double)xMaxAmount) * imageXPixels) - endingDispMapAnchorPoint1[1]) <= range) & (abs((((double)y/(double)yMaxAmount) * imageYPixels) - endingDispMapAnchorPoint1[0]) <= range)) {
		/*if (true) {
			weightsUL[y+1][x] = (((startingVerZLevels[y+1][x]*depthScalingFactor)*(1.0-((1.0/animationDelay)*timeInMs))) + ((endingVerZLevels[y+1][x]*depthScalingFactor)*((1.0/animationDelay)*timeInMs)))/(startingVerZLevels[y+1][x]*depthScalingFactor);
		}*/
		weightsUL[y+1][x] = 0;
		for (int anchorIndex = 0;anchorIndex < numberOfAnchors; anchorIndex++) {
			calculateWeightChange("UL", true, startingDispMapAnchorPoint[anchorIndex][0], startingDispMapAnchorPoint[anchorIndex][1],
					startingVerZLevels[y+1][x], endingDispMapAnchorPoint[anchorIndex][0], endingDispMapAnchorPoint[anchorIndex][1], endingVerZLevels[y+1][x]);
		}
		vAT3.ULVerInst[2] = (startingVerZLevels[y+1][x]*depthScalingFactor)*weightsUL[y+1][x];
		//if (y > (yMaxAmount-15) & x == 15 & timeInMs <= 6) {

		//((startingVerZLevels[y+1][x]*depthScalingFactor)*(1.0-((1.0/animationDelay)*timeInMs))) + ((endingVerZLevels[y+1][x]*depthScalingFactor)*((1.0/animationDelay)*timeInMs));// = meshVec_0_0;
	}
	if ((y < maxYSize-borderToCrop) & (x < (maxXSize-borderToCrop))) {
		/*if ((abs((((double)x/(double)xMaxAmount) * imageXPixels) - endingDispMapAnchorPoint1[1]) <= range) & (abs((((double)y/(double)yMaxAmount) * imageYPixels) - endingDispMapAnchorPoint1[0]) <= range)) {
		//if (true) {
			//weightsUR[y+1][x+1] = (((startingVerZLevels[y+1][x+1]*depthScalingFactor)*(1.0-((1.0/animationDelay)*timeInMs))) + ((endingVerZLevels[y+1][x+1]*depthScalingFactor)*((1.0/animationDelay)*timeInMs)))/(startingVerZLevels[y+1][x+1]*depthScalingFactor);
		}*/
		weightsUR[y+1][x+1] = 0;
		for (int anchorIndex = 0;anchorIndex < numberOfAnchors; anchorIndex++) {
			calculateWeightChange("UR", true, startingDispMapAnchorPoint[anchorIndex][0], startingDispMapAnchorPoint[anchorIndex][1],
					startingVerZLevels[y+1][x+1], endingDispMapAnchorPoint[anchorIndex][0], endingDispMapAnchorPoint[anchorIndex][1], endingVerZLevels[y+1][x+1]);
		}
		vAT3.URVerInst[2] = (startingVerZLevels[y+1][x+1]*depthScalingFactor)*weightsUR[y+1][x+1];
		//((startingVerZLevels[y+1][x+1]*depthScalingFactor)*(1.0-((1.0/animationDelay)*timeInMs))) + ((endingVerZLevels[y+1][x+1]*depthScalingFactor)*((1.0/animationDelay)*timeInMs));// = meshVec_0_0;
	}
}

void createMeshOfRect() {
	//if (timeInMs == 15) {
	/*initTexYBR = initTexYBR*texYWeight;//1.0f;//1.10f;0.64f;//
	initTexYUL = initTexYBR-texYIncrement*texYWeight;
	initTexYBL = initTexYBR*texYWeight;//1.0f;//1.10f;0.64f;//
	initTexYUR = initTexYBL-texYIncrement*texYWeight;*/
	//}

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

		//if (x==0 & y==0) {createMesh(vAT3);}

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
			//cout<<"y greater";cout<<"\n";
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
				//cout<<"x greater";cout<<"\n";
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
	//glTranslatef(-30.0f, 1.0f, -60.0f);//-150.0f);
	glTranslatef(-30.0f, 11.0f, -140.0f);//-150.0f);

	//GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat ambientLight[] = {200.2f, 200.2f, 200.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	//glRotatef(-_angle, -0.20f, 1.0f, 0.0f);
	glRotatef(-_angle, -35.00f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, _textureId);
	glBindTexture( GL_TEXTURE_2D, LoadTexture2(texGroup[(int)timeInMs], 512, 512) );

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
	/*_angle += 1.0f;//0.1f;//0.330f;
	if (_angle > 50) {
		_angle -= 100;
	}*/
	if (timeInMs == transitionTime) {//25) {
		/*if (startingDispMapImage == image1) {
			startingDispMapImage = image2;
			endingDispMapImage = image1;
			cout << "switched\n";
			changeTex = true;
		}
		else if (startingDispMapImage == image2) {
			startingDispMapImage = image1;
			endingDispMapImage = image2;
			cout << "switched back\n";
			changeTex = false;
		}*/
		timeInMs = 0;
	}
		//if (startingDispMapImage == texGroup[(int)timeInMs]) {
			startingDispMapImage = texGroup[(int)timeInMs];
			if (timeInMs < (transitionTime-1)) {
			endingDispMapImage = texGroup[(int)timeInMs+1];
			}
			else {
				endingDispMapImage = texGroup[0];
			}

			changeTex = true;
		//}
/*		timeInMs = 0;
	}*/
	cout<<timeInMs;cout<<"\n";
	glutPostRedisplay();
	//glutTimerFunc(25, update, 0);
	glutTimerFunc(20, update, 0);
}

int main(int argc, char** argv) {
	//timeInMs = 50;
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
	_angle = -60.330f;//-45.330f;//_angle = -45.330f;//25.330f;_angle = 0.0f;//
	glutTimerFunc(20, update, 0);

	// try
	// http://stackoverflow.com/questions/19070333/saving-the-opengl-context-as-a-video-output

	glutMainLoop();
	return 0;
}









