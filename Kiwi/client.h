#pragma once
#include <winsock2.h>

struct Client {
	sockaddr_in address;
	int addrLength = sizeof(address);
	int ID;
};