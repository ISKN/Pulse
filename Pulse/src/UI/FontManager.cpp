/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "FontManager.h"


FontManager::FontManager()
{
	//Insert your fonts here
	//Watch out: the enum must have the same order
	_fontsNames.push_back(FONT_REGULAR); //regular
	_fontsNames.push_back(FONT_LIGHT); //light
	_fontsNames.push_back(FONT_FUN); //fun
	_fontsNames.push_back(FONT_TITLE); //title

	//Let's prepare the containers
	_fonts.resize(_fontsNames.size());
}

void FontManager::loadBasicFonts()
{
	getFont(Fonts::Regular, getStandardSize());
	getFont(Fonts::Regular, getStandardSize() * 5);
	getFont(Fonts::Regular, getStandardSize() * 2);
	getFont(Fonts::Regular, getStandardSize() * 1.3);
	getFont(Fonts::Regular, getStandardSize() * 0.5);
	getFont(Fonts::Fun, getStandardSize());
	getFont(Fonts::Title, 10 * getStandardSize());
}

ofTrueTypeFont * FontManager::getFont(Fonts type, unsigned size)
{
	int t = (int)type;

	//Start by checking out it the font was already loaded
	FontMap::iterator it = _fonts[t].find(size);
	if (it == _fonts[t].end()) //The font was never loaded
	{
		//Load it
		ofTrueTypeFont tmp;
		_fonts[t][size] = tmp;
		_fonts[t][size].loadFont(_fontsNames[t], size, true, true, true, 0.0, 96);
		DEBUG_MSG("Loading font " << _fontsNames[t] << " with size " << size);
		DEBUG_MSG("Number of sizes for this font: " << _fonts[t].size());
		return & _fonts[t][size];
	}
	//else
		return & it->second;
}

void FontManager::draw(std::string const & text, Fonts font, unsigned size, unsigned x, unsigned y, AlignHoritzontal horizontalAlign, AlignVertical verticalAlign, bool asShapes)
{
	draw(text, font, size, ofVec2f(x, y), horizontalAlign, verticalAlign, asShapes);
}

void FontManager::draw(std::string const & text, Fonts font, unsigned size, ofVec2f const & position, AlignHoritzontal horizontalAlign, AlignVertical verticalAlign, bool asShapes)
{
	//Compute positions
	float xPosition = position.x;
	float yPosition = position.y;

	switch (horizontalAlign)
	{
		case (int)AlignHoritzontal::Left:
			//nothing to do
			break;
		case (int)AlignHoritzontal::Center:
			xPosition -= getWidth(text, font, size) / 2.0f;
			break;
		case (int)AlignHoritzontal::Right:
			xPosition -= getWidth(text, font, size);
			break;
		default:
			ERROR_MSG("Unknown horizontal align parameter: " << (int)horizontalAlign);
			break;
	}

	switch (verticalAlign)
	{
		case (int)AlignVertical::Bottom:
			//nothing to do
			break;
		case (int)AlignVertical::Middle:
			yPosition += getHeight(text, font, size) / 2.0f;
			break;
		case (int)AlignVertical::Top:
			yPosition += getHeight(text, font, size);
			break;
		default:
			ERROR_MSG("Unknown vertical align parameter: " << (int)verticalAlign);
			break;
	}
	
	//Draw the text
	if (asShapes)
	{
		getFont(font, size)->drawStringAsShapes(text, xPosition, yPosition);
	}
	else
	{
		getFont(font, size)->drawString(text, xPosition, yPosition);
	}

	//Debug : draw a circle at the beginning and the end of the text
	/*ofSetColor(COLOR_YELLOW);
	ofCircle(xPosition, yPosition, 15);
	ofCircle(xPosition + getWidth(text, font, size), yPosition, 15);*/
}

float FontManager::getWidth(std::string const & text, Fonts font, unsigned size)
{
	return getFont(font, size)->stringWidth(removeAccents(text)); //Accents can add invisible characters that would give us a wrong result.
}

float FontManager::getHeight(std::string const & text, Fonts font, unsigned size)
{
	return getFont(font, size)->stringHeight(removeAccents(text));
}

float FontManager::getWidth(std::string const & text1, std::string const & text2, Fonts font, unsigned size)
{
	return text1.size() > text2.size() ? getWidth(text1, font, size) : getWidth(text2, font, size);
}

unsigned FontManager::getStandardSize()
{
	return WIDTH / 80 + 1; //it's something
}

std::string FontManager::removeAccents(std::string const & str) const
{
	//This is a very crappy trick but with Windows it was very weird to be able to remove the accents so that's what I ended up doing.
	//(There was probably a problem with ANSI / UTF-8 encoding of source file but i was too lazy rto re-encode them all.)

	std::string result;
	std::string acceptedLetters("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ '!?:.;,-");

	for (unsigned i = 0; i < str.size(); i++)
	{
		if (acceptedLetters.find(str[i]) == std::string::npos)
		{
			if (!result.empty() && result.back() != '_') //Special characters often come up on two bytes
			{
				result.push_back('_'); //Change forbidden letters into '_'.
			}			
		}
		else
		{
			result.push_back(str[i]);
		}
	}

	//DEBUG_MSG("Converted " << str << " to " << result);

	return result;
}