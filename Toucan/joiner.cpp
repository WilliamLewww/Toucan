#include "joiner.h"

Joiner::Joiner() {

}

void Joiner::LoadContent() {

}

void Joiner::Update(int gameTime) {

}

void Joiner::Render() {
	if (localPlayer.valid) DrawPlayer(localPlayer);
	std::cout << localPlayer.position.x << std::endl;
	DrawMap();
}