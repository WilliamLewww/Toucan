#include "player.h"

std::vector<Player> playerList;
LocalPlayer localPlayer;

bool CheckCollision(Tile tile);
void HandleCollision(Tile tile);
bool CheckCollisionBottom(Tile tile);
void FloatingMovement(float deltaTimeS);

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

std::vector<Tile> groundTileList;
bool jumpPress = false;
bool floatingMovement = false;
void UpdateLocalPlayer(int gameTime) {
	float deltaTimeS = (float)(gameTime) / 1000;
	Vector2 originalPosition = localPlayer.position;

	for (auto &tile : pushTileMap) {
		if (CheckCollision(tile.tile) == true) {
			//0=up 1=down 2=right 3=left
			if (tile.GetDirection(pushTileMap) == 0) localPlayer.velocityY = tile.force * deltaTimeS;
			if (tile.GetDirection(pushTileMap) == 1) localPlayer.velocityY = -tile.force * deltaTimeS;
			if (tile.GetDirection(pushTileMap) == 2) localPlayer.velocityX = tile.force * deltaTimeS;
			if (tile.GetDirection(pushTileMap) == 3) localPlayer.velocityX = -tile.force * deltaTimeS;
		}
	}

	if (floatingMovement) FloatingMovement(deltaTimeS);

	localPlayer.position.x += localPlayer.velocityX;
	localPlayer.position.y += localPlayer.velocityY;
	localPlayer.velocityX = 0;

	if (std::find(keyList.begin(), keyList.end(), SDLK_f) != keyList.end()) floatingMovement = !floatingMovement;

	if (std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) != keyList.end()) { localPlayer.speed = 150; }
	else { localPlayer.speed = 100; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end()) localPlayer.velocityX =  -localPlayer.speed * deltaTimeS;
	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end()) localPlayer.velocityX = localPlayer.speed * deltaTimeS;

	if (localPlayer.onGround == true) { 
		if (jumpPress == false) {
			if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) != keyList.end()) {
				localPlayer.velocityY = -3.5; localPlayer.onGround = false; jumpPress = true;
			}
		}
	}
	else {
		localPlayer.velocityY += 9.8 * deltaTimeS;
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) == keyList.end()) {
		if (localPlayer.velocityY < 0 && localPlayer.onGround == false) localPlayer.velocityY += 9.8 * deltaTimeS;
		if (localPlayer.onGround == true) jumpPress = false;
	}

	for (auto &tile : tileMap) {
		if (tile.tileID == 1) {
			if (CheckCollision(tile) == true) HandleCollision(tile);
		}
	}

	std::vector<Tile> tempGroundTileList;
	for (auto &tile : groundTileList) {
		if (CheckCollision(tile) == false) {
			tempGroundTileList.push_back(tile);
		}
	}

	for (auto &tile : tempGroundTileList) {
		groundTileList.erase(std::remove(groundTileList.begin(), groundTileList.end(), tile), groundTileList.end());
	}
	tempGroundTileList.clear();

	if (groundTileList.size() == 0) localPlayer.onGround = false;

	if (originalPosition != localPlayer.position) {
		char positionChar[BUFLEN];
		std::string positionX(std::to_string(localPlayer.position.x)), positionY(std::to_string(localPlayer.position.y).c_str());
		strcpy(positionChar, ("position>" + positionX.substr(0, positionX.find('.') + 3) + "," + positionY.substr(0, positionY.find('.') + 3)).c_str());
		SendMessageWithTimer(positionChar);
	}
}

void FloatingMovement(float deltaTimeS) {
	localPlayer.velocityX = 0;
	localPlayer.velocityY = 0;
	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end()) localPlayer.velocityX = -localPlayer.speed * deltaTimeS;
	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end()) localPlayer.velocityX = localPlayer.speed * deltaTimeS;
	if (std::find(keyList.begin(), keyList.end(), SDLK_UP) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_DOWN) == keyList.end()) localPlayer.velocityY = -localPlayer.speed * deltaTimeS;
	if (std::find(keyList.begin(), keyList.end(), SDLK_DOWN) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_UP) == keyList.end()) localPlayer.velocityY = localPlayer.speed * deltaTimeS;
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

//player.top <= tile.bottom && player.top >= tile.bottom - 5 && player.left <= tile.right - 5 && player.right >= tile.left + 5:
bool CheckCollisionBottom(Tile tile) {
	if (localPlayer.top() <= tile.bottom() && localPlayer.top() >= tile.bottom() - 5 && localPlayer.left() <= tile.right() - 3 && localPlayer.right() >= tile.left() + 3) return true;
	return false;
}

void HandleCollision(Tile tile) {
	double overlapX, overlapY;
	if (localPlayer.midpoint().x > tile.midpoint().x) overlapX = tile.right() - localPlayer.left();
	else overlapX = -(localPlayer.right() - tile.left());
	if (localPlayer.midpoint().y > tile.midpoint().y) overlapY = tile.bottom() - localPlayer.top();
	else overlapY = -(localPlayer.bottom() - tile.top());

	if (overlapX != 0 && overlapY != 0) {
		if (abs(overlapY) < abs(overlapX)) {
			if (overlapY < 0) {
				if (localPlayer.velocityY > 0) {
					localPlayer.onGround = true;
					localPlayer.position.y += overlapY; localPlayer.velocityY = 0;
					if (std::find(groundTileList.begin(), groundTileList.end(), tile) == groundTileList.end()) groundTileList.push_back(tile);
				}
			}
			else {
				if (localPlayer.velocityY < 0) {
					if (CheckCollisionBottom(tile)) { localPlayer.position.y += overlapY; localPlayer.velocityY = 0; }
				}
			}
		}
		else {
			localPlayer.position.x += overlapX; localPlayer.velocityX = 0;
		}
	}
}

void DrawPlayer(Player player) {
	DrawRect(player.position, player.width, player.height);
}

void DrawPlayer(LocalPlayer player) {
	GLint texture = LoadTexture("../Content/player.bmp");
	DrawRect(texture, player.position, player.width, player.height);
}