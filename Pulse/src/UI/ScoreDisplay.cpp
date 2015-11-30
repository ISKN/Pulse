/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "ScoreDisplay.h"

ScoreDisplay::ScoreDisplay()
{
    _value = 0;
    _name = std::string("");
	_fontType = FontManager::Fonts::Fun;
	_fontSize = FontManager::getStandardSize();

    _gap = ofVec2f(0, -5);

    _color = COLOR_WHITE;
}

ScoreDisplay::ScoreDisplay(int const& value, std::string const& name, ofVec2f const& point, FontManager::Fonts fontType, unsigned fontSize, ofColor const& col, TimePeriod duration)
 : ScoreDisplay()
{
    _value = value;
    _name = name;
	_fontType = fontType;
	_fontSize = fontSize;

    _color = ofColor::fromHsb(col.getHue(), 200, 150);

	_gap = ofVec2f(0,10);

    _position = Interpolation(point, point + ofVec2f(0, -50), duration, false, Interpolation::EasingIn);
	_alpha = Interpolation(255, 0, duration, false, Interpolation::EasingIn);
}

void ScoreDisplay::draw()
{
    const ofVec2f pos = _position.current_position();
	const unsigned a = std::round(_alpha.current_float_value());

	_color.a = a;
	ofSetColor(_color);

	fontManager.draw(_name, _fontType, _fontSize, ofVec2f(pos.x, pos.y), FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Bottom);
	fontManager.draw(ofToString(_value), _fontType, _fontSize, ofVec2f(pos.x, (pos + _gap).y), FontManager::AlignHoritzontal::Center, FontManager::AlignVertical::Top);
}

bool ScoreDisplay::is_dead() const
{
    return !_position.is_active();
}
