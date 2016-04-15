#include "player.h"

Player localPlayer;

void InitializePlayer() {
	std::string tempPosition, positionX, positionY;
	bool flip = false;

	SendMessage("initializeplayer");
	tempPosition = ReceiveMessage().c_str();

	for (int x = 0; x < tempPosition.size(); x++) {
		if (tempPosition.at(x) != ':') {
			if (flip == false) positionX += tempPosition.at(x);
			if (flip == true) positionY += tempPosition.at(x);
		}
		else {
			flip = true;
		}
	}

	localPlayer.position.x = atoi(positionX.c_str());
	localPlayer.position.y = atoi(positionY.c_str());
	localPlayer.valid = true;

	std::cout << localPlayer.position.x << ":" << localPlayer.position.y << std::endl;
}

void DrawPlayer(Player player) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glBegin(GL_QUADS);
	glColor3f(0, 255, 0);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= player.width;
		vectors[x].y *= player.height;
		vectors[x] += Vector2(player.position.x, player.position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}