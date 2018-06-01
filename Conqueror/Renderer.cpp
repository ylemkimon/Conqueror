#include "Renderer.h"
#include "Segment.h"
#include "Player.h"

#include <GL/glut.h>

void drawCircle(float cx, float cy) {
	float t;
	float x = 0.7f;
	float y = 0;

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(cx, cy);
		for (int i = 0; i <= 100; i++) {
			glVertex2f(x + cx, y + cy);

			t = x;
			x = COS_PI_50 * x - SIN_PI_50 * y;
			y = SIN_PI_50 * t + COS_PI_50 * y;
		}
	glEnd();
}

void drawCorner(int x, int y, Direction prev, Direction curr) {
	if (prev == LEFT || curr == LEFT) {
		x++;
	}
	if (prev == DOWN || curr == DOWN) {
		y++;
	}

	glBegin(GL_TRIANGLES);
		for (int i = 0; i < 2; i++) {
			int _x = x;
			int _y = y;
			glVertex2i(_x, _y);
			shift(_x, _y, curr);
			glVertex2i(_x, _y);
			shift(_x, _y, prev);
			glVertex2i(_x, _y);
		}
	glEnd();
}

void drawHeart(int x) {
	glRectf(x + .5f, MAP_SIZE + 5, x + 1.5f, MAP_SIZE + 4.5f);
	glRectf(x + 2, MAP_SIZE + 5, x + 3, MAP_SIZE + 4.5f);
	glRectf(x, MAP_SIZE + 4.5f, x + 3.5f, MAP_SIZE + 3);
	glRectf(x + .5f, MAP_SIZE + 3, x + 3, MAP_SIZE + 2.5f);
	glRectf(x + 1, MAP_SIZE + 2.5f, x + 2.5f, MAP_SIZE + 2);
	glRectf(x + 1.5f, MAP_SIZE + 2, x + 2, MAP_SIZE + 1.5f);
}

Renderer::Renderer(Controller &controller) : controller(controller), bar_target()
{
}

void Renderer::draw()
{
	drawBorder();
	drawMap();
	drawTrail();
	drawCharacters();
	drawUI();

#ifdef USE_TEXTURE // TODO : extract to function
	if (controller.step < 0) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		float quarter = (float)MAP_SIZE / 4;
		float texture_offset = controller.step == LOSE ? .5f : 0;
		glBegin(GL_POLYGON);
			glTexCoord2f(0, texture_offset + .5f); glVertex2f(quarter, 2 * quarter);
			glTexCoord2f(0, texture_offset); glVertex2f(quarter, 3 * quarter);
			glTexCoord2f(1, texture_offset); glVertex2f(3 * quarter, 3 * quarter);
			glTexCoord2f(1, texture_offset + .5f); glVertex2f(3 * quarter, 2 * quarter);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
#endif
}

void Renderer::drawBorder()
{
	glColor3fv(BORDER_COLOR);
	glRectf(-1, -1, 0, MAP_SIZE + 1);
	glRectf(MAP_SIZE, -1, MAP_SIZE + 1, MAP_SIZE + 1);
	glRectf(-1, -1, MAP_SIZE + 1, 0);
	glRectf(-1, MAP_SIZE, MAP_SIZE + 1, MAP_SIZE + 1); // TODO : fill top area?
}

void Renderer::drawMap()
{
	float hue = controller.getPlayer()->color;
	Color shadowColor(hue, .8f, .2f, 1);

	for (int r = MAP_SIZE - 1; r >= 0; r--) {
		for (int c = 0; c < MAP_SIZE; c++) {
			int state = controller.getData(r, c);
			if (state <= 0) {
				continue;
			}
			float y = r + BOUNCE[state];

			int bottomState = controller.hasData(r - 1, c) ? controller.getData(r - 1, c) : TERRITORY;
			if ((state == TERRITORY) != (bottomState == TERRITORY) || bottomState <= 0) {
				glColor4fv(shadowColor.rgba);
				glRectf(c, y - SHADOW_SIZE, c + 1, y);
			}

			Color bounceColor(hue, .8f, .6f - BOUNCE[state] / 6, 1.f);
			glColor4fv(bounceColor.rgba);
			glRectf(c, y, c + 1, y + 1);

			if (state < TERRITORY) {
				controller.setData(r, c, state + 1);
			}
		}
	}
}

