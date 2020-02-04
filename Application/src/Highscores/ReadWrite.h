#pragma once
#include <string>
#include <vector>
#include <fstream>

class ReadWrite {
public:
	bool readHighScore();
	void addHighScore();
	void writeHighScore();

	struct Player {
		std::string name = "";
		float score = 0.0F;
	};

	// static pointer to player vector
	static const std::vector<Player>* const getPlayers() {
		return &_players;
	}

private:
	std::string _fileLocation = "./Highscores.txt";
	static std::vector<Player> _players;

	int _scoreLimit = 10;
};