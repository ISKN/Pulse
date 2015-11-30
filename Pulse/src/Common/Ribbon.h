/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#ifndef RIBBON_H
#define RIBBON_H

#include "../general.h"

#include "../Graphics/Spline.h"

class Ribbon
{
    public:

        Ribbon();

		void setup();
        void draw();

        void addPoint(ofVec2f const& point);
        void addPoint(unsigned x, unsigned y);
		ofVec2f getHead() const;

        void setColor(ofFloatColor const& color);
        void resetColor();
		ofFloatColor getColor() const;

        void hide();
        void show();

		void enableAutoHide();
		void disableAutoHide();

    private:

        void computeVertices();

        std::vector<ofPoint> _meshVertices;
        std::vector<ofPoint> _shapeVertices;
        Spline _spline;

        ofFloatColor _color;

		TimePoint _lastActivity;
		bool _autoHide;

        bool _isHidden;

        const unsigned _width = 20;
        const unsigned _length = 700;
        const bool _headIsCircle = false;

};

#endif // RIBBON_H
