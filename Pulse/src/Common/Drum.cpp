/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Drum.h"

Drum::Drum(ofVec2f const & position, bool big, ofColor const & color, std::string const & soundFile)
: _position(position), _isBig(big), _color(color)
{
	if (!soundFile.empty())
	{
		_hasSound = true;
		_sound.loadSound(soundFile);
		DEBUG_MSG("Loaded sound file " << soundFile);
	}
	else
	{
		_hasSound = false;
		DEBUG_MSG("No sound file specified for the drum");
	}

	_isHit = false;
	_lastPoint = ofVec2f(0, 0);

	if (_isBig)
	{
		_width = DRUM_DEFAULT_WIDTH_BIG;
		_height = DRUM_DEFAULT_HEIGHT_BIG;
	}
	else
	{
		_width = DRUM_DEFAULT_WIDTH_SMALL;
		_height = DRUM_DEFAULT_HEIGHT_SMALL;
	}

	/* Compute zone mesh */
	{
		_zone.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

		const float gap = 5.f;
		const unsigned rows = std::round(_height / gap);
		const unsigned columns = std::round(_width / gap);

		// Set up vertices
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < columns; c++)
			{
				_zone.addColor(ofColor::fromHsb(0.5f, 0.0f, 1.0f, 1.f - std::abs(r - (float)rows / 2.f) / ((float)rows / 2.f)));

				//int index = r*columns + c;
				//vertices[3 * index + 0] = (float)c;
				//vertices[3 * index + 1] = (float)r;
				//vertices[3 * index + 2] = 0.0f;

				_zone.addVertex(ofVec3f(c * gap, r * gap, 0.f));
			}
		}

		// Set up indices
		//int i = 0;
		for (int r = 0; r < rows - 1; r++)
		{
			//indices[i++] = r * columns;
			_zone.addIndex(r * columns);

			for (int c = 0; c < columns; c++)
			{
				//indices[i++] = r * columns + c;
				//indices[i++] = (r + 1) * columns + c;
				_zone.addIndex(r * columns + c);
				_zone.addIndex((r + 1) * columns + c);
			}

			//indices[i++] = (r + 1) * columns + (columns - 1);
			_zone.addIndex((r + 1) * columns + (columns - 1));
		}
	}

	/* Compute voronoi */
	{
		std::vector<ofVec2f> points;

		for (float x = 0; x < 2*_width; x += ofRandom(_width / 50.f, _width / 13.f))
		{
			for (float y = 0; y < 2*_height; y += ofRandom(_height / 5.f, _height / 1.5f))
			{
				points.push_back(ofVec2f(x - _width / 2.f, y - _height/2.f));
			}
		}

		_voronoi.compute(points, ofRectangle(0, 0, _width, _height), 0.0f);
	}

	/* Load shader */
	_bump.load(ofToDataPath("shaders/bump.vert"), ofToDataPath("shaders/bump.frag"));
}

Drum::Drum()
: Drum(ofVec2f(0,0), false, COLOR_WHITE, std::string())
{
}

Drum::~Drum()
{
	if (_hasSound)
		_sound.unloadSound();
}

bool Drum::validHit(ofVec2f const & cursor)
{
	//If the user is inside the zone (or almost)
	if ((_lastPoint.x >= _position.x - _width / 2.f && _lastPoint.x <= _position.x + _width / 2.f)
		 || (cursor.x >= _position.x - _width / 2.f && cursor.x <= _position.x + _width / 2.f))
	{
		//and if he crossed the x-axis
		if ((_lastPoint.y - _position.y) * (cursor.y - _position.y) <= 0)
		{
			//and if it did it while going down
			if (cursor.y - _position.y > 0)
			{
				//then we're good
				_isHit = true;
				_hitPoint = cursor;

				if (_hasSound)
					_sound.play();

				_lastPoint = cursor;
				return true;
			}
		}
	}

	_lastPoint = cursor;
	return false;
}

void Drum::draw(ofVec2f const & cursor)
{
	ofPushMatrix();

		ofTranslate(_position.x - _width / 2.f, _position.y - _height / 2.f);

		_bump.begin();

			_bump.setUniform2f("mouse", cursor.x - WIDTH / 2, HEIGHT - cursor.y - HEIGHT / 2);

			ofSetColor(_color);
			//_zone.drawWireframe();
			ofSetLineWidth(1);
			for (ofxSegmentIterator it = _voronoi.edges(); it; ++it)
			{
				ofxSegment e = *it;
				ofLine(e.p1, e.p2);
			}

		_bump.end();

	ofPopMatrix();
}
