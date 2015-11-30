/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/

#pragma once

#include "../general.h"
#include "../Common/Level.h"
#include "../Common/Circle.h"
#include "../Common/Drum.h"

#include "../UI/FontManager.h"
extern FontManager fontManager;

class Level2 : public Level
{
	public:

		Level2();

	protected:

		virtual void setupMain() override;
		virtual void updateMain() override;
		virtual void drawMain() override;

		virtual void setupStartMain() override;
		virtual void drawIntro() override;
		virtual void drawOutro() override;
};

