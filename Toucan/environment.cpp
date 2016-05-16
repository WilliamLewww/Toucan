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
			if (mapLine.at(x) == '1') { tempTile.position = Vector2(x * tempTile.width, y * tempTile.height); tempTile.tileID = 1; tileMap.push_back(tempTile); }
			if (mapLine.at(x) == '2') { tempPushTile.tile.position = Vector2(x * tempPushTile.tile.width, y * tempPushTile.tile.height); tempPushTile.tile.tileID = 2; tempPushTile.end = false; pushTileMap.push_back(tempPushTile); }
			if (mapLine.at(x) == '3') { tempPushTile.tile.position = Vector2(x * tempPushTile.tile.width, y * tempPushTile.tile.height); tempPushTile.tile.tileID = 2; tempPushTile.end = true; pushTileMap.push_back(tempPushTile); }
		}
	}
}

void DrawTile(Tile tile) {
	int color[3] = { 255, 0, 0 };
	DrawRect(tile.position, tile.width, tile.height, color);
}

void DrawMap(std::vector<Tile> tileMapParam) {
	for (auto &tile : tileMapParam) {
		DrawTile(tile);
	}
}