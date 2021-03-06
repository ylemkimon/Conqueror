#pragma once
#include <vector>
#include <queue>
#include <unordered_set>

#include "Segment.h"
#include "Character.h"

class Player : public Character {
	int base[2];
	std::vector<Segment> trail;

	void updateTrail();
	void traverseTrail();
	void _traverseTrail(int, int, int &, std::queue<int> *, std::unordered_set<int> &);
	bool fill(int, int, int);
public:
	Player(Controller&, float);

	int life;

	virtual void move(int);
	virtual void draw();
	void die();
	void changeHeading(Direction);
};
