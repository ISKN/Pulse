/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#pragma once

#include "../general.h"

#include "ofxVoronoi2D.h"

#define DRUM_DEFAULT_WIDTH_SMALL	WIDTH*0.2
#define DRUM_DEFAULT_HEIGHT_SMALL	HEIGHT*0.05
#define DRUM_DEFAULT_WIDTH_BIG		WIDTH*0.7
#define DRUM_DEFAULT_HEIGHT_BIG		HEIGHT*0.1

class Drum
{
	public:

		explicit Drum(ofVec2f const & position, bool big, ofColor const & color, std::string const & soundFile = std::string());
		Drum();
		~Drum();

		bool validHit(ofVec2f const & cursor);
		void draw(ofVec2f const & cursor);


	private:

		ofVec2f _position;
		bool _isBig;
		ofVboMesh _zone;
		float _width, _height;
		ofColor _color;

		ofxVoronoi2D _voronoi;
	
		bool _hasSound;
		ofSoundPlayer _sound;

		bool _isHit;
		ofVec2f _hitPoint;
		ofVec2f _lastPoint;
		ofShader _bump;
};

