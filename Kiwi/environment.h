#pragma once
#include "client.h"
#include "main.h"

const int MAPSIZEX = 40, MAPSIZEY = 30;
static int tileMap[MAPSIZEY][MAPSIZEX] = {0};

void GenerateMap();
void SendMap(Client client);