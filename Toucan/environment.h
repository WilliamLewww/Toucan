#pragma once
#include <SDL_opengl.h>
#include "main.h"
#include "net.h"
#include "vector2.h"

const int MAPSIZEX = 40, MAPSIZEY = 30;
static int tileMap[MAPSIZEY][MAPSIZEX] = { 0 };

void GetMap();
void DrawMap();