#pragma once
#include <winsock2.h>
#include "vector2.h"

struct Player {
	Vector2 position;
	int width = 15, height = 15;
};

struct Client {
	sockaddr_in address;
	int addrLength = sizeof(address);
	int uniqueID;

	Player player;
};