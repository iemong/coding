#include "testApp.h"

void setting();

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	//camera.setDistance(400);
	ofSetCircleResolution(3);
    
	lenna.loadImage("lenna.png");
	bDrawLenna = false;
	bShowHelp  = true;
	myFbo.allocate(512, 0);
    
	myGlitch.setup(&myFbo);
    
    
    //video
    video.loadMovie("20_Shape.mov");
    video.play();
    video1.loadMovie("10_comp.mov");
    video1.setLoopState(OF_LOOP_PALINDROME);
    video1.play();
    video2.loadMovie("compo4.mov");
    video2.play();
    video3.loadMovie("gear2.mov");
    video3.play();
    video4.loadMovie("00_fin_ba_138.mov");
    video4.play();
    video5.loadMovie("10_camera.mov");
    video5.play();
    
    //sound
    sound01.loadSound("sinpaku.mp3");
    sound02.loadSound("clock.mp3");
    sound03.loadSound("kick.mp3");
    sound01.setVolume(1.8);
    sound02.setVolume(1.2);
    sound03.setVolume(0.1);
    
    setting();
    
    box2d.init();
    box2d.setGravity(0, 40);
    box2d.setFPS(30.0);
    box2d.registerGrabbing();
    box2d.createBounds();
    
    for (int i = 0; i < num; i++) {
        float w = ofRandom(15, 40);
        float h = ofRandom(15, 40);
        ofPtr<ofxBox2dRect> rect = ofPtr<ofxBox2dRect> ( new ofxBox2dRect);
        rect.get() -> setPhysics(3.0, 0.53, 0.9);
        rect.get() -> setup(box2d.getWorld(), ofGetWidth()/2,ofGetHeight()/2,w,h);
        boxes.push_back(rect);
        
    }
    for (int j = 0; j < 2; j++) {
        ofPtr<CustomParticle> p = ofPtr<CustomParticle>(new CustomParticle);
        p.get()->setPhysics(1.0, 0.5, 0.3);
        p.get()->setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2 + 300, 30);
        p.get()->setVelocity(ofRandom(-30, 30), ofRandom(-30, 30));
        p.get()->setupTheCustomData();
        circles.push_back(p);
    }
    
    
    //arduino
    
    buttonState = "digital pin:";
    potValue = "analog pin:";
    
    // replace the string below with the serial port for your Arduino board
    // you can get this from the Arduino application or via command line
    // for OSX, in your terminal type "ls /dev/tty.*" to get a list of serial devices
	ard.connect("/dev/tty.usbmodemfa131", 57600);
	
	// listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setupArduino()
	ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
     
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (counter != 1) {
        myFbo.begin();
        ofClear(0, 0, 0,255);
        
        //camera.begin();
        /*for (int i = 0;i < 100;i++){
         if		(i % 5 == 0)ofSetColor(50 , 255, 100);
         else if (i % 9 == 0)ofSetColor(255, 50, 100);
         else				ofSetColor(255, 255, 255);
         
         ofPushMatrix();
         ofRotate(ofGetFrameNum(), 1.0, 1.0, 1.0);
         ofTranslate((ofNoise(i/2.4)-0.5)*1000,
         (ofNoise(i/5.6)-0.5)*1000,
         (ofNoise(i/8.2)-0.5)*1000);
         ofCircle(0, 0, (ofNoise(i/3.4)-0.5)*100+ofRandom(3));
         ofPopMatrix();
         }*/
        ofSetColor(255);
        if (counter == 0) {
            video.draw(0, 0,ofGetWidth(),ofGetHeight());
        }else if (counter == 2){
            video1.draw(0, 0,ofGetWidth()-300,ofGetHeight());
        }else if (counter == 3){
            video2.draw(-100, 0,ofGetWidth()-100,ofGetHeight());
        }else if (counter == 4){
            video3.draw(-200, 0,ofGetWidth()-200,ofGetHeight());
        }else if (counter == 5){
            video4.draw(-200, 0,ofGetWidth()-200,ofGetHeight());
        }else if (counter == 6){
            video5.draw(0, 0,ofGetWidth(),ofGetHeight());
        }
        
        //camera.end();
        
        myFbo.end();
        
        if (counter == 0) {
            video.update();
        }else if (counter == 2){
            video1.update();
        }else if (counter == 3){
            video2.update();
        }else if (counter == 4){
            video3.update();
        }else if (counter == 5){
            video4.update();
        }else if (counter == 6){
            video5.update();
        }
        

    }else{
        box2d.update();
    }
    
    
    //arduino
    updateArduino();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    jikan++;
    if (jikan > 60) {
        jikan = 0;
    }
    //cout << ard.getAnalog(0) << endl;
    int a = ard.getAnalog(0);
	if (counter != 1 ){
        /* draw normal view */
        //ofSetColor(255);
        //myFbo.draw(100, 300);
        //myGlitch.setFx(OFXPOSTGLITCH_GLOW			, true);
        /* Apply effects */
        myGlitch.generateFx();
        
        /* draw effected view */
        ofSetColor(255);
        myFbo.draw(0, 0, ofGetWidth(),ofGetHeight());
        
        
        /* show information*/
        string info = "";
        info += "1 - 0 : Apply glitch effects.\n";
        info += "q - u : Apply color remap effects.\n";
        info += "L key : Switch 3Dview / 2DImage.\n";
        info += "H key : Hide or show this information.";
        
        if (bShowHelp){
            ofSetColor(0, 200);
            //ofRect(25, 17, 320, 90);
            ofSetColor(255);
            //ofDrawBitmapString(info, 30,30);
        }
        ofDrawBitmapString("value: " + ofToString(analog_value), 30,100);
        ofDrawBitmapString("pulse: " + ofToString(a), 30,80);
    }else if (counter == 1){
        ofSetCircleResolution(32);
        for(int i=0; i<boxes.size(); i++) {
            ofFill();
            ofSetColor((int)ofRandom(200,255), (int)ofRandom(0, 100), 0);
            
            boxes[i].get()->draw();
        }
        
        for (int x = 0; x < circles.size(); x++) {
            circles[x].get()->draw();
        }
        
        // draw the ground
        //box2d.drawGround();
        
        
        
        string info1 = "";
         info1 += "Press [c] for circles\n";
         info1 += "Press [b] for blocks\n";
         info1 += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
         info1 += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
         info1 += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
         ofSetHexColor(0x444342);
         ofDrawBitmapString(info1, 30, 30);
         
    }
	   
    if(a >= analog_value){
        
        timer += 1;
        if (timer == 1) {
            if (counter == 0) {
                sound01.play();
            }else if (counter == 1){
                sound03.play();
            }else if (counter == 2){
                sound01.play();
            }else if (counter == 3){
                sound01.play();
            }else if (counter == 4){
                sound02.play();
            }else if (counter == 5){
                sound01.play();
            }else if (counter == 6){
                sound02.play();
            }
        }
        if (counter != 1) {
            if(counter == 0){
                myGlitch.setFx(OFXPOSTGLITCH_INVERT			, true);
            }else if (counter == 2){
                myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
            }else if (counter == 3){
                myGlitch.setFx(OFXPOSTGLITCH_TWIST			, true);

            }else if (counter == 4){
                myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);

            }else if (counter == 5){
                myGlitch.setFx(OFXPOSTGLITCH_SWELL			, true);
            }else if (counter == 6){
                myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
            }
            
        }else{
            
            for(int i=0; i<boxes.size(); i++) {
                boxes[i].get()->addAttractionPoint(ofGetWidth()/2, ofGetHeight()/3, 500 / 150);
            }
            for(int k = 0; k<circles.size(); k++) {
            circles[0].get()->addAttractionPoint(ofGetWidth()/2-100, ofGetHeight()-200, 500 / 10);
            circles[1].get()->addAttractionPoint(ofGetWidth()/2+100, ofGetHeight()-200, 500 / 10);
            }
        }
    }else{
        timer = 0;
        myGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);
        myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
        myGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
        myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
        myGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
        myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);

        for(int j=0; j<boxes.size(); j++) {
            boxes[j].get()->addAttractionPoint(ofGetWidth()/2, 0, 0);
        }
        for(int l = 0; l<circles.size(); l++) {
            circles[l].get()->addAttractionPoint(ofGetWidth()/2, ofGetHeight()/3,0);
        }
    }

        
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == OF_KEY_DOWN) {
        analog_value -= 1;
    }
    if (key == OF_KEY_UP) {
        analog_value += 1;
    }
    
    if (counter >= 0 && counter != 1) {
        if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
        if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, true);
        if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
        if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
        if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, true);
        if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, true);
        if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, true);
        if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
        if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, true);
        if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, true);
        
        if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
        if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
        if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
        if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
        if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
        if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
        if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);
        
        if (key == 'l') bDrawLenna ^= true;
        if (key == 'h') bShowHelp ^= true;
    }else if (counter == 1){
        
    }
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if (key == OF_KEY_LEFT) {
        counter -= 1;
    }
    if(key == OF_KEY_RIGHT){
        counter += 1;
    }
    
    if (counter >= 0 && counter != 1) {
        if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
        if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, false);
        if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
        if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
        if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
        if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
        if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, false);
        if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
        if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
        if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);
        
        if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
        if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
        if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
        if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
        if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
        if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
        if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);

    }else if (counter == 1){
        
    }
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}

