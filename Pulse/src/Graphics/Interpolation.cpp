/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Interpolation.h"

float hueBlending(float hue1, float hue2, float x) //interpolates between hue1 and hue2 at x
{
	if (hue2 - hue1 > 0.5f)
	{
		hue1 += 1.f;
	}
	else if (hue1 - hue2 > 0.5f)
	{
		hue2 += 1.f;
	}

	const float res = hue1 + (hue2 - hue1)*x;
	return res > 1 ? res - 1 : res;
}

Interpolation::Interpolation()
{
    _fcurrent = 0;
    _fstart = 0;
    _fend = 0;
    _fincrement = 0;
    _ffactor = 0;

    _pcurrent = ofVec2f(0,0);
    _pstart = ofVec2f(0,0);
    _pend = ofVec2f(0,0);
    _pincrement = ofVec2f(0,0);
    _plength = 0;

    _ppcurrent = ofVec3f(0,0,0);
    _ppstart = ofVec3f(0,0,0);
    _ppend = ofVec3f(0,0,0);
    _ppincrement = ofVec3f(0,0,0);
    _pplength = 0;

    _animation_time = 0;
    _start_time_point = ofGetElapsedTimeMicros();

    _complete = true;
    _permanent = false;

    _easing = Interpolation::NoEasing;
    _type = 0;
}

Interpolation::Interpolation(float const& start_value, float const& end_value, TimePeriod const& duration, bool const& permanent, int const& easing_type) : Interpolation()
{
    _fstart = start_value;
    _fcurrent = _fstart;
    _fend = end_value;
    _fincrement = _fend - _fstart;
    _ffactor = (_fend - _fstart) / fabs(_fend - _fstart); //1 or -1

    _animation_time = duration*1000; //From ms to µs.
    _permanent = permanent;
    _complete = false;
    _easing = easing_type;

    _type = Interpolation::Float;

    _start_time_point = ofGetElapsedTimeMicros();
}

Interpolation::Interpolation(ofVec2f const& start_value, ofVec2f const& end_value, TimePeriod const& duration, bool const& permanent, int const& easing_type) : Interpolation()
{
    _pstart = start_value;
    _pend = end_value;
    _pcurrent = _pstart;

    _pincrement = end_value - start_value;
    _plength = _pincrement.length();

    _animation_time = duration*1000; //From ms to µs.
    _permanent = permanent;
    _complete = false;
    _easing = easing_type;

    _type = Interpolation::Point;

    _start_time_point = ofGetElapsedTimeMicros();
}

Interpolation::Interpolation(ofVec3f const& start_value, ofVec3f const& end_value, TimePeriod const& duration, bool const& permanent, int const& easing_type) : Interpolation()
{
    _ppstart = start_value;
    _ppend = end_value;
    _ppcurrent = _ppstart;

    _ppincrement = end_value - start_value;
    _pplength = _ppincrement.length();

    _animation_time = duration*1000; //From ms to µs.
    _permanent = permanent;
    _complete = false;
    _easing = easing_type;

    _type = Interpolation::Point3;

    _start_time_point = ofGetElapsedTimeMicros();
}

void Interpolation::reset()
{
	_fcurrent = _fstart;
	_pcurrent = _pstart;
	_ppcurrent = _ppstart;
	_complete = false;
	_start_time_point = ofGetElapsedTimeMicros();
}

void Interpolation::update()
{
    switch (_type)
    {
        case Interpolation::Float  : update_float();   break;
        case Interpolation::Point  : update_point();   break;
        case Interpolation::Point3 : update_point3d(); break;
        default : ERROR_MSG("Unknown interpolation type: " << _type);
    }
}

void Interpolation::update_float()
{
    if (!_complete)
    {
        if (_ffactor*_fcurrent < _ffactor*_fend)
        {
            float t = (float)(ofGetElapsedTimeMicros()-_start_time_point)/(float)(_animation_time);
            t = t > 1 ? 1 : t;

            switch (_easing)
            {
                case Interpolation::NoEasing : _fcurrent = easing_func_linear(_fstart, _fincrement, t); break;
                case Interpolation::EasingIn : _fcurrent = easing_func_quadratic_in(_fstart, _fincrement, t); break;
                case Interpolation::EasingOut : _fcurrent = easing_func_quadratic_out(_fstart, _fincrement, t); break;
                case Interpolation::EasingInOut : _fcurrent = easing_func_quadratic_in_out(_fstart, _fincrement, t); break;
            default: ERROR_MSG("Unknown easing type: " << _easing);
            }
        }
        else
        {
            ofNotifyEvent(finished);
            _complete = true;
        }
    }
}

