/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "Bttn.h"

Bttn::Bttn(std::string const & text_FR, std::string const & text_EN, FontManager::Fonts fontType, unsigned fontSize, ofVec2f const & centerPosition, ofColor const & textColor, float rotation)
{
	_boxCenter = centerPosition;
	_boxWidth = BUTTON_WIDTH_FACTOR * fontManager.getWidth(text_FR, text_EN, fontType, fontSize);
	_boxHeight = BUTTON_HEIGHT_FACTOR * fontManager.getHeight(text_FR, fontType, fontSize);
	_boxRotationValue = rotation;

	_text1_FR = text_FR;
	_text1_EN = text_EN;
	_text1_FontSize = fontSize == 0 ? FontManager::getStandardSize() : fontSize;
	_text1_FontType = fontType;
	_text1_Translation = ofVec2f(0, 0);
	_text1_RotationValue = 0.f;

	_text2_FR = std::string();
	_text2_EN = std::string();
	_text2_FontSize = 0;
	_text2_FontType = FontManager::Fonts::Regular;
	_text2_Position = centerPosition;

	_textColor = textColor;
	_backgroundColor = COLOR_GRAY;
	_hoverStartTime = ofGetElapsedTimeMillis();

	_fillTime = 1500; //ms
	_state = Default;

	//Debug
	//DEBUG_MSG("New button '" << text << "' size " << _text1_FontSize << " at " << centerPosition.x << " " << centerPosition.y << " ; width " << _boxWidth << " height " << _boxHeight << " ; rotation " << rotation);
}

void Bttn::draw()
{
	//Set colors
	ofColor colorBackground, colorText;

	switch (_state)
	{
		case Inactive:
			colorBackground = COLOR_BLACK;
			colorText = COLOR_GRAY;
			break;
		case Default:
			colorBackground = SET_OPACITY(COLOR_BLACK, 150);
			colorText = SET_OPACITY(_textColor, 100);
			break;
		case Hovered:
			colorBackground = SET_OPACITY(COLOR_BLACK, 240);
			colorText = SET_OPACITY(_textColor, 255);
			break;
		case Pressed:
			colorBackground = SET_OPACITY(_textColor, 130);
			colorText = COLOR_WHITE;
			break;
		default:
			ERROR_MSG("Uknown button state " << _state);
			break;
	}

	//Draw background and bar
	ofPushMatrix();

		ofTranslate(_boxCenter);
		ofRotateZ(_boxRotationValue);

		ofPushMatrix();			

			//Box
			ofSetColor(colorBackground);
			ofRect(-(int)_boxWidth / 2, -(int)_boxHeight / 2, _boxWidth, _boxHeight);

			//Bar
			ofSetColor(colorText);
			const unsigned barHeight = _boxHeight / 5;

			float percentage = _state == Hovered ? (float)(ofGetElapsedTimeMillis() - _hoverStartTime) / (float)_fillTime : 0;
			if (percentage >= 1)
			{
				percentage = 1;
				_state = Pressed;
				ofNotifyEvent(clicked);
			}

			ofRect(-(int)_boxWidth / 2, _boxHeight / 2, percentage * _boxWidth, barHeight);

			//Verify center (activate to debug)
			/*ofSetColor(COLOR_ORANGE);
			ofCircle(0, 0, 20);*/

		ofPopMatrix();

	ofPopMatrix();

	//Draw texts
	ofSetColor(colorText);

	fontManager.draw(lang(_text2_FR, _text2_EN), _text2_FontType, _text2_FontSize, _text2_Position, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Middle);
	
	ofVec2f text1Position = _boxCenter;
	if (_text1_FontType == FontManager::Fonts::Regular && (_text1_FR == std::string("1") || _text1_EN == std::string("1"))) //Stupid necessary shit
		text1Position -= ofVec2f(fontManager.getWidth(std::string("1"), _text1_FontType, _text1_FontSize) * 9 / 20, 0);

	ofPushMatrix();

		ofTranslate(text1Position);
		ofRotateZ(_text1_RotationValue);

		ofPushMatrix();

		fontManager.draw(lang(_text1_FR, _text1_EN), _text1_FontType, _text1_FontSize, _text1_Translation, FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Middle);
		
		ofPopMatrix();
	
	ofPopMatrix();
}

void Bttn::enable()
{
    _state = Default;
}

void Bttn::disable()
{
    _state = Inactive;
}

void Bttn::toggleEnabled()
{
    isEnabled() ? disable() : enable();
}

bool Bttn::isEnabled() const
{
    return _state != Inactive;
}

void Bttn::setSecondText(std::string const & text, std::string const & text_EN, FontManager::Fonts fontType, unsigned fontSize, ofVec2f const & position)
{
	_text2_FR = text;
	_text2_EN = text_EN;
	_text2_FontType = fontType;
	_text2_FontSize = fontSize;
	_text2_Position = position;
}

void Bttn::setBoxDimensions(unsigned boxWidth, unsigned boxHeight)
{
	_boxWidth = boxWidth;
	_boxHeight = boxHeight;
}

void Bttn::setPosition(ofVec2f const & position)
{
	_text2_Position += (position - _boxCenter);
	_boxCenter = position;
}

void Bttn::setText1TranslationAndRotation(ofVec2f const & translation, float rotation)
{
	_text1_Translation = translation;
	_text1_RotationValue = rotation;
}

void Bttn::setBackgroundColor(ofColor const & color)
{
	_backgroundColor = color;
}

unsigned Bttn::getWidth() const
{
	return _boxWidth;
}

unsigned Bttn::getHeight() const
{
	return _boxHeight;
}

ofVec2f Bttn::getPosition() const
{
	return _boxCenter;
}

void Bttn::newCursorPosition(ofVec2f const & position)
{
	if (_state == Inactive)
		return;

	const unsigned x = position.x - (_boxCenter.x - _boxWidth/2);
	const unsigned y = position.y - (_boxCenter.y - _boxHeight/2);

    if (x < _boxWidth && y < _boxHeight) //We're inside
    {
        if (_state == Default)
        {
			_hoverStartTime = ofGetElapsedTimeMillis();
			_state = Hovered;
        }
    }
    else
    {
        _state = Default;
    }
}