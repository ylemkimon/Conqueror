#pragma once
#include <vector>

#include "Constants.h"

#ifdef USE_SOUND
#include <irrKlang.h>
#endif

class Character;
class Player;

class Controller {
	int data[MAP_SIZE][MAP_SIZE];
	Player* player;

#ifdef USE_SOUND
	irrklang::ISoundEngine *SoundEngine;
#endif
public:
	int step;
	int filled;
	std::vector<Character*> characters;

	Controller();
	~Controller();

	bool hasData(int, int) const;
	int getData(int, int) const;
	void setData(int, int, int);
	void playSound(const char* filename);

	Player* getPlayer();

	void updateFrame();
	void processSpecialKeys(int, int, int);
};
