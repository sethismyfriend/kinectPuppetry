#include <iostream>
#include "utilities.h"

//GENERIC Function to create an RGBA Image from a color image + mask. Must be same number of pixels. (can be used elsewhere)
//--------------------------------------------------------------
void makeRGBAComposite(ofxCvColorImage* _colorImg, ofxCvGrayscaleImage* _maskImg, ofImage* _composite, int _w, int _h, bool _fillBlack) {
    unsigned char * colorImg = _colorImg->getPixels(); // 3 channel image
    unsigned char * maskImg = _maskImg->getPixels(); // 1 channel image
    _composite->setImageType(OF_IMAGE_COLOR_ALPHA);
    unsigned char * composite = _composite->getPixels(); // 4 channel image
    int limit = _w*_h;
    int RGBAval;
    int colorVal;
    int pixel;
    
    for(int i = 0; i < limit; i++, maskImg++) {
        for(int k=0; k<4; k++) { //each of the 4 channels in the image
            //translate values
            RGBAval = i*4 + k;
            colorVal = i*3 + k;
            
            //filter channels
            if(k == 3) {
                //alpha channel
                pixel = *maskImg;
            } else {	
                if(*maskImg < 1 && _fillBlack){
                    pixel = 0; //make it black if the mask is black. 
                } else {
                    pixel = colorImg[colorVal];
                }
            }
            
            *(composite+RGBAval) = pixel;
        }
    } 
}




//GENERIC Function to create an RGBA Image from a color image + mask. Must be same number of pixels. (can be used elsewhere) 
//--------------------------------------------------------------
void makeRGBAComposite_sh(ofxCvColorImage* _colorImg, ofxCvGrayscaleImage* _maskImg, ofImage* _composite, int _w, int _h, bool _fillBlack) {
	//printf("x: %d, y %d, w %d, h %d \n", x, y, w, h);
	unsigned char * colorPx = _colorImg->getPixels(); // 3 channel image
	unsigned char * maskPx = _maskImg->getPixels(); // 1 channel image
	unsigned char alphaImg[_w*_h*4]; // 4 channel image
	
	for(int i=0; i<_w; i++) { //horizontal row
		for(int j=0; j<_h; j++) { 
			for(int k=0; k<4; k++) { //each of the 4 channels in the image
				//translate values
				int loc = i+(j*_w);
				int RGBAval = loc*4 + k;
				int colorVal = loc*3 + k;
				//filter channels
				if(k == 3) {
					//alpha channel
					alphaImg[RGBAval] = maskPx[loc];
				} else {	
					if((maskPx[loc] < 1) && (_fillBlack)){
						alphaImg[RGBAval] = 0;  //make it black if the mask is black. 	
					} else {
						alphaImg[RGBAval] = colorPx[colorVal];
					}
				}
			}
		}
	} 
	_composite->setFromPixels(alphaImg,_w,_h,OF_IMAGE_COLOR_ALPHA,true);
}



//this is a rewrite of the function using pointers that takes 1/2 the processing time (replace referance with a pointer)
void makeRGBAComposite(unsigned char * colorImg, unsigned char * maskImg, ofImage& _composite, int _w, int _h, bool _fillBlack) {
    //unsigned char * colorImg = _colorImg->getPixels(); // 3 channel image
    //unsigned char * maskImg = _maskImg->getPixels(); // 1 channel image
    _composite.setImageType(OF_IMAGE_COLOR_ALPHA);
    unsigned char * composite = _composite.getPixels(); // 4 channel image
    int limit = _w*_h;
    int RGBAval;
    int colorVal;
    int pixel;
    
    for(int i = 0; i < limit; i++, maskImg++) {
        for(int k=0; k<4; k++) { //each of the 4 channels in the image
            //translate values
            RGBAval = i*4 + k;
            colorVal = i*3 + k;
            
            //filter channels
            if(k == 3) {
                //alpha channel
                pixel = *maskImg;
            } else {
                if(*maskImg < 1 && _fillBlack){
                    pixel = 0; //make it black if the mask is black.
                } else {
                    pixel = colorImg[colorVal];
                }
            }
            
            *(composite+RGBAval) = pixel;
        }
    }
}

//This is the first (slower) version of the function I wrote that takes longer because it uses SetFromPixels to copy pixels between images.
//--------------------------------------------------------------
void makeRGBAComposite_sh(unsigned char * colorPx, unsigned char * maskPx, ofImage& _composite, int _w, int _h, bool _fillBlack) {
	//printf("x: %d, y %d, w %d, h %d \n", x, y, w, h);
	//unsigned char * colorPx = _colorImg->getPixels(); // 3 channel image
	//unsigned char * maskPx = _maskImg->getPixels(); // 1 channel image
	unsigned char alphaImg[_w*_h*4]; // 4 channel image
	
	for(int i=0; i<_w; i++) { //horizontal row
		for(int j=0; j<_h; j++) {
			for(int k=0; k<4; k++) { //each of the 4 channels in the image
				//translate values
				int loc = i+(j*_w);
				int RGBAval = loc*4 + k;
				int colorVal = loc*3 + k;
				//filter channels
				if(k == 3) {
					//alpha channel
					alphaImg[RGBAval] = maskPx[loc];
				} else {
					if((maskPx[loc] < 1) && (_fillBlack)){
						alphaImg[RGBAval] = 0;  //make it black if the mask is black.
					} else {
						alphaImg[RGBAval] = colorPx[colorVal];
					}
				}
			}
		}
	}
	_composite.setFromPixels(alphaImg,_w,_h,OF_IMAGE_COLOR_ALPHA,true);
}
