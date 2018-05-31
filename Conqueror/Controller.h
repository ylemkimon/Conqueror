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

	bool hasData(int, int) const;
	int getData(int, int) const;
	void setData(int, int, int);

	Player* getPlayer();

	void updateFrame();
	void processSpecialKeys(int, int, int);
};