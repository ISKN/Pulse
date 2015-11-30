/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#pragma once

#include "../general.h"

#include "Scene.h"

#include "../UI/FontManager.h"
extern FontManager fontManager;
extern Tempo songTempo;

#include "../UI/ScoreDisplay.h"
#include "../UI/Bttn.h"
#include "Ribbon.h"
#include "Circle.h"
#include "Drum.h"

//A Level is a Scene with an intro, an outro, an exit button, a countdown , etc.

//Some properties for some stuff (intro and outro background, boxes at the corners...)
#define LAYERS_COLOR COLOR_BLACK
#define LAYERS_OPACITY 150
#define BOXES_WIDTH (WIDTH*0.225)
#define BOXES_HEIGHT (HEIGHT*0.30)

#define INTRO_OUTRO_BACKGROUND_COLOR LAYERS_COLOR
#define INTRO_OUTRO_BACKGROUND_OPACITY 40
#define INTRO_OUTRO_BACKGROUND_WIDTH (WIDTH*0.8)
#define INTRO_OUTRO_BACKGROUND_HEIGHT (HEIGHT*0.8)
#define INTRO_OUTRO_BACKGROUND_XMIN (WIDTH - INTRO_OUTRO_BACKGROUND_WIDTH)/2.f
#define INTRO_OUTRO_BACKGROUND_XMAX (INTRO_OUTRO_BACKGROUND_XMIN + INTRO_OUTRO_BACKGROUND_WIDTH)
#define INTRO_OUTRO_BACKGROUND_YMIN (HEIGHT - INTRO_OUTRO_BACKGROUND_HEIGHT)/2.f
#define INTRO_OUTRO_BACKGROUND_YMAX (INTRO_OUTRO_BACKGROUND_YMIN + INTRO_OUTRO_BACKGROUND_HEIGHT)

#define BUTTONS_HEIGHT 0.1*HEIGHT

#define INTRO_OUTRO_X_MARGIN 0.05*WIDTH
#define INTRO_OUTRO_Y_MARGIN 0.1*HEIGHT

class Level : public Scene
{
    public:

		explicit Level(int levelNumber, TimePeriod levelDuration, ofColor const & mainLevelColor, bool hasScore);

		void setMainParams(std::string const & audioFileName, float volume);

		//Basic functions we need to override from Scene
		virtual void setup() override final;
		virtual void update() override final;
		virtual void draw() override final;

		virtual void reset() override final;

		//Useful functions to manage time
		std::string getRemainingTime() const;
		bool isLevelFinished() const;

        ofEvent<void> exitLevel;
		ofEvent<void> goToNextLevel;


	protected:

		//Audio
		ofSoundPlayer _tune;
		std::vector<Drum*> _drums;

		//Gesture analysis
		virtual void processMain(ofVec2f const & point) override;
		virtual void onHit(ofVec2f const & point) {}
		std::list<Circle> _hits;

		//Tempo
		TimePeriod _period;

		//Functions to setup the different parts
		void setupMainElements();		//This one should be used once, inside the startup function	
		void setupIntro();
		void setupOutro();

		void setupStart();				//This one should be used each time the level is restarted, along with setupMain()
		virtual void setupStartMain() = 0;

		//Functions to draw intro and outro
		virtual void drawIntro() = 0;	//This is specific to each level so it must be virtual (and null) here.
		void drawIntroOutroTitle(std::string const & text, ofColor const & color);
		void drawIntroOutroText(std::string const & text, ofColor const & color);
		virtual void drawOutro();				//The outro will show the score, or, if there is no score, then it's the last level, and there will be a specific test.

		//Attributes to manage intro and outro
		bool _introIsActive;
		bool _outroIsActive;

		Bttn _btnExit;
		Bttn _btnReady;
		Bttn _btnReplay, _btnNext;

		//Attributes for the main part of the level
		Bttn _btnExitMain;
		bool _hasScore;
		int _score;
		TimePeriod _levelDuration;
		TimePoint _levelStart;
		bool _levelActive;

		//Main color of the level
		ofColor _levelColor;

		//Useful stuff for the scores
		void newScore(std::string const& name, int const& value, ofVec2f const& pos, ofColor const& color, TimePeriod animationDuration);
		std::deque<ScoreDisplay> _scoresPopup;

		int _levelNumber;
		std::string getScoreFileName() const;
		std::vector<int> getScores() const;
		void saveNewScore(int score);

		int _scoreMin, _scoreMax, _scoreMean;

		//Events (from buttons, mostly)
		void eventExit();
		void eventStart();
		void eventNext();
		void eventLevelFinished();
		virtual void newCue() {}

		//ofShader _background;
};
