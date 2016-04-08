#pragma once
#include "net.h"

const int MAPSIZEX = 40, MAPSIZEY = 30;
static int tileMap[MAPSIZEY][MAPSIZEX] = { 0 };

void GetMap();