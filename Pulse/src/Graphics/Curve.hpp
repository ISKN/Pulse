/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#ifndef CURVE_INCLUDED
#define CURVE_INCLUDED

#include "../general.h"

class Curve
{
    public:

        //Source points
        void     addSourcePoint(ofVec2f const& point);
        void     removeFirstSourcePoint();
        ofVec2f  getSourcePoint(unsigned index) const;
        ofVec2f  getLastSourcePoint() const;
        unsigned getSourceSize() const;
        ofVec2f  getSourcesEndDirection() const;

        //Result points
        ofVec2f  getResultPoint(unsigned index) const;
        ofVec2f  getLastResultPoint() const;
        unsigned getLength() const;
        ofVec2f  getResultsEndDirection(); //Non const because of _directionBackup

        //General
        void clear();
        virtual void compute() = 0;
        virtual unsigned getEstimatedLength() const = 0;


    protected:

        std::deque<ofVec2f> _sources;
        std::vector<ofVec2f> _results;

        ofVec2f _directionBackup;

};

#endif // CURVE_INCLUDED
