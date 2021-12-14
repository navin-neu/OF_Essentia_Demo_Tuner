#include "ofApp.h"

/***************************************************/
/*! 
	Basic OpenFrameworks Sketch implementing a tuner.
	It will display a tuning meter showing the nearest
	tone and your distance from in up to +/- 50 cents.
	It will also display the note on the treble clef
	for notes in MIDI range  52-82 (the range of a trumpet.)

	This sketch demos the animating capabilities of OpenFrameworks,
	as well as the use of addons like ofxGui and ofxSVG.
	It also showcases a very basic use of the Essentia Library
	for audio analysis.

	Navin K. 2021
*/
/***************************************************/

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(255,255,255);
	ofSetColor(0,0,0);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofNoFill();

	bufferSize = 512;

	//OfSoundStream will allow us to use real time audio
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.setInListener(this);
    settings.numOutputChannels = 2;
    settings.numInputChannels = 2;
    settings.numBuffers = 4;
    settings.bufferSize = bufferSize;
	settings.sampleRate = 48000;
	soundStream.setup(settings);

	//setup trumpet staff display
	trumpetNotes.initializeAllNotes();
	trumpetNotes.setCurrentNoteByMidi(69);
	trumpetNotes.setScaleFactor(ofGetWidth()/trumpetNotes.getCurrentSVGWidth());


	//Setup the GUI panel for confidence threshold
	ofxGuiSetFont("Questrial-Regular.ttf",14,true,true);
	gui.setup("Controls");
	gui.add(confThreshold.set("Confidence", 0.75f, 0.1f, 0.99f));

	//Pass required data to initizialize yin
	yin.setup(soundStream.getSampleRate(), settings.bufferSize);
}

//--------------------------------------------------------------
void ofApp::update(){

	//compute new estimated pitch, update variables
	yin.compute();
	yinPitch = yin.getOutput();
	yinConfidence = yin.getConfidence();

	//If confidence is high we find the rounded MIDI note of new pitch
	//along with difference to actual frequency in cents
	if (yinConfidence > confThreshold)
	{
		midiNote = 69.0f + log2f(yinPitch/440.0f)*12.0f;

		float roundedNote = roundf(midiNote);
		centsFromNote = (midiNote - roundedNote)*100.0f;

		//Only update selected note when in range of trumpet
		if (roundedNote >= 52.0f && roundedNote <= 82.0f) trumpetNotes.setCurrentNoteByMidi((int) roundf(midiNote));
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackgroundGradient(ofColor::white, ofColor::darkGray);
	ofSetColor(ofColor::black);
	ofSetLineWidth(15);
	ofNoFill();

	//Find where the indicator should be based on difference between rounded an unrounded MIDI note
	float circleXPos = (float) ofGetWidth()/2 + centsFromNote*ofGetWidth()/100.0f;

	//Draw the indicator
	ofSetColor(ofColor::darkRed.getLerped(ofColor::black, (float) abs(centsFromNote/50)));
	ofDrawCircle(circleXPos, ofGetHeight()/4, ofGetHeight()/16);
	ofDrawLine(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight()/2);
	ofSetColor(ofColor::black);

	//Draw the treble clef SVG
	ofPushMatrix();
	ofTranslate(0, (ofGetHeight()-trumpetNotes.getCurrentSVGHeight())/2 - 15.0f);
	trumpetNotes.drawCurrentSVG();
	ofPopMatrix();

	//draw a few values for testing
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()),20,ofGetHeight()/2-100);
    ofDrawBitmapString("essentia pitch: " + ofToString(yinPitch),20,ofGetHeight()/2-120);
	ofDrawBitmapString("essentia confidence: " + ofToString(yinConfidence),20,ofGetHeight()/2-140);
	ofDrawBitmapString("midinote: " + ofToString(midiNote),20,ofGetHeight()/2-160);
	ofDrawBitmapString("relative cents:" + ofToString(centsFromNote),20,ofGetHeight()/2-180);

	//Dont forget the slider for confidence threshold!
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer & buffer){
	//No audio output in this app, but the buffer works quite similarly as audioIn()
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & buffer){
	
	yin.updateBufferContents(buffer); //Only thing to do with audio is pass it to PitchYin

}
