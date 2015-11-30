/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#ifndef BUTTON_H
#define BUTTON_H

/* Object representing a button handling being hoevered, clicked, disabled... */

#include "../general.h"

#include "Language.h"
#include "FontManager.h"
extern FontManager fontManager;

#define BUTTON_WIDTH_FACTOR 2	//Need this for reasons
#define BUTTON_HEIGHT_FACTOR 3	//bis.

class Bttn //Couldn't name it Button because of fucking windows #fuckDisShit
{
    public:

		Bttn(std::string const & text_FR = std::string(), std::string const & text_EN = std::string(), FontManager::Fonts fontType = FontManager::Fonts::Regular, unsigned fontSize = 0, ofVec2f const & centerPosition = ofVec2f(WIDTH / 2, HEIGHT / 2), ofColor const & textColor = COLOR_WHITE, float rotation = 0);
		
        void draw();

        void enable();
        void disable();
        void toggleEnabled();
        bool isEnabled() const;

		void setSecondText(std::string const & text, std::string const & text_EN, FontManager::Fonts fontType, unsigned fontSize, ofVec2f const & position);
		void setBoxDimensions(unsigned boxWidth, unsigned boxHeight);
        void setPosition(ofVec2f const & position);
		void setText1TranslationAndRotation(ofVec2f const & translation, float rotation);
		void setBackgroundColor(ofColor const & color);

        unsigned getWidth() const;
        unsigned getHeight() const;
		ofVec2f getPosition() const;

        void newCursorPosition(ofVec2f const & position);

        ofEvent<void> clicked;


    private:

		//Box
		ofVec2f		_boxCenter;
		unsigned	_boxWidth;
		unsigned	_boxHeight;
		float		_boxRotationValue;

		//First text
		std::string			_text1_FR;
		std::string			_text1_EN;
		unsigned			_text1_FontSize;
		FontManager::Fonts	_text1_FontType;
		ofVec2f				_text1_Translation;
		float				_text1_RotationValue;

		//Second text
		std::string			_text2_FR;
		std::string			_text2_EN;
		unsigned			_text2_FontSize;
		FontManager::Fonts	_text2_FontType;
		ofVec2f				_text2_Position;

		//General stuff
        ofColor     _textColor;
		ofColor		_backgroundColor;
        TimePoint   _hoverStartTime;

        enum States { Inactive, Default, Hovered, Pressed };
        int _state;

		TimePeriod _fillTime; //ms

};

#endif // BUTTON_H
