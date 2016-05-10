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
	int color[3] = { 255, 0, 0 };
	DrawRect(tile.position, tile.width, tile.height, color);
}

void DrawMap(std::vector<Tile> tileMapParam) {
	for (auto &tile : tileMap) {
		DrawTile(tile);
	}
}