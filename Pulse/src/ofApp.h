/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#pragma once

#include "general.h"

#include "UI/Language.h"
#include "UI/FontManager.h"
#include "Slate/Slate.h"

#include "Menu/Menu.h"
#include "Level1/Level1.h"
#include "Level2/Level2.h"

#include "ofxSplashScreen.h"

class ofApp : public ofBaseApp
{
    public:

        //Main stuff
		ofApp() { _loaded = false; };

        void setup2();									//The setup function is replaced by setup2 with the splash screen addon.
        void update();									//Called at each frame before draw.
        void draw();									//Called at each frame to render the image.

        void exit();


    private:

		//Main params
		void getMainParams();							//Parses the settings file and extracts the parameters.
		std::string _audioFileName;						//Path to the song file.
		float _songVolume;								//Volume of the song (useful to better hear the drums for instance).

		//Misc
		ofxSplashScreen splashScreen;					//Splash screen addon (doesn't always work for whatever reason).
		bool _loaded;									//The app only considers itself loaded when the setup is finished so that we're sure no scene will be called before the app is fully loaded.
		ofShader _background;							//The background is made with a shader implementing the voronoi algorithm.
		ofImage _bgTexImage;							//The background shader requires white noise which is given with a texture for performance issues (instead of being computed inside the shader with a heavy function).

        //UI events
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void windowResized(int w, int h);

        //Slates
		std::unique_ptr<Slate> _slate;					//The Slate.
		bool _slateConnected;							//Pretty clear name.
		void setupSlate();								//Called during the app setup to connect the slate.
		void receivePoint(ofVec2f & point);				//This function is called to process a new point coming from the Slate (to send it to the multiple scenes, for instance).

        //Parts
        int _partNum;									//Current part index (part 0 is the menu, part 1 is level1, etc).
        void changePart(int & part);					//Disable current part and enable new one.
        void exitCurrentPart();							//Go to menu.
		void goToNextPart();							//GO to next part (goes back to the first one if we're at the last one).
		
        Menu _menu;										
		Level1 _level1;
		Level2 _level2;
        std::vector<Scene*> _parts;						//Heterogeneous collection to manipulate the parts.
		
};

