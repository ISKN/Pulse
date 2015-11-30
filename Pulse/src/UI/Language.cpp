/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#define DEFINE_EXTERN_HERE
#include "Language.h"

std::string lang(std::string const & fr, std::string const & en)
{
	if (_lang == FR)
	{
		return fr;
	}
	else if (_lang == EN)
	{
		return en;
	}
	
	ERROR_MSG("Unknown language: " << _lang);
	return en; //Return english by default.
}

std::string lang(char * fr, char * en)
{
	return lang(std::string(fr), std::string(en));
}

void setLanguage(int value)
{
	_lang = value;
	DEBUG_MSG("New language is " << _lang);
}

void setFR()
{
	setLanguage(FR);
}

void setEN()
{
	setLanguage(EN);
}

void toggleLanguage()
{
	_lang = (_lang + 1) % 2;
	DEBUG_MSG("Switched to language " << _lang);
}