#include "ofMain.h"

#include "ofxJpegGlitch.h"

class ofApp : public ofBaseApp {
    ofxJpegGlitch jpeg;
    ofVideoGrabber grabber;
    bool bGrab = false;
    bool bAutoGlitch = true;
    int dataGlitchness;
public:
    void setup() {
        jpeg.setup(10, 20, 40);
        grabber.setup(1280, 720);
        ofSetVerticalSync(false);
        dataGlitchness = 10;
    }
    
    void update() {
        double d = ofGetElapsedTimeMicros();
        jpeg.setDataGlitchness(dataGlitchness);
        jpeg.setQNGlitchness(ofRandom(50, 10000));
        jpeg.setDHTGlitchness(0);
        jpeg.setJpegQuality(ofRandom(0, 4));
        grabber.update();
        if(bGrab && grabber.isFrameNew()) {
            ofPixels pix = grabber.getPixels();
            jpeg.setPixels(std::move(pix));
        }
        if(bAutoGlitch) {
            jpeg.glitch();
        }
    }
    
    void draw() {
        ofSetColor(255, 255, 255);
        jpeg.getImage().draw(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(255, 0, 0);
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);
    }
    
    void keyPressed(int key) {
        if(key == ' ') bGrab = true;
        if(key == 'a') bAutoGlitch ^= true;
        if(key == OF_KEY_RETURN) jpeg.glitch();
        if(key == 'g') bGrab = true;
        if(key == OF_KEY_LEFT) {
            dataGlitchness -= pow(10, int(std::log10(dataGlitchness)));
            if(dataGlitchness < 1) dataGlitchness = 1;
            ofLogNotice() << dataGlitchness;
        }
        if(key == OF_KEY_RIGHT) {
            dataGlitchness += pow(10, int(std::log10(dataGlitchness)));;
            ofLogNotice() << dataGlitchness;
        }
    }
    
    void keyReleased(int key) {
        if(key == ' ') bGrab = false;
    }
};

int main() {
    ofSetupOpenGL(1920, 1080, OF_WINDOW);
    ofRunApp(new ofApp());
}
