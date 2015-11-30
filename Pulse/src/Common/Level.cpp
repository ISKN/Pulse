/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Level.h"

Level::Level(int levelNumber, TimePeriod levelDuration, ofColor const & mainLevelColor, bool hasScore)
: Scene(), _levelNumber(levelNumber), _levelDuration(levelDuration), _levelColor(mainLevelColor), _hasScore(hasScore)
{
}

void Level::setMainParams(std::string const & audioFileName, float volume)
{
	_period = TEMPO_TO_MS(songTempo);
	_tune.loadSound(ofToDataPath(audioFileName));
	_tune.setVolume(volume);
}

void Level::setup()
{
	_introIsActive = true;
	_outroIsActive = false;

	_levelActive = false;

	//_background.load(ofToDataPath("shaders/smoke.vert"), ofToDataPath("shaders/smoke.frag"));
	//_background.load(ofToDataPath("shaders/voronoi.vert"), ofToDataPath("shaders/voronoi.frag"));

	//Other
	setupIntro();
	setupMainElements();
	setupMain();
	setupOutro();
}

void Level::update()
{
	if (_enabled)
	{
		if (!_introIsActive && !_outroIsActive)
		{
			if (isLevelFinished())
				eventLevelFinished();

			updateMain();
		}
	}
}

void Level::draw()
{
	if (_enabled)
	{
		/*_background.begin();

			_background.setUniform1f("time", ofGetElapsedTimef()*0.3);
			_background.setUniform2f("resolution", WIDTH, HEIGHT);
			ofSetColor(1, 1, 1);
			ofRect(0, 0, WIDTH, HEIGHT);

		_background.end();*/


		if (_introIsActive)
		{
			drawIntro();

			//ofSetColor(COLOR_GRAY);
			//fontManager.draw(std::string("Quand vous serez prêt, activez le bouton \"Jouer\" en bas à droite."), 
			//	FontManager::Fonts::Regular, fontManager.getStandardSize() * 0.8, INTRO_OUTRO_BACKGROUND_XMAX - INTRO_OUTRO_X_MARGIN, INTRO_OUTRO_BACKGROUND_YMAX + -1.3*BUTTONS_HEIGHT, FontManager::AlignHoritzontal::Right, FontManager::AlignVertical::Middle);
				
			_btnExit.draw();
			_btnReady.draw();
		}
		else if (_outroIsActive)
		{
			drawOutro();

			_btnExit.draw();
			_btnReplay.draw();
			if (_hasScore) //Means it's not the last level || TODO: make this clean.
				_btnNext.draw();
		}
		else
		{
			drawMain();

			//Draw time
			ofPushMatrix();

			if (_levelDuration > 0)
			{
				ofTranslate(0, 0);
				ofRotateZ(-45);

				ofSetColor(SET_OPACITY(LAYERS_COLOR, LAYERS_OPACITY));
				ofRect(-BOXES_WIDTH / 2.f, -BOXES_HEIGHT / 2.f, BOXES_WIDTH, BOXES_HEIGHT);

				ofSetColor(_levelColor);
				fontManager.draw(getRemainingTime(), FontManager::Fonts::Regular, FontManager::getStandardSize()*1.5, 0, BOXES_HEIGHT / 3.f, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Middle);
			}

			ofPopMatrix();

			//Draw score
			ofPushMatrix();

			if (_hasScore)
			{
				ofTranslate(WIDTH, 0);
				ofRotateZ(45);

				ofSetColor(SET_OPACITY(LAYERS_COLOR, LAYERS_OPACITY));
				ofRect(-BOXES_WIDTH / 2.f, -BOXES_HEIGHT / 2.f, BOXES_WIDTH, BOXES_HEIGHT);

				ofSetColor(_levelColor);
				fontManager.draw(ofToString(_score), FontManager::Fonts::Regular, FontManager::getStandardSize()*1.5, 0, BOXES_HEIGHT / 3.f, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Middle);
			}

			ofPopMatrix();

			//Draw drums
			for (unsigned i = 0; i < _drums.size(); i++)
			{
				_drums[i]->draw(_ribbon.getHead());
			}

			//Draw scores popup
			for (ScoreDisplay & s : _scoresPopup)
			{
				s.draw();
			}

			//Draw hits
			for (Circle & m : _hits)
			{
				m.draw();
			}

			//Draw exit
			_btnExitMain.draw();
		}

		_ribbon.draw();

	}
}

