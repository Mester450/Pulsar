#pragma once

#include "SFML/Graphics.hpp"
#include "Ngin.h"

class Starship : public sf::Drawable {
public:
	Starship() {
		_shape.setTexture(&*ngin::Resources::AcquireTexture("Starship.png"));
		_shape.setSize({ 512, 512 });
		_shape.setScale({ 0.2f, 0.2f });
		_shape.setFillColor(sf::Color::Blue);
		_shape.setPosition({ 1366 / 2 - _shape.getGlobalBounds().width / 2, 768 / 2 - _shape.getGlobalBounds().height / 2 });

		for (int i = 0; i < _lives; i++) {
			_health.push_back(sf::RectangleShape{ {20, 20} });
			_health[i].setPosition({( 1366 - _health[i].getGlobalBounds().width - 10) - i * ( _health[i].getGlobalBounds().width + 20) , 10 });

		}
	}

	// gets called only if there is an ongoing event
	void handleEvents(const sf::Event& event);
	// gets called every frame but is not constant
	void update();
	// gets called every frame but should only draw on window
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::FloatRect getGlobalBounds() {
		return _shape.getGlobalBounds();
	}

	void setLives(const int lives) {
		_lives = lives;
	}

	int getLives() {
		return _lives;
	}

private:
	sf::RectangleShape _shape;
	float _speed = 500.0F;

	std::vector<sf::RectangleShape> _health;
	int _lives = 3;
};