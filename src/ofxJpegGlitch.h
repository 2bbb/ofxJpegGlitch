//
//  ofxJpegGlitch.h
//
//  Created by ISHII 2bit
//

#pragma once

#include "JpegConstant.h"

#include "ofFileUtils.h"
#include "ofImage.h"
#include "ofThread.h"
#include "ofThreadChannel.h"

class ofxJpegGlitch {
public:
    ofxJpegGlitch()
    : dataBlock(16384)
    , qnBlock(2048)
    , dhtBlock(2048) {};
    virtual ~ofxJpegGlitch() {
        bClosed = true;
        needEncodingPixels.close();
        waitingBuffers.close();
        processedImages.close();
    }
    void setup(int data = 16384, int qn = 2048, int dht = 2048);
    void setJpegBuffer(const ofBuffer &buf);
    void setJpegBuffer(ofBuffer &&buf);
    void setImage(const ofPixels &pix);
    void setImage(ofPixels &&pix);
    void setImage(const ofImage &image);
    void setImage(ofImage &&image);
    void setPixels(const ofPixels &pix);
    void setPixels(ofPixels &&pix);
    
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
    
    bool glitch();
    bool isGlitchLoaded() const { return bImageLoaded; }
    const ofImage &getImage(int timeout = 60);
    bool saveImage() const;
    bool saveImage(const std::string &fileName) const;
    
    const ofBuffer &getGlitchedJpegBuffer() const {
        return encoded_buffer;
    }
private:
    MarkerType calcMarkerType(unsigned char *bytes, int cur) const;
    int calcLength(unsigned char *bytes, int cur) const;
    void glitch_impl();
    void encode();
    
    ofPixels pix;
    ofThreadChannel<ofPixels> needEncodingPixels;
    
    ofBuffer encoded_buffer;
    ofThreadChannel<ofBuffer> waitingBuffers;
    ofThreadChannel<ofImage> processedImages;
    std::atomic<bool> bClosed{false};
    
    ofImage image;
    
    int dataBlock;
    int qnBlock;
    int dhtBlock;
    int jpegQuality;
    
    bool bImageLoaded;
};
