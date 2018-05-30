#pragma once
#include <vector>

class Character;
class Player;

class Controller {
	int step;
	int **data;
	Player* player;

public:
	int filled;
	std::vector<Character*> characters;

	Controller();
	~Controller();

	int get(int, int) const;
	void set(int, int, int);
	bool isOutOfBounds(int, int) const;
	Player* getPlayer();

	void updateFrame();
	void processSpecialKeys(int, int, int);
};