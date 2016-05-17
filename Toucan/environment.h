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
	double force = 130;
	int initialDirection = -1;
	bool end = false;

	//0=up 1=down 2=right 3=left
	inline int GetDirection(std::vector<PushTile> tileMap) { 
		for (auto &otherTile : tileMap) {
			//othertile = left
			if (otherTile.tile.position.x == (tile.position.x - tile.width) && (otherTile.tile.position.y == tile.position.y)) {
				if (end == true) return 2;
				otherTile.initialDirection = 2;
				if (initialDirection == -1) return 3;
				if (initialDirection != 2) return 3;
			}
			//othertile = right
			if (otherTile.tile.position.x == (tile.position.x + tile.width) && (otherTile.tile.position.y == tile.position.y)) {
				if (end == true) return 3;
				otherTile.initialDirection = 3;
				if (initialDirection == -1) return 2;
				if (initialDirection != 3) return 2;
			}
			//othertile = down
			if (otherTile.tile.position.y == (tile.position.y - tile.height) && (otherTile.tile.position.x == tile.position.x)) {
				if (end == true) return 0;
				otherTile.initialDirection = 0;
				if (initialDirection == -1) return 1;
				if (initialDirection != 0) return 1;
			}
			//othertile = up
			if (otherTile.tile.position.y == (tile.position.y + tile.height) && (otherTile.tile.position.x == tile.position.x)) {
				if (end == true) return 1;
				otherTile.initialDirection = 1;
				if (initialDirection == -1) return 0;
				if (initialDirection != 1) return 0;
			}
		}

		return -1;
	};
};

const int MAPSIZEX = 40, MAPSIZEY = 30;
extern std::vector<Tile> tileMap;
extern std::vector<PushTile> pushTileMap;

void GetMap();
void DrawMap(std::vector<Tile> tileMapParam);