//--------------------------------------------------------------


void setting(){
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_NOTICE);
	ofDisableAntiAliasing();
    ofBackground(0, 0, 0);
    ofEnableSmoothing();
}

void testApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)
    
    // set pins D2 and A5 to digital input
    ard.sendDigitalPinMode(2, ARD_INPUT);
    ard.sendDigitalPinMode(19, ARD_INPUT);  // pin 21 if using StandardFirmata from Arduino 0022 or older
    
    // set pin A0 to analog input
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    
    // set pin D13 as digital output
	ard.sendDigitalPinMode(13, ARD_OUTPUT);
    // set pin A4 as digital output
    ard.sendDigitalPinMode(18, ARD_OUTPUT);  // pin 20 if using StandardFirmata from Arduino 0022 or older
    
    // set pin D11 as PWM (analog output)
	ard.sendDigitalPinMode(11, ARD_PWM);
    
    // attach a servo to pin D9
    // servo motors can only be attached to pin D3, D5, D6, D9, D10, or D11
    ard.sendServoAttach(9);
	
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &testApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &testApp::analogPinChanged);
}

//--------------------------------------------------------------
void testApp::updateArduino(){
    
	// update the arduino, get any data or messages.
    // the call to ard.update() is required
	ard.update();
	
	// do not send anything until the arduino has been set up
	if (bSetupArduino) {
        // fade the led connected to pin D11
		ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));   // pwm...
	}
    
}

// digital pin event handler, called whenever a digital pin value has changed
// note: if an analog pin has been set as a digital pin, it will be handled
// by the digitalPinChanged function rather than the analogPinChanged function.

//--------------------------------------------------------------
void testApp::digitalPinChanged(const int & pinNum) {
    // do something with the digital input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    buttonState = "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum));
}

// analog pin event handler, called whenever an analog pin value has changed

//--------------------------------------------------------------
void testApp::analogPinChanged(const int & pinNum) {
    // do something with the analog input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
    
    
}
