/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#ifndef MENU_H
#define MENU_H

#include "../Common/Level.h"
#include "../UI/Bttn.h"
#include "../UI/Language.h"
#include "../Graphics/Interpolation.h"

class Menu : public Scene
{
    public:

        Menu();

		virtual void reset() override;

        ofEvent<int>  eventChangePart;


    private:

        void setupMain() override;
        void updateMain() override;
        void drawMain() override;
		void processMain(ofVec2f const& point) override;

		Bttn _btnLang;
        Bttn _btnLevel1;
		Bttn _btnLevel2;

		void btnLangClicked();
        void btnLevel1Clicked();
		void btnLevel2Clicked();

		ofShader _titleFX;
		ofSoundPlayer _bandWarmingUp;

		//ofShader _background;
};

#endif // MENU_H
