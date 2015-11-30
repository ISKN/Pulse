/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Spline.h"

Spline::Spline(Type type)
 : Curve(), _type(type)
{
    //nothing
}

void Spline::compute()
{
    _results.clear();

    if (_type == Cosine)
    {
        if (_sources.size() < 2)
        {
            ERROR_MSG("A cosine spline needs at least 4 elements");
            return;
        }

        for (unsigned i = 0 ; i < _sources.size()-1 ; i++)
        {
            const ofVec2f p1 = _sources[i];
            const ofVec2f p2 = _sources[i+1];

            const float length = p1.distance(p2) * 2; //Purely arbitrary

            if (length == 0)
            {
                if (!_results.empty() && _results.back() != p2)
                {
                    _results.push_back(p2);
                }
            }
            else
            {
                for (float t = 0.0f ; t <= 1.0f ; t += 1.0f/length)
                {
                    const ofVec2f res = cosineInterpolation(p1, p2, t);
                    if ((!_results.empty() && _results.back() != res) || _results.empty())
                    {
                        _results.push_back(res);
                    }
                }
            }
        }
    }
    else
    {
        if (_sources.size() < 4)
        {
            ERROR_MSG("A cubic spline needs at least 4 elements");
            return;
        }

        for (unsigned i = 0 ; i < _sources.size()-1 ; i++)
        {
            const ofVec2f p1 = i == 0 ? _sources[0] : _sources[i-1];
            const ofVec2f p2 = _sources[i];
            const ofVec2f p3 = _sources[i+1];
            const ofVec2f p4 = i+1 == _sources.size()-1 ? _sources[i+1] : _sources[i+2];

            const float length = p2.distance(p3) * 2; //Purely arbitrary

            if (length == 0)
            {
                if (!_results.empty() && _results.back() != p3)
                {
                    _results.push_back(p3);
                }
            }
            else
            {
                for (float t = 0.0f ; t <= 1.0f ; t += 1.0f/length)
                {
                    const ofVec2f res = cubicInterpolation(p1, p2, p3, p4, t);
                    if ((!_results.empty() && _results.back() != res) || _results.empty())
                    {
                        _results.push_back(res);
                    }
                }
            }
        }
    }
}

unsigned Spline::getEstimatedLength() const
{
    unsigned length = 0;

    for (unsigned i = 0 ; i < _sources.size()-1 ; i++)
    {
        length += std::round(_sources[i].distance(_sources[i+1]))*1.3;
    }

    return length;
}

ofVec2f Spline::cubicInterpolation(ofVec2f const& p1, ofVec2f const& p2, ofVec2f const& p3, ofVec2f const& p4, float percentage)
{
    //Interpolate should always be between 0 and 1.

    const ofVec2f a = p4 - p3 - p1 + p2;
    const ofVec2f b = p1 - p2 - a;
    const ofVec2f c = p3 - p1;
    const ofVec2f d = p2;

    return a*percentage*percentage*percentage + b*percentage*percentage + c*percentage + d;
}

ofVec2f Spline::cosineInterpolation(ofVec2f const& p1, ofVec2f const& p2, float percentage)
{
    //Interpolate should always be between 0 and 1.

    const float t = (1.0f - cos(percentage * PI)) / 2.0f;

    return p1 * (1 - t) + p2 * t;
}
