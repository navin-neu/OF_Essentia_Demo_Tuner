#include "essentiaYin.h"

using namespace essentia::standard;

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

essentiaYin::essentiaYin()
{
    essentia::init();
}

essentiaYin::~essentiaYin()
{
    essentia::shutdown();
}

void essentiaYin::setup(int sampleRate, int bufferSize)
{
    //See essentia's "standard mode" documentation for explanations on this
    AlgorithmFactory& factory = essentia::standard::AlgorithmFactory::instance();
    pitchYin = factory.create("PitchYin", "frameSize", bufferSize, "sampleRate", sampleRate);

    pitchYin->input("signal").set(yinInput);
    pitchYin->output("pitch").set(yinOutput);
    pitchYin->output("pitchConfidence").set(yinConfidence);
    
}

void essentiaYin::updateBufferContents(ofSoundBuffer &buffer)
{
    //Essentia includes a useful framecutter that might normally be used to parse long audio files into frames
    //However, in this case we can simply use each of the incoming buffers as a frame...

    int bufSize = buffer.getNumFrames();

    yinInput.resize(bufSize);

    //We take in stereo audio and just sum it to mono
    for (int i = 0; i < bufSize; i++){
		yinInput.at(i % bufSize) = buffer.getSample(i, 0) + buffer.getSample(i, 1);
	}

}

void essentiaYin::compute()
{
    pitchYin->compute(); //This will be called at framerate
}

float essentiaYin::getOutput()
{
    return yinOutput;
}

float essentiaYin::getConfidence()
{
    return yinConfidence;
}