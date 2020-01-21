#include "Endscreen.h"

void Endscreen::setup()
{	
	sf::FloatRect screen = { 0, 0 , 1366, 768 };

	_gameOver.setFont(*ngin::Resources::AcquireFont("arial.ttf"));
	_gameOver.setCharacterSize(75);
	_gameOver.setString("Game Over");
	_gameOver.setFillColor(sf::Color::White);

	ngin::centerTextInBounds(_gameOver, screen, -200);
}

void Endscreen::handleEvents(const sf::Event& event)
{
}

void Endscreen::update()
{
}

void Endscreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_gameOver);
}
