//
//  ofxJpegGlitch.h
//
//  Created by ISHII 2bit
//

#ifndef __ofxJpegGlitch__
#define __ofxJpegGlitch__

#include "ofMain.h"
#include "JpegConstant.h"

class ofxJpegGlitch {
public:
    ofxJpegGlitch() {
        dataBlock = 16384;
        qnBlock  = 2048;
        dhtBlock  = 2048;
    };
    void setup(int data = 16384, int qn = 2048, int dht = 2048);
    void setJpegBuffer(ofBuffer &buf);
    void setImage(ofImage &image);
    void setPixels(ofPixelsRef pix);
    
    void setDataGlitchness(int glitchness) {
        if(glitchness < 0) return;
        dataBlock = glitchness;
    }
    
    void setQNGlitchness(int glitchness) {
        if(glitchness < 0) return;
        qnBlock = glitchness;
    }
    
    void setDHTGlitchness(int glitchness) {
        if(glitchness < 0) return;
        dhtBlock = glitchness;
    }
    
    void setJpegQuality(int quality) {
        if(4 < quality) quality = 4;
        if(quality < 0) quality = 0;
        jpegQuality = quality;
    }
    
    void glitch();
    ofImage &getImage();
    void saveImage();
    void saveImage(string fileName);
private:
    MarkerType calcMarkerType(unsigned char *bytes, int cur);
    int calcLength(unsigned char *bytes, int cur);
    
    ofBuffer buf;
    
    ofImage image;
    
    int dataBlock;
    int qnBlock;
    int dhtBlock;
    int jpegQuality;
    
    bool bImageLoaded;
};

#endif /* defined(__ofxJpegGlitch__) */
