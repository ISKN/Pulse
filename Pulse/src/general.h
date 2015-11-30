/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
 * This work is free. You can redistribute it and / or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.See the LICENSE file for more details.
 */

#ifndef GENERAL_HPP
#define GENERAL_HPP

//Includes 
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <list>
#include <memory>
#include <string>
#include <sstream>
#include <locale>
#include <codecvt>
#include <mutex>
#include <fstream>

#include "ofMain.h"

#include "Tools/FixedSizeList.hpp"

//Display
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define USE_SPLASH_SCREEN //Displays the iskn logo while the software starts
#define FULLSCREEN_MODE

//Slate
//#define REPLACE_SLATE_BY_MOUSE //If enabled, the slate won't be used and will be replaced by the mouse

//Display
#define WIDTH ofGetWidth()
#define HEIGHT ofGetHeight()

//Fonts
#define FONT_REGULAR "fonts/Muli-Regular.ttf"
#define FONT_LIGHT   "fonts/Muli-Light.ttf"
#define FONT_FUN     "fonts/ObelixPro-cyr.ttf"
#define FONT_TITLE   "fonts/Adamas-Regular.ttf"

//Useful stuff
#define TEMPO_TO_MS(x) std::round(60000/(double)(x))
#define MS_TO_TEMPO(x) std::round(60000/(double)(x))
#define SAMPLES_TO_TEMPO(x) MS_TO_TEMPO(double((x)*1000.0)/(double)AUDIO_SAMPLERATE)

#define MAKE_NON_COPYABLE(class) \
    class(const class& other) = delete; \
    class& operator = (const class&) = delete;

//Colors
#define COLOR_WHITE  ofColor(236, 240, 241, 255)
#define COLOR_GRAY   ofColor(189, 195, 199, 255)
#define COLOR_MID    ofColor(95, 102, 103, 255)
#define COLOR_DARK   ofColor(65, 73, 70, 255)
#define COLOR_BLACK  ofColor(9, 5, 4, 255)

#define COLOR_MAIN_1 ofColor(0, 118, 255, 255)
#define COLOR_MAIN_2 ofColor(255, 40, 40, 255)

#define COLOR_BLUE   ofColor(52, 152, 219, 255)
#define COLOR_GREEN  ofColor(46, 204, 113, 255)
#define COLOR_ORANGE ofColor(230, 126, 34, 255)
#define COLOR_YELLOW ofColor(241, 196, 15, 255)
#define COLOR_RED    ofColor(231, 76, 60, 255)
#define COLOR_VIOLET ofColor(155, 89, 182, 255)

#define SET_OPACITY(color, value) \
    ofColor::fromHex(color.getHex(), value)
#define DARKEN(color) \
    ofColor::fromHex(color.getHex() & 0xAAAAAA)

//Parts (always start from 0)
#define PART_NUMBER_MENU        0
#define PART_NUMBER_LEVEL1      1
#define PART_NUMBER_LEVEL2      2

#define NUMBER_OF_PARTS      (PART_NUMBER_LEVEL2+1)

//Typedefs
typedef unsigned long long  TimePoint;
typedef unsigned long long  TimePeriod;
typedef unsigned            Tempo;
typedef float				Sample;
typedef unsigned long		SamplePos;

//Messages
extern "C"
{
#define DEBUG_MSG(...)     \
	{ \
		do      \
		{	   \
			std::stringstream ss; \
			ss \
			<< "[DEBUG]"		\
			<< " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") "	\
			<< __VA_ARGS__		\
			<< ".\n";		\
			std::cout << ss.str() << std::flush;		\
			ofLog(OF_LOG_NOTICE, ss.str());  \
        } while( 0 );     \
    }

    #define ERROR_MSG(...)     \
    { 	   \
        do      \
        {	   \
			std::stringstream ss; \
			ss \
			<< "[ERROR]"		\
			<< " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") "	\
			<< __VA_ARGS__		\
			<< ".\n";		\
			std::cout << ss.str() << std::flush;		\
			ofLog(OF_LOG_ERROR, ss.str());  \
        } while( 0 );     \
    }

    #define EXCEPTION(...) \
    { \
        do      \
        {	   \
            std::stringstream ss; \
            ss << __VA_ARGS__; \
            ERROR_MSG(ss.str()); \
            throw std::runtime_error(ss.str()); \
        } while( 0 );     \
    }

    #define ERROR_QUIT(...)     \
    { 	   \
        do      \
        {	   \
			ERROR_MSG(__VA_ARGS__);		\
            std::exit(EXIT_FAILURE);		\
        } while( 0 ); \
    }
} //extern C

#endif
