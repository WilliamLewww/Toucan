#include "environment.h"

std::vector<Tile> tileMap;
std::vector<PushTile> pushTileMap;

void GetMap() {
	Tile tempTile;
	PushTile tempPushTile;
	std::string mapLine;

	SendMessage("getmap");
	for (int y = 0; y < MAPSIZEY; y++) {
		mapLine = ReceiveInitialMessage().c_str();

		for (int x = 0; x < MAPSIZEX; x++) {
			if (mapLine.at(x) == '1') { tempTile.position = Vector2(x * tempTile.width, y * tempTile.height); tileMap.push_back(tempTile); tempTile.tileID = 1; }
			if (mapLine.at(x) == '2') { tempPushTile.tile.position = Vector2(x * tempPushTile.tile.width, y * tempPushTile.tile.height); pushTileMap.push_back(tempPushTile); tempPushTile.tile.tileID = 2; }
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