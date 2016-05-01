#include "environment.h"

std::vector<Tile> tileMap;

void GetMap() {
	Tile tempTile;
	std::string mapLine;

	SendMessage("getmap");
	for (int y = 0; y < MAPSIZEY; y++) {
		mapLine = ReceiveInitialMessage().c_str();

		for (int x = 0; x < MAPSIZEX; x++) {
			if (mapLine.at(x) == '1') { tempTile.position = Vector2(x * tempTile.width, y * tempTile.height); tileMap.push_back(tempTile); }
		}
	}
}

void DrawTile(Tile tile) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glBegin(GL_QUADS);
	glColor3f(255, 0, 0);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= tile.width;
		vectors[x].y *= tile.height;
		vectors[x] += Vector2(tile.position.x, tile.position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}

void DrawMap(std::vector<Tile> tileMapParam) {
	for (auto &tile : tileMap) {
		DrawTile(tile);
	}
}