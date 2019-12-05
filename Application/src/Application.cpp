#include "Application.h"

Application::Application()
{
	windowVideoMode_ = { 1366,768 };
	windowName_ = "DodgeBall";
	window_.setView(_view); // FUCKING IMPORTANT
}

void Application::setup()
{
	ngin::Resources::setLocation("assets/");

	_currentLevel = new Menu;
	_currentLevel->setup();
}

void Application::handleEvents()
{
	_currentLevel->handleEvents(event_);

	if (_currentLevel->getResponse() == Menu::RESPONSES_SETTINGS)
	{
		_currentLevel = new Settings;
		_currentLevel->setup();
	}
	else if (_currentLevel->getResponse() == Menu::RESPONSES_START)
	{
		_currentLevel = new Game;
		_currentLevel->setup();
	}
	else if (_currentLevel->getResponse() == Menu::RESPONSES_EXIT)
	{
		window_.close();
	}
}

void Application::update()
{
	_currentLevel->update();
}

void Application::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	_currentLevel->draw(target, states);

	sf::RectangleShape shape;
}