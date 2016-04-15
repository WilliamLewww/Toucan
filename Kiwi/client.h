#pragma once
#include <winsock2.h>
#include "vector2.h"

struct Player {
	Vector2 position;
	int width = 20, height = 20;
};

struct Client {
	sockaddr_in address;
	int addrLength = sizeof(address);
	int status;

	Player player;
};