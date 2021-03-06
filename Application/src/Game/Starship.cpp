#include "Starship.h"

void Starship::handleEvents(const sf::Event& event)
{

}

void Starship::update()
{
	if (isAlive())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			_shape.move({ 0, -_speed * ngin::Timer::getDeltaTime() });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			_shape.move({ 0, _speed * ngin::Timer::getDeltaTime() });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			_shape.move({ -_speed * ngin::Timer::getDeltaTime(), 0 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			_shape.move({ _speed * ngin::Timer::getDeltaTime(), 0 });
		}


		if (_shape.getPosition().x + _shape.getGlobalBounds().width > ngin::MainLevel::view_.getSize().x) {
			_shape.setPosition({ ngin::MainLevel::view_.getSize().x - _shape.getGlobalBounds().width, _shape.getPosition().y });
		}
		if (_shape.getPosition().y + _shape.getGlobalBounds().height > ngin::MainLevel::view_.getSize().y) {
			_shape.setPosition({ _shape.getPosition().x, ngin::MainLevel::view_.getSize().y - _shape.getGlobalBounds().height });
		}
		if (_shape.getPosition().x < 0) {
			_shape.setPosition({ 0, _shape.getPosition().y });
		}
		if (_shape.getPosition().y < 0) {
			_shape.setPosition({ _shape.getPosition().x, 0 });
		}
	}


}

void Starship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isAlive()) {
		target.draw(_shape);
		for (int i = 0; i < _lives; i++) {
			target.draw(_health[i]);
		}
	}
}
