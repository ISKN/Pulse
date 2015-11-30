/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Level2.h"


Level2::Level2()
: Level(PART_NUMBER_LEVEL2, 232000, COLOR_MAIN_2, false)
{
	_drums.push_back(new Drum(ofVec2f(WIDTH*0.25, HEIGHT*0.5), false, _levelColor, ofToDataPath("drums/hat.wav")));
	_drums.push_back(new Drum(ofVec2f(WIDTH*0.5, HEIGHT*0.5), false, _levelColor, ofToDataPath("drums/clap.wav")));
	_drums.push_back(new Drum(ofVec2f(WIDTH*0.75, HEIGHT*0.5), false, _levelColor, ofToDataPath("drums/crash.wav")));
}

void Level2::setupMain()
{
}

void Level2::updateMain()
{
}

void Level2::drawMain()
{
}

void Level2::setupStartMain()
{
}

void Level2::drawIntro()
{
	drawIntroOutroTitle(lang("Déchaînez-vous", "Unleash your Talent"), _levelColor);

	drawIntroOutroText(lang("Jouez des percussions par-dessus la chanson !", "Play drums on top of the song!"), COLOR_WHITE);
}

void Level2::drawOutro()
{
	drawIntroOutroTitle(lang("Vous avez été génial", "You were really great"), _levelColor);

	drawIntroOutroText(lang("Ré-essayez si vous voulez.", "Try again if you'd like to"), COLOR_WHITE);
}