void Level::reset()
{
	_introIsActive = true;
	_outroIsActive = false;
	_btnExit.enable();
	_btnNext.disable();
	_btnReady.enable();
	_btnReplay.disable();
	_btnExitMain.enable();
	_scoresPopup.clear();
	_levelActive = false;
}

std::string Level::getRemainingTime() const
{
	if (isLevelFinished())
	{
		return std::string("00:00");
	}
	//else
		TimePeriod remaining = _levelDuration - (ofGetElapsedTimeMillis() - _levelStart);
		unsigned seconds = (remaining / 1000) % 60;
		unsigned minutes = remaining / 1000 / 60;

		std::stringstream ss;
		ss << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;

		return ss.str();
}

bool Level::isLevelFinished() const
{
	return ofGetElapsedTimeMillis() - _levelStart >= _levelDuration;
}

void Level::processMain(ofVec2f const & point)
{
	if (_levelActive)
	{
		for (unsigned i = 0; i < _drums.size(); i++)
		{
			if (_drums[i]->validHit(point))
			{
				onHit(point);

				Circle m(_period, 0.f, _ribbon.getHead(), CIRCLE_RADIUS, CIRCLE_INNER_RADIUS_FACTOR);
				m.fill(0);
				m.hit(_period / 2, 2 * CIRCLE_RADIUS, true);
				_hits.push_back(m);
				_hits.erase(std::remove_if(_hits.begin(), _hits.end(), [](Circle const& c){return c.hitFinished(); }), _hits.end()); //God bless lambda functions.
			}
		}
	}
}

void Level::setupMainElements()
{
	_btnExitMain = Bttn("Quitter", "Quit", FontManager::Fonts::Regular, FontManager::getStandardSize()*1.5, ofVec2f(0, HEIGHT), _levelColor, -135);
	_btnExitMain.setBoxDimensions(BOXES_WIDTH, BOXES_HEIGHT);
	_btnExitMain.setText1TranslationAndRotation(ofVec2f(0, -BOXES_HEIGHT / 3.f), -135 + 180);

	ofAddListener(_btnExitMain.clicked, this, &Level::eventExit);
	registerButton(&_btnExitMain);
	_btnExitMain.disable();
}

void Level::setupStart()
{
	_score = 0;
	_levelActive = true;
	_scoresPopup.clear();

	setupStartMain();

	_tune.play();

	_levelStart = ofGetElapsedTimeMillis();
}

void Level::setupIntro()
{
	_btnExit = Bttn("Quitter", "Quit",
		FontManager::Fonts::Regular, FontManager::getStandardSize(), 
		ofVec2f(INTRO_OUTRO_BACKGROUND_XMIN + BUTTON_WIDTH_FACTOR * fontManager.getWidth("Quitter", "Quit", FontManager::Fonts::Regular, FontManager::getStandardSize()) / 2.f, 
		INTRO_OUTRO_BACKGROUND_YMAX - BUTTONS_HEIGHT / 2.f),
		_levelColor);

	_btnExit.setBoxDimensions(_btnExit.getWidth(), BUTTONS_HEIGHT);
	_btnExit.setBackgroundColor(COLOR_WHITE);
	ofAddListener(_btnExit.clicked, this, &Level::eventExit);
	registerButton(&_btnExit);

	_btnReady = Bttn("Jouer", "Play",
		FontManager::Fonts::Regular, FontManager::getStandardSize(),
		ofVec2f(INTRO_OUTRO_BACKGROUND_XMAX - BUTTON_WIDTH_FACTOR * fontManager.getWidth("Jouer", "Play", FontManager::Fonts::Regular, FontManager::getStandardSize()) / 2.f,
		INTRO_OUTRO_BACKGROUND_YMAX - BUTTONS_HEIGHT / 2.f),
		_levelColor);

	_btnReady.setBoxDimensions(_btnReady.getWidth(), BUTTONS_HEIGHT);
	_btnReady.setBackgroundColor(COLOR_WHITE);
	ofAddListener(_btnReady.clicked, this, &Level::eventStart);
	registerButton(&_btnReady);
}

