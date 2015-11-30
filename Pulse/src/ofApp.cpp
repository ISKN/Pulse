/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#include "ofApp.h"

extern FontManager fontManager; //this can't be in the header or it will be included in main.cpp
extern Tempo songTempo; //Same here

//--------------------------------------------------------------
void ofApp::setup2()
{
	//Log
	ofSetLogLevel(OF_LOG_NOTICE);
	std::stringstream logName;
	logName << "logs/log_" << std::setfill('0') << std::setw(2) << ofGetDay() << "-" << ofGetMonth() << "-" << ofGetYear() << "--" << ofGetHours() << "-" << ofGetMinutes() << "-" << ofGetSeconds() << ".txt";
	ofLogToFile(ofToDataPath(logName.str()), false);

	//Start
	DEBUG_MSG("Starting setup...");

#ifdef USE_SPLASH_SCREEN
	splashScreen.init(ofToDataPath("iskn.jpg"));
	splashScreen.begin();
#endif

	//Opengl params
	ofEnableSmoothing();
	ofEnableAntiAliasing();
	ofSetWindowTitle("Pulse");
	ofSetFrameRate(60);
	ofSetCircleResolution(200);

	//Tempo and song params
	getMainParams();

	//Background
	_background.load(ofToDataPath("shaders/voronoi.vert"), ofToDataPath("shaders/voronoi.frag"));
	ofDisableArbTex();
	_bgTexImage.loadImage(ofToDataPath("shaders/whitenoise.jpg"));

	//Language
	setEN();

	//Fonts
	fontManager.loadBasicFonts();

	//Parts
	Scene::_ribbon.setup();

    _parts.push_back(&_menu);
	_parts.push_back(&_level1);
	_parts.push_back(&_level2);

	_level1.setMainParams(_audioFileName, _songVolume);
	_level2.setMainParams(_audioFileName, _songVolume);

	for (Scene * s : _parts)
	{
		s->setup();
		s->disable();
	}

	//Slates
	#ifndef REPLACE_SLATE_BY_MOUSE
	setupSlate();
	//ofAddListener(_slate->newPoint, this, &ofApp::receivePoint);
	#endif

	//Various listeners
    ofAddListener(_menu.eventChangePart, this, &ofApp::changePart);

	ofAddListener(_level1.exitLevel, this, &ofApp::exitCurrentPart);
	ofAddListener(_level2.exitLevel, this, &ofApp::exitCurrentPart);

	ofAddListener(_level1.goToNextLevel, this, &ofApp::goToNextPart);

	_partNum = PART_NUMBER_MENU;
	_parts[_partNum]->reset();
	_parts[_partNum]->enable();

	_loaded = true;
#ifdef USE_SPLASH_SCREEN
	splashScreen.end();
#endif
	ofHideCursor();
}

void ofApp::getMainParams()
{
	DEBUG_MSG("Loading main parameters");

	//Get lines from settings file
	std::ifstream inputStream(ofToDataPath("settings.ini").c_str(), std::ifstream::in);

	if (!inputStream.is_open())
		ERROR_QUIT("Cannot find parameters file '" << ofToDataPath("settings.ini") << "'");

	std::vector<std::string> lines;

	while (inputStream.good())
	{
		std::string line;
		std::getline(inputStream, line);
		lines.push_back(line);
	}

	//Get audio file
	if (lines[0][0] != '#')
		ERROR_QUIT("The first line should be a comment");

	_audioFileName = lines[1];

	if (_audioFileName.empty())
		ERROR_QUIT("The audio file name is empty");

	//Get volume
	if (lines[3][0] != '#')
		ERROR_QUIT("The fourth line should be a comment");

	_songVolume = std::stof(lines[4]);

	//Get tempo
	if (lines[6][0] != '#')
		ERROR_QUIT("The seventh line should be a comment");

	songTempo = std::stoul(lines[7]);

	//End
	inputStream.close();
	DEBUG_MSG("Main parameters successfully loaded: " << _audioFileName << " | " << _songVolume << " | " << songTempo);
}

void ofApp::setupSlate()
{
	_slateConnected = false;

	try
	{
		DEBUG_MSG("Connecting slate");
		//Create object
		_slate = std::make_unique<Slate>();
		//Connect
		_slate->connect();
		DEBUG_MSG("Slate connected");
	}
	catch (std::exception & e)
	{
		ERROR_QUIT("Couldn't connect slate: " << e.what());
	}

}

//--------------------------------------------------------------
void ofApp::exit()
{
	DEBUG_MSG("Exiting on " << std::setfill('0') << std::setw(2) << ofGetDay() << "-" << ofGetMonth() << "-" << ofGetYear() << " at " << ofGetHours() << ":" << ofGetMinutes() << ":" << ofGetSeconds());
    
#ifndef REPLACE_SLATE_BY_MOUSE
	if (_slateConnected)
	{
		_slate->disconnect();
	}
#endif
	
	std::exit(EXIT_SUCCESS);
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (ofGetFrameNum() == 1)
	{
		this->setup2();
	}

	if (_loaded)
	{
		#ifndef REPLACE_SLATE_BY_MOUSE
			//_slate->fetchPoints();
			std::deque<ofVec2f> points = _slate->fetchPoints();
			for (auto p = points.rbegin(); p != points.rend(); p++)
				receivePoint(*p);
		#endif

		_parts[_partNum]->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (_loaded)
	{
		_background.begin();

			_background.setUniform1f("time", ofGetElapsedTimef()*0.3);
			_background.setUniform2f("resolution", WIDTH, HEIGHT);
			_background.setUniformTexture("white_noise_texture", _bgTexImage, 1);

			ofSetColor(1, 1, 1);
			ofRect(0, 0, WIDTH, HEIGHT);

		_background.end();

		_parts[_partNum]->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	#ifdef REPLACE_SLATE_BY_MOUSE
		ofVec2f pt(x, y);
		receivePoint(pt);
	#endif
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::receivePoint(ofVec2f & point)
{
	if (_loaded)
	{
		//DEBUG_MSG("Received new point " << point.x << " " << point.y);

		//Update ribbon
		Scene::_ribbon.addPoint(point);

		//Update current part (scene)
		_parts[_partNum]->process(point);
	}
}


//--------------------------------------------------------------
void ofApp::changePart(int & part)
{
    //Disable old one
    _parts[_partNum]->disable();

    //Reset and enable new one
    DEBUG_MSG("Old part is " << _partNum << " and new one is " << part);
    _parts[part]->reset();
    _parts[part]->enable();

	//Reset ribbon color
	Scene::_ribbon.resetColor();

    //Update
    _partNum = part;
}

void ofApp::exitCurrentPart()
{
    int fuckingReference = PART_NUMBER_MENU;
    changePart(fuckingReference);
}

void ofApp::goToNextPart()
{
	int newPart = _partNum + 1 < NUMBER_OF_PARTS ? _partNum + 1 : 0;
	changePart(newPart);
}