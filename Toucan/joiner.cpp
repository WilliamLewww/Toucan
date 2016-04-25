#include "joiner.h"

Joiner::Joiner() {

}

void Joiner::LoadContent() {

}

void Joiner::Update(int gameTime) {
	UpdateLocalPlayer(gameTime);
}

void Joiner::Render() {
	if (localPlayer.valid) DrawPlayer(localPlayer);
	for (auto &player : playerList) { DrawPlayer(player); }
	DrawMap();
}