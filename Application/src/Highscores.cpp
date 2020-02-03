#include "Highscores.h"

void Highscores::setup()
{	
	sf::FloatRect screen{ 0,0, 1366, 768 };

	_highScores.setFont(*ngin::Resources::AcquireFont("oldgame.ttf"));
	_highScores.setCharacterSize(90);
	_highScores.setString("HIGHSCORES");
	_highScores.setFillColor({ 214, 112, 28 });
	ngin::centerTextInBounds(_highScores, screen, -300);

	_back.setTexture(*ngin::Resources::AcquireTexture("button.png"));
	_back.setFont(*ngin::Resources::AcquireFont("pixeled.ttf"));
	_back.setPosition({ 1366 / 2 - _back.getSize().x / 2, 650 });
	_back.setSelectThickness(0);
	_back.setFillColor({ 28, 105, 214 });
	_back.setTextColor({ 214, 112, 28 });
}

void Highscores::handleEvents(const sf::Event& event)
{
	_back.handleEvents(event, ngin::Cursor::getPosition());

	if (_back.isSelected()) {

		_back.setScale({ 1.02f,1.02f });

		if (_canStartMove) {
			const float x = _back.getPosition().x - (_back.getSize().x * _back.getScale().x - _back.getSize().x) / 2;
			const float y = _back.getPosition().y - (_back.getSize().y * _back.getScale().y - _back.getSize().y) / 2;
			_back.setPosition({ x,y });

			_canStartMove = false;
		}
	}
	else {

		if (!_canStartMove) {
			const float x = _back.getPosition().x + (_back.getSize().x * _back.getScale().x - _back.getSize().x) / 2;
			const float y = _back.getPosition().y + (_back.getSize().y * _back.getScale().y - _back.getSize().y) / 2;
			_back.setPosition({ x,y });

			_canStartMove = true;
		}

		_back.setScale({ 1,1 });

	}

	if (_back.isPressed()) {
		response_ = RESPONSES_BACK;
	}
	else {
		response_ = RESPONSES_NONE;
	}
}

void Highscores::update()
{
}

void Highscores::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(_highScores);
	target.draw(_back);
}
