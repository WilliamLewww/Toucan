#include "player.h"

std::vector<Player> playerList;
Player localPlayer;

void InitializePlayer() {
	std::string tempPosition, positionX, positionY;
	bool flip = false;

	SendMessage("initializeplayer");
	tempPosition = ReceiveInitialMessage().c_str();
	localPlayer.uniqueID = atoi(tempPosition.c_str());
	tempPosition = ReceiveInitialMessage().c_str();

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
}

void AddPlayer(std::string message) {
	std::string tempMessage = message.substr(message.find('>') + 1);
	std::string tempPlaceHolder, tempPlaceHolderB;

	bool flip = false;

	float positionX, positionY;
	int userID;

	for (int x = 0; x < tempMessage.length(); x++) {
		if (tempMessage[x] == ':') goto jump;
		tempPlaceHolder += tempMessage[x];
	}

jump:
	userID = atoi(tempPlaceHolder.c_str());
	for (int x = 0; x < playerList.size(); x++) { 
		if (playerList[x].uniqueID == userID) { ResetAdvert(); return; }
	}

	tempPlaceHolder.clear();
	tempMessage = tempMessage.substr(tempMessage.find(':') + 1);

	for (int x = 0; x < tempMessage.length(); x++) {
		if (flip == false && tempMessage.at(x) != ',') tempPlaceHolder += tempMessage[x];
		if (flip == true) tempPlaceHolderB += tempMessage[x];
		if (tempMessage.at(x) == ',') flip = true;
	}

	positionX = atoi(tempPlaceHolder.c_str());
	positionY = atoi(tempPlaceHolderB.c_str());

	Player tempPlayer;
	tempPlayer.position = Vector2(positionX, positionY);
	tempPlayer.valid = true;
	tempPlayer.uniqueID = userID;

	playerList.push_back(tempPlayer);

	ResetAdvert();
}

void RequestPlayer() {
	std::string tempMessage, tempCommand;
	std::vector<std::string> positionList;
	std::vector<int> idList;

	bool flip = false;

	SendMessage("requestplayer");
	tempMessage = ReceiveInitialMessage().c_str();

	if (tempMessage.length() == 0) return;

	for (int x = 1; x < tempMessage.length(); x++) {
		if (tempMessage[x] == ':') goto jump;
		if (tempMessage[x] != '.') tempCommand += tempMessage[x];
		else {
			idList.push_back(atoi(tempCommand.c_str()));
			tempCommand.clear();
		}
	}

jump:
	idList.push_back(atoi(tempCommand.c_str()));
	tempCommand.clear();
	tempMessage = tempMessage.substr(tempMessage.find(':'));

	for (int x = 1; x < tempMessage.length(); x++) {
		if (tempMessage[x] != ':') { tempCommand += tempMessage[x]; }
		else {
			positionList.push_back(tempCommand);
			tempCommand.clear();
		}
	}

	positionList.push_back(tempCommand);
	tempMessage.clear();
	tempCommand.clear();

	for (int x = 0; x < positionList.size(); x++) {
		Player tempPlayer;
		tempPlayer.valid = true;

		for (int y = 0; y < positionList[x].length(); y++) {
			if (positionList[x].at(y) == ',') { flip = true; y += 1; }
			if (flip == false) tempMessage += positionList[x].at(y);
			if (flip == true) tempCommand += positionList[x].at(y);
		}

		tempPlayer.position.x = atoi(tempMessage.c_str());
		tempPlayer.position.y = atoi(tempCommand.c_str());
		playerList.push_back(tempPlayer);

		tempMessage.clear();
		tempCommand.clear();
		flip = false;
	}

	for (int x = 0; x < idList.size(); x++) playerList[x].uniqueID = idList[x];
}

void UpdateLocalPlayer(int gameTime) {
	Vector2 originalPosition = localPlayer.position;

	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end()) localPlayer.position.x -= 1;
	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end()) localPlayer.position.x += 1;

	if (originalPosition != localPlayer.position) {
		char positionChar[BUFLEN];
		strcpy(positionChar, ("position>" + std::to_string((int)localPlayer.position.x) + "," + std::to_string((int)localPlayer.position.y)).c_str());
		SendMessage(positionChar);
	}
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