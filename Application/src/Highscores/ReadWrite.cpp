#include "ReadWrite.h"
#include "../Endscreen.h"// getPlayerName()
#include "../Game.h" // getScoreFloat()

std::vector<ReadWrite::Player> ReadWrite::_players;

bool ReadWrite::readHighScore()
{
	_players.clear();

	std::ifstream in(_fileLocation);
	if (in.fail()) {
		return false;
	}

	std::string name;
	float score;
	while (in >> name) {
		in >> score;
		_players.push_back(Player{name, score});
	}

	return true;
}

void ReadWrite::addHighScore()
{
	// Format player name for invalid character(space)
	std::string playerName = Endscreen::getPlayerName();
	std::replace(playerName.begin(), playerName.end(), ' ', '_'); // replace ' ' with '_'

	Player thisPlayer{ playerName, Game::getScoreFloat() };

	if (_players.size() == 0) {
		_players.push_back(thisPlayer);
	}
	else {
		bool isSaved = false; // check if it was added
		for (int i = 0; i < _players.size(); i++) {
			if (thisPlayer.score > _players[i].score) {
				// add before the position i
				std::vector<Player>::iterator it = _players.begin() + i;
				_players.insert(it, thisPlayer);
				isSaved = true;
				break;
			}
		}

		if (!isSaved) { // save if less players than limit	
			_players.push_back(thisPlayer);
		}

		if ( static_cast<int>(_players.size() - _scoreLimit) > 0) { // delete if more players than limit
			_players.erase(_players.begin() + _scoreLimit, _players.end());
		}
	}
}

void ReadWrite::writeHighScore()
{
	std::ofstream out(_fileLocation);

	for (int i = 0; i < _players.size(); i++) {
		out << _players[i].name << " " << _players[i].score << std::endl;
	}
}
