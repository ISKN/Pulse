/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Level1.h"

Level1::Level1()
: Level(PART_NUMBER_LEVEL1, 60000, COLOR_MAIN_1, true)
{
}

void Level1::setupMain()
{
	_drums.push_back(new Drum(ofVec2f(WIDTH / 2, HEIGHT / 2), true, _levelColor, ofToDataPath("drums/tick.wav")));

	try
	{
		_debugTick = (bool)std::stoi(getSetting("debug", "tick"));
	}
	catch (std::exception & e)
	{
		ERROR_MSG("Cannot get tick setting: '" << e.what() << "' -> disabling debug feature by default");
		_debugTick = false;
	}

	if (_debugTick)
		_debug.load(ofToDataPath("drums/tick.wav"));
}

void Level1::updateMain()
{
	//Update beat timer
	TimePoint now = ofGetElapsedTimeMillis();
	if (now - _lastBeat >= _period)
	{
		_lastBeat = now - (now - _lastBeat - _period); //Include the delay if we're a bit late (will surely happen)
		_resetLastBeatCheck = false;

	if (_debugTick)
		_debug.play();
	}

	//Check if we just crossed half the last cue time
	if (!_resetLastBeatCheck && ofGetElapsedTimeMillis() >= _lastBeat + _period / 2)
	{
		_lastBeatCheck = false;
		_resetLastBeatCheck = true;
	}
}

void Level1::drawMain()
{
}

void Level1::setupStartMain()
{
	_lastBeatCheck = false;
	_resetLastBeatCheck = false;

	_lastBeat = ofGetElapsedTimeMillis();
}

void Level1::drawIntro()
{
	drawIntroOutroTitle(lang("Suivez le rythme", "Keep the Beat"), _levelColor);

	drawIntroOutroText(lang("Traversez la zone en rythme et battez le meilleur score !","Go through the displayed zone in pace with the music and break the record!"), COLOR_WHITE);
}

void Level1::onHit(ofVec2f const & point)
{
	(void)point;

	if (_lastBeatCheck)
	{
		newScore(lang("Doucement !", "Slow down!"), SCORE_MULTIPLE_HIT, _ribbon.getHead() + ofVec2f(130, -20), COLOR_YELLOW, _period);
	}
	else
	{
		const TimePoint now = ofGetElapsedTimeMillis();
		long long int difference = (long long int)now - (long long int)_lastBeat;
		if (difference >= (long long int)_period / 2)
			difference -= (long long int)_period;

		int score = SCORE_FUNCTION((double)(difference) / (double)(_period * 0.5));

		if (std::abs(difference) < _period*0.05)
		{
			score += SCORE_PERFECT_BONUS;
			newScore(lang("Super !", "Great!"), score, _ribbon.getHead() + ofVec2f(130, -20), COLOR_BLUE, _period);
		}
		else if (std::abs(difference) >= _period*0.05 && std::abs(difference) < _period*0.20)
		{
			newScore(lang("Bien !", "Good!"), score, _ribbon.getHead() + ofVec2f(130, -20), COLOR_GREEN, _period);
		}
		else if (std::abs(difference) >= _period*0.20)
		{
			newScore(lang("Pas mal !", "Not bad!"), score, _ribbon.getHead() + ofVec2f(130, -20), COLOR_ORANGE, _period);
		}

		_lastBeatCheck = true;
	}
}