void Level::setupOutro()
{
	//_btnExit was already created

	_btnReplay = Bttn("Rejouer", "Play again",
		FontManager::Fonts::Regular, FontManager::getStandardSize(),
		ofVec2f(WIDTH/2,
		INTRO_OUTRO_BACKGROUND_YMAX - BUTTONS_HEIGHT / 2.f),
		_levelColor);

	_btnReplay.setBoxDimensions(_btnReplay.getWidth(), BUTTONS_HEIGHT);
	_btnReplay.setBackgroundColor(COLOR_WHITE);
	ofAddListener(_btnReplay.clicked, this, &Level::eventStart);
	registerButton(&_btnReplay);
	_btnReplay.disable();

	_btnNext = Bttn("Continuer", "Continue",
		FontManager::Fonts::Regular, FontManager::getStandardSize(),
		ofVec2f(INTRO_OUTRO_BACKGROUND_XMAX - BUTTON_WIDTH_FACTOR * fontManager.getWidth("Continuer", "Continue", FontManager::Fonts::Regular, FontManager::getStandardSize()) / 2.f,
		INTRO_OUTRO_BACKGROUND_YMAX - BUTTONS_HEIGHT / 2.f),
		_levelColor);

	_btnNext.setBoxDimensions(_btnNext.getWidth(), BUTTONS_HEIGHT);
	_btnNext.setBackgroundColor(COLOR_WHITE);
	ofAddListener(_btnNext.clicked, this, &Level::eventNext);
	registerButton(&_btnNext);
	_btnNext.disable();
}

void Level::drawIntroOutroTitle(std::string const & text, ofColor const & color)
{
	ofSetColor(color);
	fontManager.draw(text, FontManager::Fonts::Regular, fontManager.getStandardSize() * 2, WIDTH / 2, INTRO_OUTRO_BACKGROUND_YMIN + INTRO_OUTRO_Y_MARGIN, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Top);
}

void Level::drawIntroOutroText(std::string const & text, ofColor const & color)
{
	ofSetColor(color);
	fontManager.draw(text, FontManager::Fonts::Regular, fontManager.getStandardSize(), WIDTH / 2, INTRO_OUTRO_BACKGROUND_YMIN + 2 * INTRO_OUTRO_Y_MARGIN + fontManager.getHeight("Title", FontManager::Fonts::Regular, fontManager.getStandardSize() * 2), FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Top);
}

int roundUpToMultiple(int number, int multiple)
{
	if (multiple == 0)
		return number;

	int tmp = number % multiple;

	if (tmp == 0)
		return number;

	return number + multiple - tmp;
}

