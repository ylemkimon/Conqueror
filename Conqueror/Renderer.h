#pragma once
#include "Constants.h"
#include "Controller.h"

class Renderer {
	Controller& controller;

	int bar_target;
public:
	unsigned int texture_id;

	Renderer(Controller&);

	void draw();
	void drawBorder();
	void drawMap();
	void drawCharacters();
	void drawTrail();
	void drawUI();
};
