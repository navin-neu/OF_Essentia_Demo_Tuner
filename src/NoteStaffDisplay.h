#pragma once

#include <unordered_map>
#include <string>
#include "ScalableSVGContainer.h"

/***************************************************/
/*! 
	A composite version of ScalableSVGContainer.
    Used to store SVGS for several musical notes,
    all indexed by their midi number.
	Navin K. 2021
*/
/***************************************************/


struct NoteData {
    std::string filePath;
    float noteFrequency;
};

class NoteStaffDisplay : public ScalableSVGContainer {

public:

NoteStaffDisplay()
{

}

~NoteStaffDisplay()
{
    
}

bool setCurrentNoteByMidi(int midiNumber)
{
    NoteData n;

    try { n = noteScale.at(midiNumber); }
    catch (std::exception& e)
    {
        return false;
    }

    currentMidiNote = midiNumber;
    currentSVG.load(n.filePath);
    if (scaleFactor != 1.0f) this->scaleCurrentSVGByScaleFactor();
    return true;
}

float getCurrentNoteFrequency()
{
    return noteScale.at(currentMidiNote).noteFrequency;
}

void addNote(int degree, NoteData noteData)
{
    noteScale.insert({degree, noteData});
}

int getStaffSize()
{
    return noteScale.size();
}

void clearStaff()
{
    noteScale.clear();
}

void initializeAllNotes() //would prefer to read this from a table.
{
    noteScale.insert({52, {"note1.svg", 164.81f}});
    noteScale.insert({53, {"note2.svg", 174.61f}});
    noteScale.insert({54, {"note3.svg", 185.00f}});
    noteScale.insert({55, {"note4.svg", 196.00f}});
    noteScale.insert({56, {"note5.svg", 207.65f}});
    noteScale.insert({57, {"note6.svg", 220.00f}});
    noteScale.insert({58, {"note7.svg", 233.08f}});
    noteScale.insert({59, {"note8.svg", 246.94f}});
    noteScale.insert({60, {"note9.svg", 261.63f}});
    noteScale.insert({61, {"note10.svg", 277.18f}});
    noteScale.insert({62, {"note11.svg", 293.66f}});
    noteScale.insert({63, {"note12.svg", 311.13f}});
    noteScale.insert({64, {"note13.svg", 329.63f}});
    noteScale.insert({65, {"note14.svg", 349.23f}});
    noteScale.insert({66, {"note15.svg", 369.99f}});
    noteScale.insert({67, {"note16.svg", 392.00f}});
    noteScale.insert({68, {"note17.svg", 415.30f}});
    noteScale.insert({69, {"note18.svg", 440.00f}});
    noteScale.insert({70, {"note19.svg", 466.16f}});
    noteScale.insert({71, {"note20.svg", 493.88f}});
    noteScale.insert({72, {"note21.svg", 523.25f}});
    noteScale.insert({73, {"note22.svg", 554.37f}});
    noteScale.insert({74, {"note23.svg", 587.33f}});
    noteScale.insert({75, {"note24.svg", 622.25f}});
    noteScale.insert({76, {"note25.svg", 659.25f}});
    noteScale.insert({77, {"note26.svg", 698.46f}});
    noteScale.insert({78, {"note27.svg", 739.99f}});
    noteScale.insert({79, {"note28.svg", 830.61f}});
    noteScale.insert({80, {"note29.svg", 880.00f}});
    noteScale.insert({81, {"note30.svg", 932.33f}});
    noteScale.insert({82, {"note31.svg", 987.77f}});
}

private:

std::unordered_map<int, NoteData> noteScale;
int currentMidiNote;

};