#pragma once
#include <SDL_opengl.h>
#include <vector>
#include "main.h"
#include "net.h"
#include "vector2.h"

struct Tile {
	Vector2 position;
	int width = 20, height = 20;

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }
};

const int MAPSIZEX = 40, MAPSIZEY = 30;
extern std::vector<Tile> tileMap;

void GetMap();
void DrawMap(std::vector<Tile> tileMapParam);