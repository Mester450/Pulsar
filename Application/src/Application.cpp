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
	Music::playTheme(Music::Theme::Menu);
	ngin::Resources::setLocation("assets/");

	ngin::MainLevel::setWindowIcon("icon.png");
	_background.setTexture(NG_TEXTURE("background.png"));
	ngin::Cursor::setTexture(NG_TEXTURE("cursor.png"));
	ngin::Cursor::setScale(cursorScale_);

	ngin::Audio::subscribeMusic(&Music::nowPlaying_);
	ngin::Cursor::setBuffer(NG_SOUNDBUFFER("Click.wav"));

	ngin::Audio::subscribeSound(ngin::Cursor::getSoundPtr());

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
		_background.setColor(sf::Color{0,0,0});
		ngin::Cursor::setScale({0,0});
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

	if (_currentLevel->getResponse() == Game::RESPONSES_ENDSCREEN)
	{
		_background.setColor(sf::Color{ 255,255,255 });
		ngin::Cursor::setScale(cursorScale_);
		_currentLevel = new Endscreen;
		_currentLevel->setup();
	}
}

void Application::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_background);
	_currentLevel->draw(target, states);

	sf::RectangleShape shape;
}