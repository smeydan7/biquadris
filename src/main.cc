#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "core/Game.h"
using namespace std;

int highscore = 0; // should be passed as a parameter in score constructor

int main(int argc, char *argv[])
{
	bool withGraphics = true;
	int startLevel = 2;
	unsigned int seed = 1000;
	string inputFiles[2] = {"biquadris_sequence1.txt", "biquadris_sequence2.txt"};

	for (int i = 1; i < argc; ++i)
	{
		string arg = argv[i];
		if (arg == "-text")
		{
      withGraphics = false;
		}
		if (arg == "-seed")
		{
			++i;
			string temp = argv[i];
			istringstream iss{temp};
			iss >> seed;
			srand(seed);
		}
		if (arg == "-scriptfile1")
		{
			++i;
			string name = argv[i];
      inputFiles[0] = name;
		}
		if (arg == "-scriptfile2")
		{
			++i;
			string name = argv[i];
      inputFiles[1] = name;
		}
		if (arg == "-startlevel")
		{
			++i;
			string temp = argv[i];
			istringstream iss{temp};
			iss >> startLevel;
		}
	}

	// Call function to run game with parameters: withGraphics, inputFile1, inputFile2, startLevel
    Game g(withGraphics, startLevel, seed, inputFiles);
    g.play();
}
