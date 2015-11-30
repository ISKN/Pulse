/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#pragma once

#include "../general.h"

#include "../UI/FontManager.h"
extern FontManager fontManager;

#include "Ribbon.h"
#include "../UI/Bttn.h"

//This interface is useful to create a new part in the application.

class Scene
{
	public:

		Scene();
	
		virtual void setup();
		virtual void update();
		virtual void draw();

		void process(ofVec2f const & point);

		void enable();
		void disable();
		bool isEnabled() const;

		virtual void reset() {} //Go back to the state right after setup.

		static Ribbon _ribbon; //The ribbon is shared between all the scenes!


	protected:

		virtual void setupMain() = 0;
		virtual void updateMain() = 0;
		virtual void drawMain() = 0;
		virtual void processMain(ofVec2f const& point) = 0;

		void registerButton(Bttn * button);
		void unregisterButton(Bttn * button);
		bool buttonIsRegistered(Bttn * button) const;
		void clearButtons();

		void notifyMainLog(std::string const & text);

		std::list<Bttn*> _buttons;

		bool _enabled;

};
