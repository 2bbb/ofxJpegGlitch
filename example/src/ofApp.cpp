#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    jpeg.setup(20, 40, 80);
    grabber.initGrabber(640, 480);
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    if(grabber.isFrameNew()) {
        jpeg.setPixels(grabber.getPixelsRef());
        jpeg.glitch();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBaseDraws *baseDraw;
    if(jpeg.getImage().isAllocated()) {
        baseDraw = &(jpeg.getImage());
    } else {
        baseDraw = &grabber;
    }
    baseDraw->draw(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
