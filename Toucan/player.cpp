#include "player.h"

std::vector<Player> playerList;
LocalPlayer localPlayer;

bool CheckCollision(Tile tile);
void CheckCollisionSpecific(Tile tile);

void InitializePlayer() {
	std::string tempPosition, positionX, positionY;
	bool flip = false;

	SendMessage("initializeplayer");
	tempPosition = ReceiveInitialMessage().c_str();
	localPlayer.uniqueID = atoi(tempPosition.c_str());
	tempPosition = ReceiveInitialMessage().c_str();

	for (std::size_t x = 0; x < tempPosition.size(); x++) {
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

void UpdatePlayer(std::string message) {
	std::string tempMessage = message.substr(message.find('>') + 1);
	std::string tempPlaceHolder, tempPlaceHolderB;

	bool flip = false;

	float positionX, positionY;
	int userID;

	for (std::size_t x = 0; x < tempMessage.length(); x++) {
		if (tempMessage[x] == ':') goto jump;
		tempPlaceHolder += tempMessage[x];
	}

jump:
	userID = atoi(tempPlaceHolder.c_str());
	tempPlaceHolder.clear();
	tempMessage = tempMessage.substr(tempMessage.find(':') + 1);

	for (std::size_t x = 0; x < tempMessage.length(); x++) {
		if (flip == false && tempMessage.at(x) != ',') tempPlaceHolder += tempMessage[x];
		if (flip == true) tempPlaceHolderB += tempMessage[x];
		if (tempMessage.at(x) == ',') flip = true;
	}

	positionX = atof(tempPlaceHolder.c_str());
	positionY = atof(tempPlaceHolderB.c_str());

	for (std::size_t x = 0; x < playerList.size(); x++) {
		if (playerList[x].uniqueID == userID) { playerList[x].position = Vector2(positionX, positionY); ResetAdvert(); return; }
	}

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

	for (std::size_t x = 1; x < tempMessage.length(); x++) {
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

	for (std::size_t x = 1; x < tempMessage.length(); x++) {
		if (tempMessage[x] != ':') { tempCommand += tempMessage[x]; }
		else {
			positionList.push_back(tempCommand);
			tempCommand.clear();
		}
	}

	positionList.push_back(tempCommand);
	tempMessage.clear();
	tempCommand.clear();

	for (std::size_t x = 0; x < positionList.size(); x++) {
		Player tempPlayer;
		tempPlayer.valid = true;

		for (std::size_t y = 0; y < positionList[x].length(); y++) {
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

	for (std::size_t x = 0; x < idList.size(); x++) playerList[x].uniqueID = idList[x];
}

void UpdateLocalPlayer(int gameTime) {
	float deltaTimeS = (float)(gameTime) / 1000;

	Vector2 originalPosition = localPlayer.position;
	localPlayer.velocityX = 0;

	if (std::find(keyList.begin(), keyList.end(), SDLK_x) != keyList.end()) { localPlayer.speed = 125; }
	else { localPlayer.speed = 100; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end()) localPlayer.velocityX =  -localPlayer.speed * deltaTimeS;
	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end()) localPlayer.velocityX = localPlayer.speed * deltaTimeS;

	if (localPlayer.onGround == true) { 
		if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) != keyList.end()) { 
			localPlayer.velocityY = -3.5; localPlayer.onGround = false; 
		}
	}

	localPlayer.position.x += localPlayer.velocityX;
	localPlayer.position.y += localPlayer.velocityY;

	localPlayer.onGround = false;
	localPlayer.velocityY += 9.8 * deltaTimeS; 

	for (auto &tile : tileMap) {
		if (CheckCollision(tile) == true) CheckCollisionSpecific(tile);
	}

	if (originalPosition != localPlayer.position) {
		char positionChar[BUFLEN];
		std::string positionX(std::to_string(localPlayer.position.x)), positionY(std::to_string(localPlayer.position.y).c_str());
		strcpy(positionChar, ("position>" + positionX.substr(0, positionX.find('.') + 3) + "," + positionY.substr(0, positionY.find('.') + 3)).c_str());
		SendMessage(positionChar);
	}
}

//player.Left <= rectangle.Right &&
//player.Right >= rectangle.Left &&
//player.Top <= rectangle.Bottom &&
//player.Bottom >= rectangle.Top

bool CheckCollision(Tile tile) {
	if (localPlayer.left() <= tile.right() &&
		localPlayer.right() >= tile.left() &&
		localPlayer.top() <= tile.bottom() &&
		localPlayer.bottom() >= tile.top()) {
			return true;
	}

	return false;
}

void CheckCollisionSpecific(Tile tile) {
	if (localPlayer.bottom() > tile.top() && localPlayer.bottom() < tile.top() + 16 && localPlayer.left() < tile.right() - 3 && localPlayer.right() > tile.left() + 3) {
		localPlayer.onGround = true;
		localPlayer.velocityY = 0;
		localPlayer.position.y = tile.top() - tile.height;
	}

	if (localPlayer.top() < tile.bottom() && localPlayer.top() > tile.top() - 16 && localPlayer.left() < tile.right() - 3 && localPlayer.right() > tile.left() + 3) {
		if (localPlayer.velocityY < 0) localPlayer.velocityY = 0;
		localPlayer.position.y = tile.bottom();
	}

	if (localPlayer.left() < tile.right() && localPlayer.left() > tile.right() - 5 && localPlayer.bottom() > tile.top() + 5 && localPlayer.top() < tile.bottom() - 5) {
		if (localPlayer.velocityX < 0) localPlayer.velocityX = 0;
		localPlayer.position.x = tile.left() + tile.width;
	}

	if (localPlayer.right() > tile.left() && localPlayer.right() < tile.left() + 5 && localPlayer.bottom() > tile.top() + 5 && localPlayer.top() < tile.bottom() - 5) {
		if (localPlayer.velocityX > 0) localPlayer.velocityX = 0;
		localPlayer.position.x = tile.left() - localPlayer.width;
	}
}

void DrawPlayer(Player player) {
	DrawRect(player.position, player.width, player.height);
}

void DrawPlayer(LocalPlayer player) {
	GLint texture = LoadTexture("player.bmp");
	DrawRect(texture, player.position, player.width, player.height);
}