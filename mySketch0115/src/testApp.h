#pragma once

#include "ofMain.h"
#include "ofxPostGlitch.h"
#include "ofxBox2d.h"
#include "ofEvents.h"

#define num 200

// A simple little Data class. This is were
// you can store anything you want.
class Data {
public:
	ofColor color;
	string  name;
	int		id;
};


// A Custom Particle extedning the box2d circle
class CustomParticle : public ofxBox2dCircle {
	
public:
	
	void setupTheCustomData() {
		
		static int colors[] = {0xcae72b, 0xe63b8f, 0x2bb0e7};
		//static string abc   = "abcdefghijklmnopqrstuvwxyz";
		
		// we are using a Data pointer because
		// box2d needs to have a pointer not
		// a referance
		setData(new Data());
		Data * theData = (Data*)getData();
		
		theData->id = ofRandom(0, 100);
		//theData->name += abc[(int)ofRandom(0, abc.size())];
		theData->color.setHex(colors[(int)ofRandom(0, 3)]);
        
		printf("setting the custom data!\n");
		
	}
	
	void draw() {
		Data* theData = (Data*)getData();
		if(theData) {
			
			// Evan though we know the data object lets just
			// see how we can get the data out from box2d
			// you would use this when using a contact listener
			// or tapping into box2d's solver.
			
			float radius = getRadius();
			ofPushMatrix();
			ofTranslate(getPosition());
			ofRotateZ(getRotation());
			//ofSetColor(theData->color);
            ofSetColor(255, 255, 255);
			ofFill();
			ofCircle(0, 0, radius);
            ofSetColor(0, 0, 0);
            ofCircle(0, 0, radius/3);
			
            //            float textSize = radius/10;
            //            ofPushMatrix();
            //            ofScale(textSize, textSize);
            //			ofSetColor(255);
            //			ofDrawBitmapString(theData->name, -textSize/2, textSize);
            //            ofPopMatrix();
            //
            
            ofPopMatrix();
		}
	}
};
//-------------------------------------------------------------



class testApp : public ofBaseApp{
    
public:
	void setup();
	void update();
	void draw();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
	
	bool			bDrawLenna;
	bool			bShowHelp;
    
	
    
/*Addon instance*/
    ofFbo			myFbo;
	ofEasyCam		camera;
    
	ofTexture		texture;
	ofxPostGlitch	myGlitch;
    
//image
    ofImage			lenna;
//video
    ofVideoPlayer video;
    ofVideoPlayer video1;
    ofVideoPlayer video2;
    ofVideoPlayer video3;
    ofVideoPlayer video4;
    ofVideoPlayer video5;
//sound
    ofSoundPlayer sound01;
    ofSoundPlayer sound02;
    ofSoundPlayer sound03;
//box2d
    ofxBox2d box2d;
    vector<ofPtr<ofxBox2dRect> > boxes;
    vector<ofPtr<CustomParticle> > circles;
    
    int counter = 0;
    int analog_value = 600;
    float  number = 0;
    int  timer = 0;
    int  jikan;
//arduino
    ofArduino	ard;
    bool		bSetupArduino;			// flag variable for setting up arduino once
    bool flag = true;
    int a;
    private:
    
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
    void updateArduino();
    
    string buttonState;
    string potValue;

    
    
};