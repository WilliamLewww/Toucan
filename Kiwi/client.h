#pragma once
#include <winsock2.h>
#include "vector2.h"

struct Player {
	Vector2 position;
};

struct Client {
	sockaddr_in address;
	int addrLength = sizeof(address);
	int status;

	Player player;
};