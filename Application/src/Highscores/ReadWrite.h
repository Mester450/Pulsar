#pragma once
#include <string>
#include <vector>
#include <fstream>

class ReadWrite {
public:
	bool readHighScore();
	bool writeHighScore();

private:
	std::string _fileLocation = "./Highscores.txt";
	std::vector <float> _names;
	std::vector <float> _scores;

};