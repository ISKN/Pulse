/* Copyright © 2015 Pierre Schefler <pierre.schefler@oxbern.com>
* This work is free. You can redistribute it and / or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar.See the LICENSE file for more details.
*/


#include "Scene.h"

Ribbon Scene::_ribbon = Ribbon(); //Define the ribbon

Scene::Scene()
{
	disable();
	clearButtons();
}

void Scene::setup()
{
	setupMain();
}

void Scene::update()
{
	if (_enabled)
	{
		updateMain();
	}
}

void Scene::draw()
{
	if (_enabled)
	{
		drawMain();
		_ribbon.draw();
	}
}

void Scene::process(ofVec2f const& point)
{
	if (_enabled)
	{
		for (Bttn * b : _buttons)
			b->newCursorPosition(point);

		processMain(point);
	}
}

void Scene::disable()
{
	_enabled = false;
	for (Bttn * b : _buttons)
		b->disable();
}

void Scene::enable()
{
	_enabled = true;
	for (Bttn * b : _buttons)
		b->enable();
}

bool Scene::isEnabled() const
{
	return _enabled;
}

void Scene::registerButton(Bttn * button)
{
	if (!buttonIsRegistered(button))
		_buttons.push_back(button);
}

void Scene::unregisterButton(Bttn * button)
{
	if (buttonIsRegistered(button))
		_buttons.erase(std::find(_buttons.begin(), _buttons.end(), button));
}

bool Scene::buttonIsRegistered(Bttn * button) const
{
	return std::find(_buttons.begin(), _buttons.end(), button) != _buttons.end();
}

void Scene::clearButtons()
{
	_buttons.clear();
}