void Interpolation::update_point()
{
    if (!_complete)
    {
        if ((_pcurrent-_pstart).length() < _plength)
        {
            float t = (float)(ofGetElapsedTimeMicros()-_start_time_point)/(float)(_animation_time);
            t = t > 1 ? 1 : t;

            switch (_easing)
            {
                case Interpolation::NoEasing :
                    _pcurrent.x = easing_func_linear(_pstart.x, _pincrement.x, t);
                    _pcurrent.y = easing_func_linear(_pstart.y, _pincrement.y, t);
                    break;
                case Interpolation::EasingIn :
                    _pcurrent.x = easing_func_quadratic_in(_pstart.x, _pincrement.x, t);
                    _pcurrent.y = easing_func_quadratic_in(_pstart.y, _pincrement.y, t);
                    break;
                case Interpolation::EasingOut :
                    _pcurrent.x = easing_func_quadratic_out(_pstart.x, _pincrement.x, t);
                    _pcurrent.y = easing_func_quadratic_out(_pstart.y, _pincrement.y, t);
                    break;
                case Interpolation::EasingInOut :
                    _pcurrent.x = easing_func_quadratic_in_out(_pstart.x, _pincrement.x, t);
                    _pcurrent.y = easing_func_quadratic_in_out(_pstart.y, _pincrement.y, t);
                    break;
                default: ERROR_MSG("Unknown easing type: " << _easing);
            }
        }
        else
        {
            ofNotifyEvent(finished);
            _complete = true;
        }
    }
}

void Interpolation::update_point3d()
{
    if (!_complete)
    {
        if ((_ppcurrent-_ppstart).length() < _pplength)
        {
            float t = (float)(ofGetElapsedTimeMicros()-_start_time_point)/(float)(_animation_time);
            t = t > 1 ? 1 : t;

            switch (_easing)
            {
                case Interpolation::NoEasing :
                    _ppcurrent.x = easing_func_linear(_ppstart.x, _ppincrement.x, t);
                    _ppcurrent.y = easing_func_linear(_ppstart.y, _ppincrement.y, t);
                    _ppcurrent.z = easing_func_linear(_ppstart.z, _ppincrement.z, t);
                    break;
                case Interpolation::EasingIn :
                    _ppcurrent.x = easing_func_quadratic_in(_ppstart.x, _ppincrement.x, t);
                    _ppcurrent.y = easing_func_quadratic_in(_ppstart.y, _ppincrement.y, t);
                    _ppcurrent.z = easing_func_quadratic_in(_ppstart.z, _ppincrement.z, t);
                    break;
                case Interpolation::EasingOut :
                    _ppcurrent.x = easing_func_quadratic_out(_ppstart.x, _ppincrement.x, t);
                    _ppcurrent.y = easing_func_quadratic_out(_ppstart.y, _ppincrement.y, t);
                    _ppcurrent.z = easing_func_quadratic_out(_ppstart.z, _ppincrement.z, t);
                    break;
                case Interpolation::EasingInOut :
                    _ppcurrent.x = easing_func_quadratic_in_out(_ppstart.x, _ppincrement.x, t);
                    _ppcurrent.y = easing_func_quadratic_in_out(_ppstart.y, _ppincrement.y, t);
                    _ppcurrent.z = easing_func_quadratic_in_out(_ppstart.z, _ppincrement.z, t);
                    break;
                default: ERROR_MSG("Unknown easing type: " << _easing);
            }
        }
        else
        {
            ofNotifyEvent(finished);
            _complete = true;
        }
    }
}

float Interpolation::current_float_value()
{
    update_float();
    return _fcurrent;
}

ofVec2f Interpolation::current_position()
{
    update_point();
    return _pcurrent;
}

ofVec3f Interpolation::current_position3d()
{
    update_point3d();
    return _ppcurrent;
}

float Interpolation::elapsed_seconds() const
{
	return (float)(ofGetElapsedTimeMicros() - _start_time_point) / 1000000.f;
}

bool Interpolation::is_active() const
{
    return _permanent ? true : !_complete;
}

bool Interpolation::is_permanent() const
{
    return _permanent;
}

float Interpolation::easing_func_linear(float const& start, float const& increment, float const& x)
{
    return increment*x + start;
}

float Interpolation::easing_func_quadratic_in(float const& start, float const& increment, float const& x)
{
    return increment*x*x + start;
}

float Interpolation::easing_func_quadratic_out(float const& start, float const& increment, float const& x)
{
    return -increment * x * (x-2) + start;
}

float Interpolation::easing_func_quadratic_in_out(float const& start, float const& increment, float const& x)
{
    float x2 = 2*x;
	if (x2 < 1)
        return increment/2*x2*x2 + start;
	x2--;
	return -increment/2 * (x2*(x2-2) - 1) + start;
}