void Renderer::drawCharacters() // TODO : move to Character
{
	for (const auto& character : controller.characters) {
		float hue = character->color;

		Color shadowColor(hue, .8f, .2f, 1);
		glColor4fv(shadowColor.rgba);
		drawCircle((float)character->pos[0] / STEP_SIZE + 0.65f, (float)character->pos[1] / STEP_SIZE + 0.35f);

		Color playerColor(hue, .8f, .45f, 1);
		glColor4fv(playerColor.rgba);
		drawCircle((float)character->pos[0] / STEP_SIZE + 0.5f, (float)character->pos[1] / STEP_SIZE + 0.5f);
	}
}

void Renderer::drawTrail()
{
	Player& p = *controller.getPlayer();
	std::vector<Segment>& trail = p.getTrail();

	if (!trail.empty()) {
		Color tailColor(p.color, .8f, .8f, .5f);
		glColor4fv(tailColor.rgba);

		Direction prev = NONE;
		int* base = p.getBase();
		int x = base[1];
		int y = base[0];
		for (const auto& move : trail) {
			if (prev != NONE) {
				drawCorner(x, y, prev, move.direction);
			}

			if (move.direction == UP || move.direction == RIGHT) {
				shift(x, y, move.direction);
			}
			if (move.length > 1) {
				int x1 = x;
				int y1 = y;
				shift(x, y, move.direction, move.length - 1);
				glRectf(x1, y1, x == x1 ? x + 1 : x, y == y1 ? y + 1 : y);
			}
			if (move.direction == DOWN || move.direction == LEFT) {
				shift(x, y, move.direction);
			}
			prev = move.direction;
		}
		if (prev == p.heading[0]) {
			glRectf(x, y, x + 1, y + 1);
		}
		else {
			drawCorner(x, y, prev, p.heading[0]);
		}
	}
}

void Renderer::drawUI()
{
	Player& p = *controller.getPlayer();

	glColor3f(1, 0, 0);
	for (int i = 0; i < INITIAL_LIFE; i++) {
		if (i == p.life) {
			glColor3f(.2f, .2f, .2f);
		}
		drawHeart(HEART_WIDTH * i);
	}
	int start = HEART_WIDTH * INITIAL_LIFE + 1;

	char buffer[10];
	int len = sprintf(buffer, "KILLS: %d", ZOMBIE_COUNT + 1 - controller.characters.size());
	int end = MAP_SIZE - len - 1;

	glColor3f(0, 0, 0);
	glRasterPos2f(end, MAP_SIZE + 2.5f);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
	}

	int diff = controller.filled - bar_target;
	if (diff > 0) {
		bar_target += diff < 80 ? (diff > 4 ? diff / 4 : 1) : 20;
	}
	float ratio = (float)bar_target / (MAP_SIZE * MAP_SIZE);
	float bar_length = ratio * (end - start);

	Color barColor(p.color, .8f, .4f, 1);
	glColor4fv(barColor.rgba);
	glRectf(start, MAP_SIZE + 1.5f, start + bar_length, MAP_SIZE + 5); // TODO : bar height

	len = sprintf(buffer, "%.2f %%", ratio * 100);
	if (bar_length < len + 1.3f) {
		glRasterPos2f(start + bar_length + .8f, MAP_SIZE + 2.5f);
	}
	else {
		glColor3f(1, 1, 1);
		glRasterPos2f(start + bar_length - len - 1.2f, MAP_SIZE + 2.5f);
	}
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
	}
}
