#pragma once
#include <SDL_opengl.h>
#include <vector>
#include "main.h"
#include "net.h"
#include "vector2.h"

struct Tile {
	Vector2 position;
	int width = 20, height = 20;
	int tileID = -1;

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }
};

struct PushTile {
	Tile tile;

	inline int GetDirection() { };
};

const int MAPSIZEX = 40, MAPSIZEY = 30;
extern std::vector<Tile> tileMap;
extern std::vector<PushTile> pushTileMap;

void GetMap();
void DrawMap(std::vector<Tile> tileMapParam);

void GetAdjacentPushTile(PushTile &pushTile);