/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Menu.h"

Menu::Menu()
 : Scene()
{
}

void Menu::reset()
{
	_bandWarmingUp.play();
}

void Menu::setupMain()
{
	_btnLang = Bttn("English", "Français", FontManager::Fonts::Regular, FontManager::getStandardSize(), ofVec2f(WIDTH*0.3, HEIGHT*0.9), COLOR_BLACK);

	const float numbersSizeFactor = 8.f;
	const unsigned numbersHeight = fontManager.getHeight("1", FontManager::Fonts::Regular, FontManager::getStandardSize() * numbersSizeFactor);
	const unsigned subTextWidth = fontManager.getWidth("Unleash your Talent", "Unleash your Talent", FontManager::Fonts::Regular, FontManager::getStandardSize());
	const unsigned sideLength = std::max(numbersHeight, subTextWidth) * 1.1;

	_btnLevel1 = Bttn("1", "1", FontManager::Fonts::Regular, FontManager::getStandardSize()*numbersSizeFactor, ofVec2f(WIDTH*0.25, HEIGHT*0.65), COLOR_MAIN_1);
	_btnLevel1.setBoxDimensions(sideLength, sideLength);
	_btnLevel1.setSecondText("Suivez le rythme", "Keep the Beat", FontManager::Fonts::Regular, FontManager::getStandardSize(), _btnLevel1.getPosition() + ofVec2f(0, numbersHeight / 2 + FontManager::getStandardSize()));

	_btnLevel2 = Bttn("2", "2", FontManager::Fonts::Regular, FontManager::getStandardSize()*numbersSizeFactor, ofVec2f(WIDTH*0.75, HEIGHT*0.65), COLOR_MAIN_2);
	_btnLevel2.setBoxDimensions(sideLength, sideLength);
	_btnLevel2.setSecondText("Déchaînez-vous", "Unleash your Talent", FontManager::Fonts::Regular, FontManager::getStandardSize(), _btnLevel2.getPosition() + ofVec2f(0, numbersHeight / 2 + FontManager::getStandardSize()));
	
	ofAddListener(_btnLang.clicked, this, &Menu::btnLangClicked);
	ofAddListener(_btnLevel1.clicked, this, &Menu::btnLevel1Clicked);
	ofAddListener(_btnLevel2.clicked, this, &Menu::btnLevel2Clicked);

	clearButtons();
	//registerButton(&_btnLang);
	registerButton(&_btnLevel1);
	registerButton(&_btnLevel2);

	_titleFX.load(ofToDataPath("shaders/title.vert"), ofToDataPath("shaders/title.frag"));
	//_background.load(ofToDataPath("shaders/voronoi.vert"), ofToDataPath("shaders/voronoi.frag"));
	_bandWarmingUp.loadSound(ofToDataPath("fx/cheering.mp3"));
	_bandWarmingUp.setLoop(true);
}

void Menu::updateMain()
{
}

void Menu::drawMain()
{
	/*_background.begin();

		_background.setUniform1f("time", ofGetElapsedTimef()*0.3);
		_background.setUniform2f("resolution", WIDTH, HEIGHT);
		ofSetColor(1, 1, 1);
		ofRect(0, 0, WIDTH, HEIGHT);

	_background.end();*/

	_titleFX.begin();

		_titleFX.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1);
		_titleFX.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18);
		_titleFX.setUniform2f("mouse", _ribbon.getHead().x - WIDTH / 2, HEIGHT - _ribbon.getHead().y - HEIGHT / 4);

		ofSetColor(ofFloatColor::fromHsb(_ribbon.getColor().getHue(), 0.8, 0.9, 0.9));
		fontManager.draw("PULSE", FontManager::Fonts::Title, FontManager::getStandardSize() * 10, WIDTH / 2, HEIGHT*0.1, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Top, true);

	_titleFX.end();

	//_btnLang.draw();
    _btnLevel1.draw();
	_btnLevel2.draw();
}

void Menu::processMain(ofVec2f const& point)
{
	/* Compute ribbon color */

	//Positions on the x axis of the main buttons
	const std::vector<float> mainButtonsXPositions{ WIDTH*0.25f, WIDTH*0.75f };

	//Hues
	const std::vector<float> mainHues{ ((float)COLOR_MAIN_1.getHue()) / 255.f,
		((float)COLOR_MAIN_2.getHue()) / 255.f };

	//Compute hue
	float hue;

	if (point.x <= mainButtonsXPositions.front()) //Special case if we're outside the buttons
		hue = mainHues.front();
	else if (point.x >= mainButtonsXPositions.back()) //Special case if we're outside the buttons
		hue = mainHues.back();
	else
	{
		//Identify the two extremities of the gradient (in case there are more than 2 buttons)
		float hue1, hue2;
		float pos1, pos2;
		for (unsigned i = 0; i < mainButtonsXPositions.size() - 1; i++)
		{
			if (mainButtonsXPositions[i] <= point.x)
			{
				hue1 = mainHues[i];
				pos1 = mainButtonsXPositions[i];
				hue2 = mainHues[i + 1];
				pos2 = mainButtonsXPositions[i + 1];
			}
		}

		//Compute x position (between 0 and 1)
		const float x = (point.x - pos1) / (pos2 - pos1);

		//Blend hues
		hue = hueBlending(hue1, hue2, x);
	}

	//Compute saturation
	const float buttonsHeight = HEIGHT*0.65f;
	const float difference = std::abs(point.y - buttonsHeight);
	const float saturation = difference / (float)(HEIGHT - buttonsHeight);

	//Compute brightness
	const float brightness = (((float)COLOR_MAIN_1.getBrightness()) / 255.f
		+ ((float)COLOR_MAIN_2.getBrightness()) / 255.f) / 2.f;

	_ribbon.setColor(ofFloatColor::fromHsb(hue, saturation, brightness, 1.f));
}

void Menu::btnLangClicked()
{
	if (this->isEnabled())
	{
		DEBUG_MSG("language clicked");
		toggleLanguage();
	}
}

void Menu::btnLevel1Clicked()
{
    if (this->isEnabled())
    {
		_bandWarmingUp.stop();
        DEBUG_MSG("level1 clicked");
        int tmp = PART_NUMBER_LEVEL1; //Seems stupid but is actually needed since events parameters are references
        ofNotifyEvent(eventChangePart, tmp, this);
    }
}

void Menu::btnLevel2Clicked()
{
    if (this->isEnabled())
    {
		_bandWarmingUp.stop();
        DEBUG_MSG("level2 clicked");
        int tmp = PART_NUMBER_LEVEL2;
        ofNotifyEvent(eventChangePart, tmp, this);
    }
}
