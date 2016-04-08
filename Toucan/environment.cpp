#include "environment.h"

void GetMap() {
	std::string mapLine;

	SendMessage("getmap");
	for (int y = 0; y < MAPSIZEY; y++) {
		mapLine = ReceiveMessage().c_str();

		for (int x = 0; x < MAPSIZEX; x++) {
			tileMap[y][x] = mapLine.at(x) - 48;
			std::cout << tileMap[y][x];
		}

		std::cout << std::endl;
	}
}