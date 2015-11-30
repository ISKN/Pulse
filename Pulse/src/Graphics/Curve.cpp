/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Curve.hpp"

void Curve::addSourcePoint(ofVec2f const& point)
{
    _sources.push_back(point);
}

void Curve::removeFirstSourcePoint()
{
    if (!_sources.empty())
        _sources.pop_front();
}

ofVec2f Curve::getSourcePoint(unsigned index) const
{
    if (index < _sources.size())
    {
        return _sources[index];
    }
    //else
        ERROR_MSG(index << " is not a valid _sources index");
        return ofVec2f(0,0);
}

ofVec2f Curve::getLastSourcePoint() const
{
    if (!_sources.empty())
        return _sources.back();
    //else
        ERROR_MSG("No source point available: return empty point");
        return ofVec2f(0,0);
}

unsigned Curve::getSourceSize() const
{
    return _sources.size();
}

ofVec2f Curve::getSourcesEndDirection() const
{
    if (_sources.size() >= 2)
    {
        return _sources[_sources.size() - 1] - _sources[_sources.size() - 2];
    }
    //else
        ERROR_MSG("Not enough sources to get the direction");
        return ofVec2f(0,0);
}

ofVec2f Curve::getResultPoint(unsigned index) const
{
    if (index < _results.size())
    {
        return _results[index];
    }
    //else
        ERROR_MSG(index << " is not a valid _results index");
        return ofVec2f(0,0);
}

ofVec2f Curve::getLastResultPoint() const
{
    if (!_results.empty())
    {
        return _results.back();
    }
    //else
        ERROR_MSG("Results list is empty");
        return ofVec2f(0,0);
}

unsigned Curve::getLength() const
{
    return _results.size();
}

ofVec2f Curve::getResultsEndDirection()
{
    if (_results.size() >= 2)
    {
        _directionBackup = _results[_results.size() - 1] - _results[_results.size() - 2];
        _directionBackup.normalize();
    }
    else
        ERROR_MSG("Not enough results to get the direction");

    return _directionBackup;
}

void Curve::clear()
{
    _sources.clear();
    _results.clear();
}
