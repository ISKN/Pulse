/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include "../general.h"
#include "../Graphics/Interpolation.h"

#include "../UI/FontManager.h"
extern FontManager fontManager;
extern Tempo songTempo;

//This class will display a "score" made out of a value and a string, which will slowly go upwards while fading out.
//When it's over, the function is_dead return true.

class ScoreDisplay
{
    public:

        ScoreDisplay();
        ScoreDisplay(int const & value, std::string const & name, ofVec2f const & point, FontManager::Fonts fontType, unsigned fontSize, ofColor const & col, TimePeriod duration = TEMPO_TO_MS(songTempo)); //See the private attributes to understand the parameters.

        void draw();
        bool is_dead() const;


    private:

        int                 _value;         //Score value
        std::string         _name;          //Message displayed with score
		FontManager::Fonts	_fontType;		//The font used to display the score
		int					_fontSize;		//The size of the font

        Interpolation       _position;      //Initial position of the score

        ofVec2f             _gap;           //Distance between string and number

        Interpolation       _alpha;         //Dynamic alpha of the score color
        ofColor             _color;         //Display color
};

#endif // SCOREDISPLAY_H
