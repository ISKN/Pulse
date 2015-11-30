/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#ifndef SPLINE_H
#define SPLINE_H

#include "../general.h"
#include "Curve.hpp"

class Spline : public Curve
{
    enum Type { Cosine, Cubic };

    public:

        explicit Spline(Type type = Cosine);
        void compute() override; //Will interpolate the whole spline.

        unsigned getEstimatedLength() const override;


    protected:

        Type _type;


    private:

        ofVec2f cubicInterpolation(ofVec2f const& p1, ofVec2f const& p2, ofVec2f const& p3, ofVec2f const& p4, float percentage);
        ofVec2f cosineInterpolation(ofVec2f const& p1, ofVec2f const& p2, float percentage);

};

#endif // SPLINE_H
