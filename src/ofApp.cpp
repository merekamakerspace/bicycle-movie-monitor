#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(52);
	ofHideCursor();
	settings.loadFile("settings.xml");
	string serialPort = settings.getValue("settings:serialPort", "/dev/ttyACM0");
	string videoFile = settings.getValue("settings:videoFile", "osce.mp4");

	lowThres = settings.getValue("settings:lowThres", 300);
	highThres = settings.getValue("settings:highThres", 600);


	ofSetWindowTitle("Battery Level");
	serial.setup(serialPort, 115200);
	serial.startContinuousRead();
	ofAddListener(serial.NEW_MESSAGE, this, &ofApp::onNewMessage);
	myfont.load("arial.ttf", 70);

	myPlayer.load(videoFile);
	myPlayer.setLoopState(OF_LOOP_NONE);
	myPlayer.setVolume(0.8);

	//charged = true;
	//myPlayer.setPaused(true);
}

//--------------------------------------------------------------
void ofApp::update() {
	myPlayer.update();
}

void ofApp::showVideo() {
	myPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());

	if (myPlayer.getIsMovieDone()) {
		charged = false;
	}
}

void ofApp::showBattery() {
	//noFill();
	//float cnr = 25;
	//myPlayer.draw(20,20);
	ofPushStyle();
	float level = ofMap(val, 0, 100, 0, 600);
	ofSetColor(255, 255, 255);
	ofDrawRectangle(700, 250, 50, 100);

	//fill(255);

	ofFill();
	ofDrawRectangle(100, 100, 600, 400 ); //, cnr, cnr, cnr, cnr);
	//ofNoFill();
	//noStroke();
	//ofFill();
	if (val > 5) {
		ofSetColor(0, 200, 0);
		ofDrawRectangle(100, 100, level, 400);//, cnr, cnr, cnr, cnr);
	}
	if (val > 97) {
		ofSetColor(0, 200, 0);
		ofDrawRectangle(100, 100, 600, 400 );
		ofDrawRectangle(700, 250, 50, 100);

		//fill(0, 200, 0);
	}

	//textSize(70);
	ofSetColor(0);
	string val_str = ofToString(int(val)) + "%";
	myfont.drawString(val_str, 350, 320);
	//textSize(12);
	//text("received: " + inputStr, 10,50);
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (charged) {
		showVideo();
	} else {
		showBattery();
	}
	//showBattery();


	// string val_str = ofToString(int(val)) + "%";
	// myfont.drawString(val_str, 350, 320);

	//showBattery();

}

void ofApp::onNewMessage(string & message)
{
	ofLog()   << "message: " << message;
	vector<string> tokens = ofSplitString( message, ",");
	
	if (tokens[0] == "c") {

		val = ofMap(ofToFloat(tokens[1]), lowThres, highThres, 0, 100);
		val = ofClamp(val, 0, 100);

		ofLog() << "cap val:" << val;

		if (val > 99 && !charged) {
			charged = true;
			myPlayer.setPosition(0);
			myPlayer.play();
			ofLog() << "playing";

		}

		if (val < 20 && charged) {
			charged = false;
			myPlayer.stop();
		}

	}


}

