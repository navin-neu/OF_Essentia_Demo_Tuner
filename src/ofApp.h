#pragma once

#include "ofMain.h"
#include <map>
#include "ofxGui.h"
#include <deque>
#include <vector>
#include "essentiaYin.h"
#include "ofMath.h"
#include "NoteStaffDisplay.h"

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

class ofApp : public ofBaseApp{
	
	public:

		//The most fundamental functions for an OF sketch
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);
		
		//These functions are called everytime an input/output buffer is filled
		void audioOut(ofSoundBuffer & buffer);
		void audioIn(ofSoundBuffer & buffer);


		int bufferSize; //Can be changed in setup()
		ofSoundStream soundStream;

		ofxPanel gui;
		ofParameter<float> confThreshold; //update display whenever yinConfidence > this

		essentiaYin yin; //Our instance of the YinPitch algorithm.
		float yinPitch;
		float yinConfidence;

		float midiNote = 69.0f; //Default values to be displayed on startup
		float centsFromNote = 0.0f;

		NoteStaffDisplay trumpetNotes; //Stores all of the svgs to be displayed on the bottom
	
};
