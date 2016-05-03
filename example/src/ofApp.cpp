#include "ofMain.h"

#include "ofxJpegGlitch.h"

class ofApp : public ofBaseApp {
    ofxJpegGlitch jpeg;
    ofVideoGrabber grabber;
    bool bGrab{false};
public:
    void setup() {
        jpeg.setup(10, 20, 40);
        grabber.setup(1920, 1080);
    }
    
    void update() {
        jpeg.setDataGlitchness(ofRandom(10, 20));
        jpeg.setQNGlitchness(ofRandom(10, 20));
        jpeg.setDHTGlitchness(ofRandom(10, 20));
        jpeg.setJpegQuality(ofRandom(10, 20));
        grabber.update();
        if(bGrab && grabber.isFrameNew()) {
            ofPixels pix = grabber.getPixels();
            jpeg.setPixels(std::move(pix));
        }
        jpeg.glitch();
        ofSetWindowTitle(ofToString(ofGetFrameRate()));
    }
    
    void draw() {
        ofSetColor(255, 255, 255);
        jpeg.getImage().draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    void keyPressed(int key) {
        if(key == ' ') bGrab = true;
    }
    
    void keyReleased(int key) {
        if(key == ' ') bGrab = false;
    }
};

int main() {
    ofSetupOpenGL(1920, 1080, OF_WINDOW);
    ofRunApp(new ofApp());
}
