//
//  ofxJpegGlitch.h
//
//  Created by ISHII 2bit
//

/*
 ==========================
 = ONLY TESTED ON MAC OSX =
 ==========================
 
 if you want to use ofxTurboJpeg, then insert
    #define USE_OFXTURBOJPEG
 before
    #include "ofxJpegGlitch.h"
 and, you must use the satoruhiga ver. of ofxTurboJpeg.
 download from: https://github.com/satoruhiga/ofxTurboJpeg
 */

#define USE_OFXTURBOJPEG 0

#ifndef __ofxJpegGlitch__
#define __ofxJpegGlitch__

#include "ofMain.h"
#include "JpegConstant.h"

#if USE_OFXTURBOJPEG
#include "ofxTurboJpeg.h"
#endif


class ofxJpegGlitch {
public:
    ofxJpegGlitch() {
        dataBlock = 16384;
        qnBlock  = 2048;
        dhtBlock  = 2048;
        
#if USE_OFXTURBOJPEG
        ofLogNotice("ofxJpegGlitch") << "now use ofxTurboJpeg" << endl;
#endif
    };
    void setup(int data = 16384, int qn = 2048, int dht = 2048);
    void setJpegBuffer(ofBuffer &buf);
    void setImage(ofPixelsRef pix);
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
    bool isGlitchLoaded() const { return bImageLoaded; }
    ofImage &getImage();
    bool forceLoadImage();
    void saveImage();
    void saveImage(string fileName);
private:
    MarkerType calcMarkerType(unsigned char *bytes, int cur);
    int calcLength(unsigned char *bytes, int cur);
    
    ofBuffer buf;
    
#if USE_OFXTURBOJPEG
    ofxTurboJpeg turbo;
#endif
    ofImage image;
    
    int dataBlock;
    int qnBlock;
    int dhtBlock;
    int jpegQuality;
    
    bool bImageLoaded;
};

#endif /* defined(__ofxJpegGlitch__) */
