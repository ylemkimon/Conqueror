#pragma once
#include "Constants.h"
#include "Controller.h"

class Renderer {
	Controller& controller;
public:
	Renderer(Controller&);

	void draw();
	void drawBorder();
	void drawMap();
	void drawCharacters();
	void drawTrail();
	void drawUI();
};