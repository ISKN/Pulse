/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Circle.h"

Circle::Circle(TimePeriod tempoPeriod, float rotationValue, ofVec3f const& position, int radius, float innerFactor)
: _tempoPeriod(tempoPeriod), _rotation(rotationValue), _position(position), _radius(radius), _innerFactor(innerFactor)
{
    _color = COLOR_WHITE;
    _isDead = false;
    _isFull = false;
    _isEmptying = false;
    _isBuilding = false;
	_hitAnimationSet = false;
	_ring = ofxRing(0, 0, _radius*_innerFactor, _radius, 200);
	_hitRing = ofxRing(0, 0, _radius*_innerFactor, _radius, 200);
}

void Circle::draw()
{
    ofPushMatrix();

        ofTranslate(_position);

        ofPushMatrix();

            ofRotateX(_rotation);

            //Check if he's dead for the color

            if (_isDead)
            {
                const unsigned r = std::round(_dieRAnimation.current_float_value());
                const unsigned g = std::round(_dieGAnimation.current_float_value());
                const unsigned b = std::round(_dieBAnimation.current_float_value());
                const unsigned a = std::round(_dieOpacityAnimation.current_float_value());
                ofSetColor(ofColor(r,g,b,a));
            }
            else
            {
                ofSetColor(_color);
            }

            //Check if there are some animations for the shape

            if (_isFull)
            {
                _ring.setInnerRadius(_fillAnimation.current_float_value());
            }

            if (_isEmptying)
            {
                _ring.setInnerRadius(_emptyAnimation.current_float_value());
            }

            if (_isBuilding)
            {
				_ring.setInnerRadius(_buildAnimation.current_float_value()*_innerFactor);
                _ring.setOuterRadius(_buildAnimation.current_float_value());
            }

			if (_isDead)
			{
				//_ring.setInnerRadius(_dieRadiusAnimation.current_float_value()*CIRCLE_INNER_RADIUS_FACTOR);
				_ring.setOuterRadius(_dieRadiusAnimation.current_float_value());
			}

            _ring.draw();

            //Draw the hit animation
            if (_hitOpacityAnimation.is_active())
            {
                ofSetColor(SET_OPACITY(_color, std::round(_hitOpacityAnimation.current_float_value())));
				_hitRing.setInnerRadius(_hitRadiusAnimation.current_float_value()*_innerFactor);
                _hitRing.setOuterRadius(_hitRadiusAnimation.current_float_value());
                _hitRing.draw();
            }

        ofPopMatrix();

    ofPopMatrix();
}

void Circle::setPosition(ofVec3f const& position)
{
    _position = position;
}

ofVec3f Circle::getPosition() const
{
    return _position;
}

void Circle::kill(TimePeriod duration, bool makeItGoSmaller)
{
    if (!_isDead)
    {
        _isDead = true;
        _dieOpacityAnimation = Interpolation(_color.a, 0.0f, duration, false, Interpolation::EasingOut);
		_dieRAnimation = Interpolation(_color.r, 0.0f, duration, false, Interpolation::EasingOut);
		_dieGAnimation = Interpolation(_color.g, 0.0f, duration, false, Interpolation::EasingOut);
		_dieBAnimation = Interpolation(_color.b, 0.0f, duration, false, Interpolation::EasingOut);
		if (makeItGoSmaller)
		{
			_dieRadiusAnimation = Interpolation(_radius, 0, duration, false, Interpolation::EasingOut);
		}
		else
		{
			_dieRadiusAnimation = Interpolation(_radius, _radius, duration, false, Interpolation::EasingOut);
		}
    }
}

void Circle::hit(TimePeriod duration, float finalRadius, bool finalHit)
{
    //You can always hit a circle except when he's dead
    if (!_isDead)
    {
        if (finalHit)
        {
			_hitRadiusAnimation = Interpolation(0.9*_radius, finalRadius, duration, false);
			_hitOpacityAnimation = Interpolation(_color.a, 0.0f, duration, false);
            _ring.setInnerRadius(0.0f);
            _ring.setOuterRadius(0.0f);
        }
        else
        {
			if (!_hitAnimationSet)
			{
				_hitRadiusAnimation = Interpolation(0.9*_radius, finalRadius, duration, false);
				_hitOpacityAnimation = Interpolation(_color.a, 0.0f, duration, false);
				_hitAnimationSet = true;
			}
			else
			{
				_hitRadiusAnimation.reset();
				_hitOpacityAnimation.reset();
			}
		}
    }
}

void Circle::fill(TimePeriod duration)
{
    if (!_isFull)
    {
        _isFull = true;
		_fillAnimation = Interpolation(_innerFactor*_radius, 0.0, duration, true);
    }
}

void Circle::empty(TimePeriod duration)
{
    if (!_isEmptying)
    {
        _isEmptying = true;
		_ring.setInnerRadius(0.0);
		_emptyAnimation = Interpolation(0.0, _innerFactor*_radius, duration, true);
    }
}

void Circle::build(TimePeriod duration, float finalRadius)
{
    if (!_isBuilding)
    {
        _isBuilding = true;
        _buildAnimation = Interpolation(0.0, finalRadius, duration, true);
    }
}

void Circle::setColor(ofColor const& color)
{
    _color = color;
}

bool Circle::isDead() const
{
    return _isDead;
}

bool Circle::hitFinished() const
{
	return !_hitOpacityAnimation.is_active();
}