#pragma once

#include "ofxSvg.h"

/***************************************************/
/*! 
	A wrapper class that extends ofxSVG to allow
	the SVG to be scaled uniformly. It does this
	by simply scaling up each of the individual paths
	that make up the SVG.

	Navin K. 2021
*/
/***************************************************/


class ScalableSVGContainer {

public:

ScalableSVGContainer()
{

}

~ScalableSVGContainer()
{
    
}

void setScaleFactor(float newScaleFactor)
{
    scaleFactor = newScaleFactor;
    this->scaleCurrentSVGByScaleFactor();
}

void drawCurrentSVG()
{
    currentSVG.draw();
}

float getCurrentSVGHeight() { return currentSVG.getHeight(); }
float getCurrentSVGWidth() { return currentSVG.getWidth(); }

protected:

void scaleCurrentSVGByScaleFactor()
{
    for (int i = 0; i<currentSVG.getNumPath(); i++)
	{
		currentSVG.getPathAt(i).scale(scaleFactor,scaleFactor);
	}
}

ofxSVG currentSVG;
float scaleFactor = 1.0f;
};