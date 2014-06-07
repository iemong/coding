#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(63, 63, 63);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(6);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < particles.size(); i++) {
        particles[i].resetForce();
        particles[i].updateForce();
        particles[i].addForce(ofVec2f(0, 0.001));
        particles[i].updatePos();
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < particles.size(); i++) {
        particles[i].draw();
    }
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("particle num = " + ofToString(particles.size()), 10, 15);
    ofDrawBitmapString("fps = " +  ofToString(ofGetFrameRate()), 10, 30);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
    }
    if (key == 'c') {
        particles.clear();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for (int i = 0; i < 10; i++) {
        ofVec2f pos = ofVec2f(x, y);
        float length = ofRandom(1);
        float angle = ofRandom(PI * 2);
        ofVec2f vel = ofVec2f(cos(angle) * length, sin(angle) * length);
        
        Particle p;
        p.setup(pos, vel);
        p.radius = 2;
        p.friction = 0.002;
        particles.push_back(p);
    }
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
