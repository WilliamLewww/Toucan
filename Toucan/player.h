#pragma once
#include <stdlib.h>
#include "vector2.h"
#include "net.h"

void InitializePlayer();

struct Player {
	Vector2 position;
	bool valid = false;
};

static Player localPlayer;