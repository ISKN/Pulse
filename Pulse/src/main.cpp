/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "general.h"
#include "ofApp.h"

//Global variables (defined here, are declared as extern in other files)
#include "UI/FontManager.h"
FontManager fontManager;
Tempo songTempo = 160;

int main()
{
	//Log
	ofSetLogLevel(OF_LOG_NOTICE);
	std::stringstream logName;
	logName << "logs/log_" << std::setfill('0') << std::setw(2) << ofGetDay() << "-" << ofGetMonth() << "-" << ofGetYear() << "--" << ofGetHours() << "-" << ofGetMinutes() << "-" << ofGetSeconds() << ".txt";
	ofLogToFile(ofToDataPath(logName.str()), false);

	//Opengl context
	ofGLWindowSettings settings;

	//Width
	int width = 1600;
	try
	{
		width = std::stoi(getSetting("display", "width"));
	}
	catch (std::exception & e)
	{
		ERROR_MSG("Cannot get width setting: '" << e.what() << "' -> choosing 1600 by default");
	}
	settings.width = width;

	//Height
	int height = 900;
	try
	{
		height = std::stoi(getSetting("display", "height"));
	}
	catch (std::exception & e)
	{
		ERROR_MSG("Cannot get height setting: '" << e.what() << "' -> choosing 900 by default");
	}
	settings.height = height;

	//Display mode
	bool fullscreen = true;
	try
	{
		fullscreen = (bool)std::stoi(getSetting("display", "fullscreen"));
	}
	catch (std::exception & e)
	{
		ERROR_MSG("Cannot get display mode setting: '" << e.what() << "' -> choosing fullscreen by default");
	}
	if (fullscreen)
		settings.windowMode = OF_FULLSCREEN;
	else
		settings.windowMode = OF_WINDOW;

	DEBUG_MSG("Creating openGL context with the following parameters: " << width << " | " << height << " | " << fullscreen);

	//Etc
	settings.setGLVersion(2, 0); //Shaders were written for GLSL 1.10
	ofCreateWindow(settings);

	//Start!
	ofRunApp(new ofApp());
}
