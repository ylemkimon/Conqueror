#pragma once
#include <vector>
#include <queue>

#include "Controller.h"
#include "Segment.h"
#include "Character.h"

class Player : public Character {
	int base[2];
	std::vector<Segment> trail;

	void updateTrail();
	void traverseTrail();
	void _traverseTrail(int, int, std::queue<int> *);
	void fill(int, int);
public:
	Player(Controller&, float);

	int* getBase();
	std::vector<Segment>& getTrail();

	virtual void move(int);
	virtual void die();
};