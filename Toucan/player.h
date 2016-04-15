#pragma once
#include <SDL_opengl.h>
#include <stdlib.h>
#include "vector2.h"
#include "net.h"
#include "main.h"

struct Player {
	Vector2 position;
	int width = 20, height = 20;
	bool valid = false;
};

extern Player localPlayer;

void InitializePlayer();
void DrawPlayer(Player player);