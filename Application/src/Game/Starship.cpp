#include "Starship.h"

void Starship::handleEvents(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::W) {
			_shape.move({ 0,-10 });
		}
		if (event.key.code == sf::Keyboard::S) {
			_shape.move({ 0,10 });
		}
		if (event.key.code == sf::Keyboard::A) {
			_shape.move({ -10,0 });
		}
		if (event.key.code == sf::Keyboard::D) {
			_shape.move({ 10,0 });
		}
		
	}
}

void Starship::update()
{
}

void Starship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_isAlive) {
		target.draw(_shape);
	}
}
