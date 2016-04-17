#include "connection.h"

void ReceiveTimeout(Client client, bool* messageReceived, char buf[]);
bool PingClient(Client client);

int GetConnectionCount() {
	return curConnections;
}

bool AddConnection(Client client, std::vector<Client> clientList) {
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

	return -1;
}

void InitializePlayer(Client client) {
	std::string tempPosition;
	client.player.position = Vector2(rand() % (SCREENWIDTH - (client.player.width - 1)), rand() % (SCREENHEIGHT - (client.player.height - 1)));
	tempPosition = std::to_string((int)client.player.position.x);
	tempPosition += ":";
	tempPosition += std::to_string((int)client.player.position.y);

	char tempPositionChar[255];
	strcpy(tempPositionChar, tempPosition.c_str());

	SendMessage(tempPositionChar, client);
}