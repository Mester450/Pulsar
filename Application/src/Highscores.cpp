#include "Highscores.h"
#include "Highscores/ReadWrite.h"

void Highscores::setup()
{	
	sf::FloatRect screen = { 0, 0 ,
		ngin::MainLevel::view_.getSize().x,
		ngin::MainLevel::view_.getSize().y };

	_highScores.setFont(*ngin::Resources::AcquireFont("oldgame.ttf"));
	_highScores.setCharacterSize(90);
	_highScores.setString("HIGHSCORES");
	_highScores.setFillColor({ 214, 112, 28 });
	ngin::centerTextInBounds(_highScores, screen, -300);

	_back.setTexture(*ngin::Resources::AcquireTexture("button.png"));
	_back.setFont(*ngin::Resources::AcquireFont("pixeled.ttf"));
	_back.setPosition({ 1366 / 2 - _back.getSize().x / 2, 675 });
	_back.setSelectThickness(0);
	_back.setFillColor({ 28, 105, 214 });
	_back.setTextColor({ 214, 112, 28 });

	// TODO: REMOVE
	for (int i = 0; i < (int)ReadWrite::getPlayers()->size(); i++) {
		sf::Text tmp;
		tmp.setFont(*ngin::Resources::AcquireFont("arial.ttf"));
		tmp.setCharacterSize(30);
		tmp.setFillColor({ 214, 112, 28 });
		tmp.setString(std::to_string(i + 1) + ": " +
			ReadWrite::getPlayers()->at(i).name + " " +
			std::to_string(ReadWrite::getPlayers()->at(i).score));

		ngin::centerTextInBounds(tmp, screen, -200 + i * (45));

		_scores.push_back(tmp);
	}
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

	for (int i = 0; i < _scores.size(); i++) {
		target.draw(_scores[i]);
	}
}
