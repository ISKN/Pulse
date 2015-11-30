/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "../general.h"

//Color blending
float hueBlending(float hue1, float hue2, float x);

class Interpolation
{
    public:

        Interpolation();
        Interpolation(float const& start_value, float const& end_value, TimePeriod const& duration, bool const& permanent = false, int const& easing_type = Interpolation::NoEasing);
        Interpolation(ofVec2f const& start_value, ofVec2f const& end_value, TimePeriod const& duration, bool const& permanent = false, int const& easing_type = Interpolation::NoEasing);
        Interpolation(ofVec3f const& start_value, ofVec3f const& end_value, TimePeriod const& duration, bool const& permanent = false, int const& easing_type = Interpolation::NoEasing);

        enum Type { Float, Point, Point3 };
        enum Easing { NoEasing, EasingIn, EasingOut, EasingInOut };

		void reset();
        void update();

        float current_float_value();
        ofVec2f current_position();
        ofVec3f current_position3d();
		float elapsed_seconds() const;

        bool is_active() const;
        bool is_permanent() const;

        ofEvent<void> finished;

    private:

        //Attributes
        float _fcurrent, _fstart, _fend, _fincrement, _ffactor;
        ofVec2f _pcurrent, _pstart, _pend, _pincrement; float _plength;
        ofVec3f _ppcurrent, _ppstart, _ppend, _ppincrement; float _pplength;

        TimePeriod _animation_time;
        TimePoint _start_time_point;

        bool _complete, _permanent;
        int _easing, _type;

        //Functions
        void update_float();
        void update_point();
        void update_point3d();

        float easing_func_linear(float const& start, float const& increment, float const& x);
        float easing_func_quadratic_in(float const& start, float const& increment, float const& x);
        float easing_func_quadratic_out(float const& start, float const& increment, float const& x);
        float easing_func_quadratic_in_out(float const& start, float const& increment, float const& x);

};

#endif // INTERPOLATION_H
