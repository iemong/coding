#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(36);
    
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
    ofBeginShape();

    for (int i = 0; i < particles.size(); i++) {
        ofFill();
        particles[i].draw();
        ofPoint pos = ofPoint(particles[i].position.x, particles[i].position.y, particles[i].position.z);
        ofSetColor(155, 250, 205, 50);
        ofNoFill();
        ofCurveVertex(pos);
    }
    ofEndShape();
    ofSetColor(255, 255, 255);
    //ofDrawBitmapString("particle num = " + ofToString(particles.size()), 10, 15);
    //ofDrawBitmapString("fps = " +  ofToString(ofGetFrameRate()), 10, 30);
    
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
        ofVec3f pos = ofVec3f(x, y, 0);
        float length = ofRandom(1);
        float angle = ofRandom(PI * 2);
        ofVec3f vel = ofVec3f(cos(angle) * length, sin(angle) * length, ofRandom(-2, 2));
        
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
