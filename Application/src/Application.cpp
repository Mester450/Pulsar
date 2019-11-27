#include "Application.h"

Application::Application()
{
	windowVideoMode_ = { 1366,768 };
	windowName_ = "DodgeBall";
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
}

void Application::update()
{
	_currentLevel->update();
}

void Application::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	_currentLevel->draw(target, states);
}