/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#ifndef LEVEL1_H
#define LEVEL1_H

#include "../general.h"
#include "../Common/Level.h"
#include "../Common/Drum.h"

#include "../UI/FontManager.h"
extern FontManager fontManager;

//Debug
//#define DEBUG_TEMPO //Enable this if you want the tick sound to be played at each beat

//Score
#define SCORE_MISSED        0//-30
#define SCORE_MULTIPLE_HIT  -100
#define SCORE_WRONG_HIT     0//-80
#define SCORE_FUNCTION(x)   1+(int)(250*0.3989422804*exp(-pow((double)(x),2)/2.0)) //Gaussian function between f(-1) = f(1) = 70 and f(0) = 100
#define SCORE_PERFECT_BONUS 20

class Level1 : public Level
{
    public:

		Level1();

    protected:

		virtual void setupMain() override;
		virtual void updateMain() override;
		virtual void drawMain() override;

		virtual void setupStartMain() override;
		virtual void drawIntro() override;

		virtual void onHit(ofVec2f const & point) override;

        TimePoint _lastBeat;
		bool _lastBeatCheck;
		bool _resetLastBeatCheck;

		//Debug
		ofSoundPlayer _debug;

	private:

		bool _debugTick;
};

#endif // LEVEL1_H
