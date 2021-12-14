#pragma once

#include <essentia/algorithmfactory.h>
#include <essentia/essentiamath.h>
#include "essentia.h"
#include "ofSoundBuffer.h"

/***************************************************/
/*! 
	Helper class to encapsulate the usage of Essentia's
    PitchYin algorithm within this sketch.

    While Essentia does offer a streaming mode that is suitable for realtime
    use, here I elected to use their standard mode where algorithms
    are computed on command. This was convenient since in this case
    we only need to update values at a rate equal to OpenFrameworks's
    framerate.

	Navin K. 2021
*/
/***************************************************/


class essentiaYin {

public:

    essentiaYin();

    ~essentiaYin();

    void setup(int sampleRate, int bufferSize);

    void updateBufferContents(ofSoundBuffer &buffer);

    void compute();

    float getOutput();
    
    float getConfidence();

private:

essentia::standard::Algorithm* pitchYin;
std::vector<essentia::Real> yinInput;
essentia::Real yinOutput;
essentia::Real yinConfidence;

};