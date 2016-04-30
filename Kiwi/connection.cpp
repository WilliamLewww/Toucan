#include "connection.h"

void ReceiveTimeout(Client client, bool* messageReceived, char buf[]);
bool PingClient(Client client);

std::vector<Client> clientList;

int GetConnectionCount() {
	return curConnections;
}

bool AddConnection(Client client) {
	CheckConnection();

	if (curConnections < maxConnections) {
		clientList.push_back(client);
		curConnections += 1;
		return true;
	}
	
	return false;
}

void CheckConnection() {

}

bool PingClient(Client client) {
	SendMessage("ping", client);
	bool messageReceived = false;
	static char message[BUFLEN];

	memset(message, '\0', BUFLEN);
	std::thread tryReceive(ReceiveTimeout, client, &messageReceived, message);

	std::clock_t initial;
	double duration = 0;
	initial = std::clock();

	while (duration < 5 && messageReceived == false) {
		duration = (std::clock() - initial) / (double)CLOCKS_PER_SEC;
	}

	tryReceive.detach();

	if (std::string(message).compare("pong")) return true;
	else return false;
}

void ReceiveTimeout(Client client, bool* messageReceived, char buf[]) {
	ReceiveMessage(buf, client);
	*messageReceived = true;
}

int ProcessCommand(char buf[]) {
	std::string command(buf);
	if (command.compare("connect") == 0) return 0;
	if (command.compare("getmap") == 0) return 1;
	if (command.compare("initializeplayer") == 0) return 2;
	if (command.compare("requestplayer") == 0) return 3;
	if (command.compare(0, 9,"position>") == 0) return 4;

	return -1;
}

void UpdatePosition(Client &client, char buf[]) {
	std::string message(buf), tempMessage, tempMessageB;
	message = message.substr(message.find('>') + 1);

	bool flip = false;

	for (int x = 0; x < message.length(); x++) {
		if (flip == false && message.at(x) != ',') tempMessage += message[x];
		if (flip == true) tempMessageB += message[x];
		if (message.at(x) == ',') flip = true;
	}

	client.player.position = Vector2(atoi(tempMessage.c_str()), atoi(tempMessageB.c_str()));
	tempMessage.clear();

	tempMessage += "advert<position>" + std::to_string((int)client.uniqueID) + ":";
	tempMessage += std::to_string(client.player.position.x) + "," + std::to_string(client.player.position.y);

	char tempMessageChar[BUFLEN];
	strcpy(tempMessageChar, tempMessage.c_str());
	SendMessage(tempMessageChar, client, clientList);
}

void InitializePlayer(Client &client) {
	std::string tempPosition;

	srand(time(NULL));
	client.player.position = Vector2(rand() % (SCREENWIDTH - (client.player.width - 1)), rand() % (SCREENHEIGHT - (client.player.height - 1)));

	tempPosition = std::to_string(client.player.position.x);
	tempPosition += ":";
	tempPosition += std::to_string(client.player.position.y);

	char tempPositionChar[BUFLEN];
	strcpy(tempPositionChar, std::to_string((int)client.uniqueID).c_str());
	SendMessage(tempPositionChar, client);

	memset(tempPositionChar, '\0', BUFLEN);

	strcpy(tempPositionChar, tempPosition.c_str());
	SendMessage(tempPositionChar, client);
}

void RequestPlayer(Client client) {
	std::string clientMessage;

	for (auto &otherClient : clientList) {
		if (otherClient.uniqueID != client.uniqueID) {
			clientMessage += ".";
			clientMessage += std::to_string((int)otherClient.uniqueID);
		}
	}

	for (auto &otherClient : clientList) {
		if (otherClient.uniqueID != client.uniqueID) {
			clientMessage += ":";
			clientMessage += std::to_string(otherClient.player.position.x) + "," + std::to_string(otherClient.player.position.y);
		}
	}

	char tempClientMessage[BUFLEN];
	strcpy(tempClientMessage, clientMessage.c_str());

	SendMessage(tempClientMessage, client);
}