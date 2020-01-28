#include "Endscreen.h"

void Endscreen::setup()
{	
	sf::FloatRect screen = { 0, 0 , 1366, 768 };

	_gameOver.setFont(*ngin::Resources::AcquireFont("arial.ttf"));
	_gameOver.setCharacterSize(90);
	_gameOver.setString("Game Over");
	_gameOver.setFillColor(sf::Color::White);

	_score.setFont(*ngin::Resources::AcquireFont("arial.ttf"));
	_score.setCharacterSize(45);
	_score.setString("Score: " + Game::getScoreString());
	_score.setFillColor(sf::Color::White);


	ngin::centerTextInBounds(_gameOver, screen, -200);
	ngin::centerTextInBounds(_score, screen, -100);

	button.setTexture(*ngin::Resources::AcquireTexture("button.png"));
	button.setFont(*ngin::Resources::AcquireFont("arial.ttf"));
	button.setPosition({ 1366 / 2 - button.getSize().x / 2, 400 });
	button.setSelectThickness(0);
	button.setFillColor({ 28, 105, 214 });
	button.setTextColor({ 214, 112, 28 });

}

void Endscreen::handleEvents(const sf::Event& event)
{
	button.handleEvents(event, ngin::Cursor::getPosition());

	if (button.isSelected()) {

		button.setScale({ 1.02f,1.02f });

		if (_canStartMove) {
			const float x = button.getPosition().x - (button.getSize().x * button.getScale().x - button.getSize().x) / 2;
			const float y = button.getPosition().y - (button.getSize().y * button.getScale().y - button.getSize().y) / 2;
			button.setPosition({ x,y });

			_canStartMove = false;
		}
	}
	else {

		if (!_canStartMove) {
			const float x = button.getPosition().x + (button.getSize().x * button.getScale().x - button.getSize().x) / 2;
			const float y = button.getPosition().y + (button.getSize().y * button.getScale().y - button.getSize().y) / 2;
			button.setPosition({ x,y });

			_canStartMove = true;
		}

		button.setScale({ 1,1 });

	}

	if (button.isPressed())
	{
		response_ = RESPONSES_BACK;
	}
	else {
		response_ = RESPONSES_NONE;
	}

}

void Endscreen::update()
{
}

void Endscreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_gameOver);
	target.draw(_score);
	target.draw(button);
}
