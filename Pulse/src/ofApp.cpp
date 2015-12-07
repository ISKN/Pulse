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
	if (!_replaceSlateByMouse)
	{
		setupSlate();
		//ofAddListener(_slate->newPoint, this, &ofApp::receivePoint);
	}

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
	DEBUG_MSG("Loading main settings");


	//Song
	try
	{
		_audioFileName = getSetting("song", "path");
	}
	catch (std::exception & e)
	{
		ERROR_QUIT("Cannot get song path: '" << e.what() << "' -> exiting");
	}

	//Tempo
	try
	{
		songTempo = std::stoul(getSetting("song", "tempo"));
	}
	catch (std::exception & e)
	{
		ERROR_QUIT("Cannot get song tempo: '" << e.what() << "' -> exiting");
	}

	//Volume
	try
	{
		_songVolume = std::stof(getSetting("song", "volume"));
	}
	catch (std::exception & e)
	{
		ERROR_MSG("Cannot get song volume: '" << e.what() << "' -> choosing 1.0 by default");
		_songVolume = 1.f;
	}

	//Background
	try
	{
		_backgroundEnabled = (bool)std::stoi(getSetting("display", "background"));
	}
	catch (std::exception & e)
	{
		ERROR_MSG("Cannot get background setting: '" << e.what() << "' -> enabling by default");
		_backgroundEnabled = true;
	}

	//Mouse
	try
	{
		_replaceSlateByMouse = (bool)std::stoi(getSetting("debug", "mouse"));
	}
	catch (std::exception & e)
	{
		ERROR_MSG("Cannot get mouse setting: '" << e.what() << "' -> disabling debug feature by default");
		_replaceSlateByMouse = false;
	}


	DEBUG_MSG("Main settings successfully loaded: " << _audioFileName << " | " << _songVolume << " | " << songTempo << " | " << _backgroundEnabled << " | " << _replaceSlateByMouse);
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
		if (!_replaceSlateByMouse)
		{
			//_slate->fetchPoints();
			std::deque<ofVec2f> points = _slate->fetchPoints();
			for (auto p = points.rbegin(); p != points.rend(); p++)
				receivePoint(*p);
		}

		_parts[_partNum]->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (_loaded)
	{
		if (_backgroundEnabled)
		{
			_background.begin();

			_background.setUniform1f("time", ofGetElapsedTimef()*0.3);
			_background.setUniform2f("resolution", WIDTH, HEIGHT);
			_background.setUniformTexture("white_noise_texture", _bgTexImage, 1);

			ofSetColor(1, 1, 1);
			ofRect(0, 0, WIDTH, HEIGHT);

			_background.end();
		}
		else
		{
			ofSetColor(0);
			ofRect(0, 0, WIDTH, HEIGHT);
		}

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
	if (_replaceSlateByMouse)
	{
		ofVec2f pt(x, y);
		receivePoint(pt);
	}
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