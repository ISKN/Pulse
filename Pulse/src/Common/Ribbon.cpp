/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Ribbon.h"

Ribbon::Ribbon()
{
	show();
    resetColor();
}

void Ribbon::setup()
{
	for (float y = 0; y <= 1.5*_length; y += 1.5*_length / 10.0)
		_spline.addSourcePoint(ofVec2f(0.5*WIDTH, 0.2*HEIGHT + y));
	_spline.compute();
	computeVertices();

	_lastActivity = ofGetElapsedTimeMillis();
	_autoHide = false;

	//DEBUG_MSG("Spline has " << _spline.getSourceSize() << " sources and " << _spline.getLength() << " results");
}

void Ribbon::draw()
{
	if (_autoHide)
	{
		if (ofGetElapsedTimeMillis() - _lastActivity >= 1000)
		{
			hide();
		}
		else
		{
			show();
		}
	}

	if (_isHidden)
    {
        return;
    }

    //Draw contour
    ofSetLineWidth(3);
    ofSetColor(COLOR_WHITE);

    for (unsigned i = 0 ; i < _shapeVertices.size() - 1 ; i++)
    {
        ofLine(_shapeVertices.at(i), _shapeVertices.at(i+1));
    }
    ofLine(_shapeVertices.back(), _shapeVertices.front());

    //Draw polygon
    ofSetColor(_color);
    ofVboMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    for (unsigned i = 0 ; i < _meshVertices.size() ; i++)
    {
        _color.a = 1.0f*(float)i/(float)_meshVertices.size();
        mesh.addColor(_color);
		if (_meshVertices.size() == 0 || i >= _meshVertices.size())
		{
			DEBUG_MSG("Index " << i << " over size of " << _meshVertices.size());
			std::exit(EXIT_FAILURE);
		}
        mesh.addVertex(_meshVertices.at(i));
    }
    //mesh.addVertices(_meshVertices);
    mesh.draw();

    //Draw head
    _color.a = 1.0f;
    ofSetColor(_color);
    if (_headIsCircle)
        ofCircle(_spline.getLastSourcePoint(), _width);
}

void Ribbon::addPoint(ofVec2f const& point)
{
	_lastActivity = ofGetElapsedTimeMillis();

	//DEBUG_MSG("adding " << point.x << " " << point.y);
    while (_spline.getEstimatedLength() > 1.2*_length)
    {
        _spline.removeFirstSourcePoint();
    }

    _spline.addSourcePoint(point);
    _spline.compute();

    computeVertices();
}

void Ribbon::addPoint(unsigned x, unsigned y)
{
    addPoint(ofVec2f(x,y));
}

ofVec2f Ribbon::getHead() const
{
	return _spline.getLastSourcePoint();
}

void Ribbon::setColor(ofFloatColor const& color)
{
    //DEBUG_MSG("new color " << color.getHue() << " " << color.getSaturation() << " " << color.getBrightness() << " " << color.a);
    _color = color;
}

void Ribbon::resetColor()
{
    _color = ofFloatColor(1.0, 1.0, 1.0, 1.0);
}

ofFloatColor Ribbon::getColor() const
{
	return _color;
}

void Ribbon::hide()
{
    _isHidden = true;
}

void Ribbon::show()
{
    _isHidden = false;
}

void Ribbon::enableAutoHide()
{
	_autoHide = true;
}

void Ribbon::disableAutoHide()
{
	_autoHide = false;
}

void Ribbon::computeVertices()
{
    //Assert
    if (_spline.getLength() < _length)
    {
        //ERROR_MSG("The spline is too small: " << _spline.getLength());
        return;
    }

    //Reset
    _meshVertices.clear();
    _shapeVertices.clear();
    std::vector<ofPoint> tmp; tmp.clear();

    if (!_headIsCircle) //triangle
    {
        _meshVertices.push_back(_spline.getLastResultPoint() + _width*_spline.getResultsEndDirection());
        _shapeVertices.push_back(_meshVertices.back());
    }

    //Add vertices on the sides of the spline with decreasing width from the head
    unsigned length = 0;
    unsigned index = _spline.getLength()-1;
    while (length < _length)
    {
        const ofVec2f p1 = _spline.getResultPoint(index);
        ofVec2f dir = _spline.getResultPoint(index-1) - p1;
        dir.normalize();
        const ofVec2f perpendicular = dir.getRotated(90);
        const float space = (float)(_length-length) * (float)_width / (float)_length;

        _meshVertices.push_back(p1 + space*perpendicular);
        _meshVertices.push_back(p1 - space*perpendicular);

        _shapeVertices.push_back(p1 + space*perpendicular);
        tmp.push_back(p1 - space*perpendicular);

        index -= 10;
        length += 10;
    }

    std::reverse(tmp.begin(), tmp.end());
    for (ofPoint p : tmp)
        _shapeVertices.push_back(p);

    //Reverse order
    std::reverse(_meshVertices.begin(), _meshVertices.end());

	//DEBUG_MSG("mesh vertices number: " << _meshVertices.size());

    /*DEBUG_MSG("All points:");
    for (unsigned i=0 ; i<_meshVertices.size() ; i++)
    {
        DEBUG_MSG("x " << _meshVertices[i].x << " y " << _meshVertices[i].y);
    }*/
}
