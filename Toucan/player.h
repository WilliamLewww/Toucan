#pragma once
#include <SDL_opengl.h>
#include <string>
#include <stdlib.h>
#include "vector2.h"
#include "net.h"
#include "main.h"
#include "input.h"

struct Player {
	Vector2 position;
	int width = 20, height = 20;
	bool valid = false;

	int uniqueID;
};

extern Player localPlayer;
extern std::vector<Player> playerList;

void InitializePlayer();
void RequestPlayer();
void UpdateLocalPlayer(int gameTime);
void DrawPlayer(Player player);
void UpdatePlayer(std::string message);