void Level::drawOutro()
{
	ofSetColor(_levelColor);
	fontManager.draw(lang("Résumé du niveau", "Level summary"), FontManager::Fonts::Regular, fontManager.getStandardSize() * 2, WIDTH / 2, INTRO_OUTRO_BACKGROUND_YMIN + INTRO_OUTRO_Y_MARGIN, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Top);

	if (_hasScore)
	{
		ofSetColor(COLOR_DARK);

		/*
		std::stringstream ss;
		ss << "Votre score : " << _score
			<< "\nMeilleur score : " << _scoreMax
			<< "\nMoins bon score : " << _scoreMin
			<< "\nMoyenne : " << _scoreMean;

		fontManager.draw(ss.str(),
			FontManager::Fonts::Regular, fontManager.getStandardSize(), INTRO_OUTRO_BACKGROUND_XMIN + INTRO_OUTRO_X_MARGIN,
			INTRO_OUTRO_BACKGROUND_YMIN + 1.5 * INTRO_OUTRO_Y_MARGIN + fontManager.getHeight("Title", FontManager::Fonts::Regular, fontManager.getStandardSize() * 2), FontManager::AlignHoritzontal::Left, FontManager::AlignVertical::Top);
		*/

		//Useful variables for score display
		const float width = INTRO_OUTRO_BACKGROUND_WIDTH - 2.5 * INTRO_OUTRO_X_MARGIN;
		const float xMin = WIDTH/2.f - width/2.f;
		const float height = 0.1 * HEIGHT;
		const float yMin = INTRO_OUTRO_BACKGROUND_YMIN + 3.5 * INTRO_OUTRO_Y_MARGIN;
		const float gapX = 10.f;
		const float gapY = 1.5f * fontManager.getHeight("Text", FontManager::Fonts::Regular, fontManager.getStandardSize());

		const int scoreLimit = roundUpToMultiple(_scoreMax, 1000);
		const float xScoreMin = xMin + width * (float)_scoreMin / (float)scoreLimit;
		const float xScoreMax = xMin + width * (float)_scoreMax / (float)scoreLimit;
		const float xScoreUser = xMin + width * (float)_score / (float)scoreLimit;

		//Score container
		ofSetColor(_levelColor);
		ofSetLineWidth(4);
		ofLine(xMin, yMin, xMin, yMin + height);
		ofLine(xMin + width, yMin, xMin + width, yMin + height);
		ofLine(xMin, yMin, xMin + width, yMin);
		ofLine(xMin, yMin + height, xMin + width, yMin + height);

		//Score bar
		ofSetColor(_levelColor);
		ofRect(xScoreMin, yMin, xScoreMax - xScoreMin, height);

		//Limits
		ofSetColor(COLOR_DARK);
		fontManager.draw(ofToString(0), FontManager::Fonts::Regular, fontManager.getStandardSize(), xMin - gapX, yMin + height/2.f, FontManager::AlignHoritzontal::Right, FontManager::AlignVertical::Middle);
		fontManager.draw(ofToString(scoreLimit), FontManager::Fonts::Regular, fontManager.getStandardSize(), xMin + width + gapX, yMin + height / 2.f, FontManager::AlignHoritzontal::Left, FontManager::AlignVertical::Middle);

		//Min and max score info
		ofSetColor(_levelColor);
		fontManager.draw(lang("Meilleur score", "Best score"), FontManager::Fonts::Regular, fontManager.getStandardSize(), xScoreMax, yMin - gapY, FontManager::AlignHoritzontal::Right, FontManager::AlignVertical::Middle);
		fontManager.draw(ofToString(_scoreMax), FontManager::Fonts::Regular, fontManager.getStandardSize(), xScoreMax, yMin - 2*gapY, FontManager::AlignHoritzontal::Right, FontManager::AlignVertical::Middle);
		fontManager.draw(lang("Moins bon score", "Worst score"), FontManager::Fonts::Regular, fontManager.getStandardSize(), xScoreMin, yMin - gapY, FontManager::AlignHoritzontal::Left, FontManager::AlignVertical::Middle);
		fontManager.draw(ofToString(_scoreMin), FontManager::Fonts::Regular, fontManager.getStandardSize(), xScoreMin, yMin - 2*gapY, FontManager::AlignHoritzontal::Left, FontManager::AlignVertical::Middle);

		//User score info
		ofSetColor(COLOR_WHITE);
		fontManager.draw(lang("Votre score", "Your score"), FontManager::Fonts::Regular, fontManager.getStandardSize(), xScoreUser, yMin + height + gapY, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Middle);
		fontManager.draw(ofToString(_score), FontManager::Fonts::Regular, fontManager.getStandardSize(), xScoreUser, yMin + height + 2 * gapY, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Middle);
		
		//User score line
		ofSetColor(COLOR_WHITE);
		ofSetLineWidth(4);
		ofLine(xScoreUser, yMin, xScoreUser, yMin + height);

		//Conclusion
		ofSetColor(_levelColor);
		if (_score < _scoreMean)
		{
			fontManager.draw(lang("Hmm... Vous devriez peut-être ré-essayer...", "Hmm... Maybe you should try again..."), FontManager::Fonts::Regular, fontManager.getStandardSize(),
				WIDTH / 2, INTRO_OUTRO_BACKGROUND_YMAX - 2 * INTRO_OUTRO_Y_MARGIN, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Middle);
		}
		else if (_score >= _scoreMean && _score < _scoreMax * 0.9)
		{
			fontManager.draw(lang("Vous avez fait mieux que la plupart des gens. Bravo !", "You did better than most people. Good job!"), FontManager::Fonts::Regular, fontManager.getStandardSize(),
				WIDTH / 2, INTRO_OUTRO_BACKGROUND_YMAX - 2 * INTRO_OUTRO_Y_MARGIN, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Middle);
		}
		else if (_score >= _scoreMax * 0.9 && _score < _scoreMax)
		{
			fontManager.draw(lang("Excellent ! Vous êtes très proche du meilleur score !", "Very good! You're really close to the top score!"), FontManager::Fonts::Regular, fontManager.getStandardSize(),
				WIDTH / 2, INTRO_OUTRO_BACKGROUND_YMAX - 2 * INTRO_OUTRO_Y_MARGIN, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Middle);
		}
		else
		{
			fontManager.draw(lang("Wouah !! Vous avez battu le record !", "Wow!! You just broke the record!"), FontManager::Fonts::Regular, fontManager.getStandardSize(),
				WIDTH / 2, INTRO_OUTRO_BACKGROUND_YMAX - 2 * INTRO_OUTRO_Y_MARGIN, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Middle);
		}
	}
	else
	{
		fontManager.draw("Fin", FontManager::Fonts::Regular, fontManager.getStandardSize(), WIDTH / 2, HEIGHT / 2);
	}
}

