#include "Game.h"

void Game::setup()
{
}

void Game::handleEvents(const sf::Event& event)
{
	_starShip.handleEvents(event);
}

void Game::update()
{
	_starShip.update();
	_enemy.update();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	_enemy.draw(target, states);
	_starShip.draw(target, states);
}
