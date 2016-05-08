#pragma once
#include <SDL_opengl.h>
#include <string>
#include "vector2.h"
#include "net.h"
#include "main.h"
#include "input.h"

struct LocalPlayer {
	Vector2 position;
	int width = 20, height = 20;
	bool valid = false;

	int uniqueID;

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }

	bool onGround = false;
	double velocityX, velocityY;

	double speed = 100;
};

struct Player {
	Vector2 position;
	int width = 20, height = 20;
	bool valid = false;

	int uniqueID;

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }
};

extern LocalPlayer localPlayer;

extern std::vector<Player> playerList;

void InitializePlayer();
void RequestPlayer();
void UpdateLocalPlayer(int gameTime);
void DrawPlayer(Player player);
void DrawPlayer(LocalPlayer player);
void UpdatePlayer(std::string message);