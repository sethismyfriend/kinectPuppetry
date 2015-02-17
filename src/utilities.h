#ifndef telekinect_depth_composite_network_utilities_h
#define telekinect_depth_composite_network_utilities_h

#include "ofxOpenCv.h"


void makeRGBAComposite(ofxCvColorImage* _colorImg, ofxCvGrayscaleImage* _maskImg, ofImage* _composite, int _w, int _h, bool _fillBlack=false);
void makeRGBAComposite_sh(ofxCvColorImage* _colorImg, ofxCvGrayscaleImage* _maskImg, ofImage* _composite, int _w, int _h, bool _fillBlack=false);
void makeRGBAComposite(unsigned char * colorImg, unsigned char * maskImg, ofImage& _composite, int _w, int _h, bool _fillBlack=false);
void makeRGBAComposite_sh(unsigned char * colorImg, unsigned char * maskImg, ofImage& _composite, int _w, int _h, bool _fillBlack=false);
float cvAvgMinMax(ofxCvGrayscaleImage* _grayImg, ofxCvGrayscaleImage* _blackMask, int _min, int _max, int _w, int _h);

#endif