void Level::newScore(std::string const& name, int const& value, ofVec2f const& pos, ofColor const& color, TimePeriod animationDuration)
{
	_scoresPopup.erase(std::remove_if(_scoresPopup.begin(), _scoresPopup.end(), [](ScoreDisplay const& s){return s.is_dead(); }), _scoresPopup.end()); //God bless lambda functions.
	_scoresPopup.emplace_back(value, name, pos, FontManager::Fonts::Fun, FontManager::getStandardSize(), color, animationDuration);
	_score += value;
}

std::string Level::getScoreFileName() const
{
	return ofToDataPath(std::string("score") + ofToString(_levelNumber) + std::string(".xml"));
}

std::vector<int> Level::getScores() const
{
	ofXml scoreFile;
	std::vector<int> scores;

	if (!scoreFile.load(getScoreFileName()))
	{
		ERROR_MSG("(Loading) No score file was found for level " << _levelNumber << " ! Creating one");
		scoreFile.addChild("Scores");
		scoreFile.save(getScoreFileName());
	}
	else
	{
		if (scoreFile.exists("Score"))
		{
			//scoreFile.setTo("Scores");
			scoreFile.setTo("Score[0]");

			do 
			{
				scores.push_back(scoreFile.getValue<int>("Value"));

			} while (scoreFile.setToSibling()); //next score
		}
		else
		{
			DEBUG_MSG("(Loading) Score file existed for level " << _levelNumber << " but no score was found");
		}
	}

	DEBUG_MSG("Loading scores for level " << _levelNumber << ": " << scores.size() << " scores loaded");

	return scores;
}

void Level::saveNewScore(int score)
{
	if (score < -1000) //Might be a bug
		score = 0;

	ofXml scoreFile;

	if (!scoreFile.load(getScoreFileName()))
	{
		ERROR_MSG("(Saving) No score file was found for level " << _levelNumber << " ! Creating one");
		scoreFile.addChild("Scores");
	}
	else
	{
		if (!scoreFile.exists("Score"))
		{
			DEBUG_MSG("(Saving) Score file existed for level " << _levelNumber << " but no score was found");
			scoreFile.addChild("Scores");
		}

		//scoreFile.setTo("Scores");

		scoreFile.addChild("Score");
		scoreFile.setToChild(scoreFile.getNumChildren() - 1);

		std::stringstream date;
		date << std::setfill('0') << std::setw(2) << ofGetDay() << "/" << ofGetMonth() << "/" << ofGetYear() << " - " << ofGetHours() << ":" << ofGetMinutes() << ":" << ofGetSeconds();
		scoreFile.addValue("Date", date.str());

		scoreFile.addValue("Value", score);

		DEBUG_MSG("Saving new score for level " << _levelNumber << ": " << score << " on " << date.str());
	}

	scoreFile.save(getScoreFileName());
}

void Level::eventExit()
{
	_tune.stop();

	std::stringstream ss;
	ss << "LEVEL " << _levelNumber << " exit";
	notifyMainLog(ss.str());

	_levelActive = false;
	ofNotifyEvent(exitLevel);
}

void Level::eventStart()
{
	std::stringstream ss;
	ss << "LEVEL " << _levelNumber << " start";
	notifyMainLog(ss.str());

	_levelActive = true;
	_introIsActive = false;
	_outroIsActive = false;
	_btnExit.disable();
	_btnNext.disable();
	_btnReady.disable();
	_btnReplay.disable();
	_btnExitMain.enable();
	setupStart();
}

void Level::eventNext()
{
	_levelActive = false;
	ofNotifyEvent(goToNextLevel);
}

void Level::eventLevelFinished()
{
	_tune.stop();

	std::stringstream ss;
	ss << "LEVEL " << _levelNumber << " finished";
	notifyMainLog(ss.str());

	_levelActive = false;
	//Stop player

	DEBUG_MSG("Level ended with score " << _score);

	//Activate outro
	_introIsActive = false;
	_outroIsActive = true;
	_btnExit.enable();
	_btnNext.enable();
	_btnReady.disable();
	_btnReplay.enable();
	_btnExitMain.disable();

	if (_hasScore)
	{
		//Get scores
		std::vector<int> scores = getScores();
		_scoreMin = 0;
		_scoreMax = 0;
		_scoreMean = 0;
		if (!scores.empty())
		{
			_scoreMin = *std::min_element(scores.begin(), scores.end());
			_scoreMax = *std::max_element(scores.begin(), scores.end());
			_scoreMean = std::accumulate(scores.begin(), scores.end(), _score) / (scores.size() + 1);
		}

		//Save current score
		saveNewScore(_score);
	}
}
