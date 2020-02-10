#include "Application.h"

Application::Application()
{
	view_ = sf::View{ {0, 0, 1920, 1080} };
	windowVideoMode_ = { 1366,768 };
	windowName_ = "DodgeBall";

 #ifndef _DEBUG
	ShowWindow(GetConsoleWindow(), SW_HIDE);
 #endif
}

void Application::setup()
{
	ngin::Resources::setLocation("assets/");

	_currentLevel = new Menu;
	_currentLevel->setup();

	window_.setFramerateLimit(144);

	_readWrite.readHighScore();
}

void Application::handleEvents()
{
	_currentLevel->handleEvents(event_);

	if (_currentLevel->getResponse() == Menu::RESPONSES_START)
	{
		_currentLevel = new Game;
		_currentLevel->setup();
	}
	else if (_currentLevel->getResponse() == Menu::RESPONSES_HIGHSCORES) 
	{
		_currentLevel = new Highscores;
		_currentLevel->setup();
	}
	else if (_currentLevel->getResponse() == Menu::RESPONSES_SETTINGS)
	{
		_currentLevel = new Settings;
		_currentLevel->setup();
	}
	else if (_currentLevel->getResponse() == Menu::RESPONSES_EXIT || event_.type == sf::Event::Closed)
	{
		_readWrite.writeHighScore();
		window_.close();
	}

	
	if (_currentLevel->getResponse() == Game::RESPONSES_ENDSCREEN)
	{
		_currentLevel = new Endscreen;
		_currentLevel->setup();
	}

	if (_currentLevel->getResponse() == Highscores::RESPONSES_BACK)
	{
		_currentLevel = new Menu;
		_currentLevel->setup();
	}

	if (_currentLevel->getResponse() == Endscreen::RESPONSES_BACK)
	{
		_readWrite.addHighScore();
		_currentLevel = new Menu;
		_currentLevel->setup();
	}

	if (_currentLevel->getResponse() == Settings::RESPONSES_MENU)
	{
		_currentLevel = new Menu;
		_currentLevel->setup();
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