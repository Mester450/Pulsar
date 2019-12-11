#include "Starship.h"

void Starship::handleEvents(const sf::Event& event)
{

}

void Starship::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		_shape.move({ 0, - _speed * ngin::Timer::getDeltaTime() });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		_shape.move({ 0, _speed * ngin::Timer::getDeltaTime() });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_shape.move({ - _speed * ngin::Timer::getDeltaTime(), 0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_shape.move({ _speed * ngin::Timer::getDeltaTime(), 0 });
	}


	if (_shape.getPosition().x + _shape.getGlobalBounds().width > ngin::MainLevel::getView().getSize().x) {
		_shape.setPosition({ ngin::MainLevel::getView().getSize().x - _shape.getGlobalBounds().width, _shape.getPosition().y});
	}
	if (_shape.getPosition().y + _shape.getGlobalBounds().height > ngin::MainLevel::getView().getSize().y) {
		_shape.setPosition({ _shape.getPosition().x, ngin::MainLevel::getView().getSize().y - _shape.getGlobalBounds().height });
	}
	if (_shape.getPosition().x < 0) {
		_shape.setPosition({ 0, _shape.getPosition().y });
	}
	if (_shape.getPosition().y < 0) {
		_shape.setPosition({ _shape.getPosition().x, 0 });
	}


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
		_isAlive = false;
	}

}

void Starship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_isAlive) {
		target.draw(_shape);
	}
}
