/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "../general.h"
#include "../Graphics/Interpolation.h"
#include "ofxRing.h"

extern Tempo songTempo;

#define CIRCLE_ROTATION -20
#define CIRCLE_RADIUS 30
#define CIRCLE_INNER_RADIUS_FACTOR 0.7

class Circle
{
    public:

		explicit Circle(TimePeriod tempoPeriod = TEMPO_TO_MS(songTempo), float rotationValue = CIRCLE_ROTATION, ofVec3f const& position = ofVec3f(0, 0, 0), int radius = CIRCLE_RADIUS, float innerFactor = CIRCLE_INNER_RADIUS_FACTOR);

        virtual void update() {} //Does nothing here.
        void draw();

        void setPosition(ofVec3f const& position);
        ofVec3f getPosition() const;

        void kill(TimePeriod duration = TEMPO_TO_MS(songTempo), bool makeItGoSmaller = false);
        void hit(TimePeriod duration = TEMPO_TO_MS(songTempo), float finalRadius = 2*CIRCLE_RADIUS, bool finalHit = false);
        void fill(TimePeriod duration = TEMPO_TO_MS(songTempo));
        void empty(TimePeriod duration = TEMPO_TO_MS(songTempo));
        void build(TimePeriod duration = TEMPO_TO_MS(songTempo), float finalRadius = CIRCLE_RADIUS);
        void setColor(ofColor const& color);

        bool isDead() const;
		bool hitFinished() const;


    protected:

        TimePeriod _tempoPeriod;
        float _rotation;
        ofVec3f _position;
		int _radius;
		float _innerFactor;

        bool _isDead;
        Interpolation _dieRAnimation;
        Interpolation _dieGAnimation;
        Interpolation _dieBAnimation;
        Interpolation _dieOpacityAnimation;
		Interpolation _dieRadiusAnimation;

        Interpolation _hitRadiusAnimation;
        Interpolation _hitOpacityAnimation;
		bool _hitAnimationSet;

        ofxRing _hitRing;

        ofxRing _ring;
        bool _isFull;
        Interpolation _fillAnimation;

        bool _isEmptying;
        Interpolation _emptyAnimation;

        bool _isBuilding;
        Interpolation _buildAnimation;

        ofColor _color;

};

#endif // CIRCLE_H
