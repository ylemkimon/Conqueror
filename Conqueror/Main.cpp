#include <ctime>

#include "Constants.h"
#include "Controller.h"
#include "Renderer.h"

#include <GL/glut.h>

Controller controller;
Renderer renderer(controller);

void processSpecialKeys(int key, int x, int y) {
	controller.processSpecialKeys(key, x, y);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer.draw();
	glutSwapBuffers();
}

void idle() {
	static clock_t previousTime = clock();
	clock_t currentTime = clock();
	if (currentTime - previousTime < 16) {
		return;
	}
	previousTime = currentTime;

	controller.updateFrame();

	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(150, 100);
	glutInitWindowSize(900, 900);
	glutCreateWindow("Conqueror");

	// glutGameModeString("1024x600:32@60");
	// glutEnterGameMode();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, MAP_SIZE + 1, -1, MAP_SIZE + UI_SIZE);

	glClearColor(CLEAR_COLOR, 1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();
}
