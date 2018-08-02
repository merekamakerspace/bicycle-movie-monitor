#pragma once

#include "ofMain.h"
#include "ofxSimpleSerial.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void onNewMessage(string & message);
	void showVideo();
	void showBattery();

	string message;

	float val;

	float lowThres;
	float highThres;

	bool charged = false;

	ofxSimpleSerial	serial;

	ofTrueTypeFont myfont;

	ofVideoPlayer myPlayer;

	ofxXmlSettings settings;

};
