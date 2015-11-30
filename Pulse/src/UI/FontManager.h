/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#pragma once

#include "../general.h"

/* Description:
 * Pretty useful class that will keep fonts in memory as you load them.
 */

typedef std::map<unsigned, ofTrueTypeFont> FontMap;
typedef std::vector<FontMap> FontMapList;

class FontManager
{
	public:

		enum class Fonts { Regular, Light, Fun, Title };													//Different types of fonts
		enum class AlignHoritzontal { Left, Center, Right };												//Hozitonal alignment
		enum class AlignVertical { Bottom, Middle, Top };													//Vertical alignment

		FontManager();

		void loadBasicFonts();																				//Avoid some annoying loading time during the program's execution

		ofTrueTypeFont * getFont(Fonts type, unsigned size);												//Returns a pointer to the font a type 'type' and size 'size'.

		//Draw 'text' using 'font' with 'size' at (x, y) or 'position' and specified alignment parameters. 'asShapes' is useful if you want to be able to process the text through a vertex shader for instance.
		void draw(std::string const & text, Fonts font, unsigned size, unsigned x, unsigned y, AlignHoritzontal horizontalAlign = AlignHoritzontal::Left, AlignVertical verticalAlign = AlignVertical::Top, bool asShapes = false);
		void draw(std::string const & text, Fonts font, unsigned size, ofVec2f const & position, AlignHoritzontal horizontalAlign = AlignHoritzontal::Left, AlignVertical verticalAlign = AlignVertical::Top, bool asShapes = false);

		float getWidth(std::string const & text, Fonts font, unsigned size);								//Returns the width in pixels of the 'text' as rendered by the 'font' with 'size'
		float getHeight(std::string const & text, Fonts font, unsigned size);								//Same thing with the height.
		float getWidth(std::string const & text1, std::string const & text2, Fonts font, unsigned size);	//Returns the biggest width between 'text1' and 'text2'.

		static unsigned getStandardSize();																	//Returns the standard size corresponding to the resolution.

		std::string removeAccents(std::string const & str) const;											//Returns the string without accents (can be useful to evaluate the width of a string while ignoring character encoding problems).


	private:

		std::vector<std::string> _fontsNames;																//A list of the different fonts.
		FontMapList _fonts;																					//Behaves almost like a 2D matrix : a call to _fonts[font type][font size] will create the font if it doesn't exist and simply return it if it does exist.


};

