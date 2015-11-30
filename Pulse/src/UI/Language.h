/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#pragma once

#include "../general.h"

/* Simple tool to handle multiple languages (by default, the language is english but it is very easy to add a button to trigger a language change). */

//Languages
#define FR 0
#define EN 1

//Global var
#ifndef DEFINE_EXTERN_HERE
extern int _lang;
#else
int _lang;
#endif

//Functions
std::string lang(std::string const & fr, std::string const & en);	//Returns the fr or en string depending on the _lang parameter.
std::string lang(char * fr, char * en);								//Same thing with char*.

void setLanguage(int value);										//Change the current language to "value".
void setFR();														//Change to french.
void setEN();														//Change to english.
void toggleLanguage();												//Change to FR if current lang is EN and reciprocally.