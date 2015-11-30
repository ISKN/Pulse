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
	//Opengl context
	ofGLWindowSettings settings;
	settings.width = WINDOW_WIDTH;
	settings.height = WINDOW_HEIGHT;

#ifdef FULLSCREEN_MODE
	settings.windowMode = OF_FULLSCREEN; //~OF_WINDOW
#endif

	settings.setGLVersion(2, 0); //Shaders were written for GLSL 1.10
	ofCreateWindow(settings);

	//Start!
	ofRunApp(new ofApp());
}
