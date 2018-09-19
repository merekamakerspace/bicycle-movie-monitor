#include "ofApp.h"

bool doLoadNextMovie = false;

void ofApp::onVideoEnd(ofxOMXPlayerListenerEventData& e)
{
	ofLogVerbose(__func__) << " RECEIVED";
	doLoadNextMovie = true;
	ofLog() << "Video Stopped";
	charged = false;

}




//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);
	ofHideCursor();
	settings.loadFile("settings.xml");
	string serialPort = settings.getValue("settings:serialPort", "/dev/ttyACM0");
	string videoDirectory = settings.getValue("settings:videoDirectory", "movies");

	lowThres = settings.getValue("settings:lowThres", 4);
	highThres = settings.getValue("settings:highThres", 10);


	ofSetWindowTitle("Bicycle Cinema");
	serial.setup(serialPort, 115200);
	serial.startContinuousRead();
	ofAddListener(serial.NEW_MESSAGE, this, &ofApp::onNewMessage);
	myfont.load("arial.ttf", 70);

	ofDirectory currentVideoDirectory(ofToDataPath(videoDirectory, true));

	for (int i = 0; i < currentVideoDirectory.size(); i++) {
		ofLog() << (currentVideoDirectory.getPath(i));
	}

	if (currentVideoDirectory.exists())
	{
		currentVideoDirectory.listDir();
		currentVideoDirectory.sort();
		files = currentVideoDirectory.getFiles();
		if (files.size() > 0)
		{
			videoCounter = 0;
			pSettings.videoPath = files[videoCounter].path();
			pSettings.useHDMIForAudio = true;	//default true
			pSettings.enableLooping = false;		//default true
			pSettings.enableTexture = true;		//default true
			pSettings.listener = this;			//this app extends ofxOMXPlayerListener so it will receive events ;
			omxPlayer.setup(pSettings);
		}
	}

}

//--------------------------------------------------------------
void ofApp::update() {

}

void ofApp::loadNextMovie()
{
	if (videoCounter + 1 < files.size())
	{
		videoCounter++;
	} else
	{
		videoCounter = 0;
	}
	//skipTimeStart = ofGetElapsedTimeMillis();
	omxPlayer.loadMovie(files[videoCounter].path());
	//skipTimeEnd = ofGetElapsedTimeMillis();
	//amountSkipped = skipTimeEnd - skipTimeStart;
	//totalAmountSkipped += amountSkipped;
	doLoadNextMovie = false;
}


void ofApp::showVideo() {
	if (!omxPlayer.isTextureEnabled()) return;

	omxPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());

}

void ofApp::showBattery() {
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (charged) {
		showVideo();
	} else {
		showBattery();
	}

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
			loadNextMovie();
			ofLog() << "playing";

		}

		if (val < 20 && charged) {
			charged = false;
			omxPlayer.setPaused(true);
			//myPlayer.stop();
		}

	}


}

