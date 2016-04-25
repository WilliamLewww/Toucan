#include "environment.h"

void GetMap() {
	std::string mapLine;

	SendMessage("getmap");
	for (int y = 0; y < MAPSIZEY; y++) {
		mapLine = ReceiveInitialMessage().c_str();

		for (int x = 0; x < MAPSIZEX; x++) {
			tileMap[y][x] = mapLine.at(x) - 48;
		}
	}
}

void DrawTile(int xPos, int yPos) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glBegin(GL_QUADS);
	glColor3f(255, 0, 0);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= tileWidth;
		vectors[x].y *= tileHeight;
		vectors[x] += Vector2(xPos, yPos);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}
void DrawMap() {
	for (int y = 0; y < MAPSIZEY; y++) {
		for (int x = 0; x < MAPSIZEX; x++) {
			if (tileMap[y][x] == 1) DrawTile(x * tileWidth, y * tileHeight);
		}
	}
}