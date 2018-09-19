#pragma once

#include "ofMain.h"
#include "ofxSimpleSerial.h"
#include "ofxXmlSettings.h"
#include "ofxOMXPlayer.h"

class ofApp : public ofBaseApp , public ofxOMXPlayerListener{
public:
	void setup();
	void update();
	void draw();
	void onNewMessage(string & message);
	void showVideo();
	void showBattery();

	void loadNextMovie();

	void onVideoEnd(ofxOMXPlayerListenerEventData& e);
	void onVideoLoop(ofxOMXPlayerListenerEventData& e){};

	string message;

	float val;

	float lowThres;
	float highThres;

	bool charged = false;

	ofxSimpleSerial	serial;

	ofTrueTypeFont myfont;

	ofxXmlSettings settings;

	vector<ofFile> files;

	int videoCounter;

	ofxOMXPlayerSettings pSettings;

	ofxOMXPlayer omxPlayer;


};
