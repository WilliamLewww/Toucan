#include <winsock2.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "main.h"
#include "environment.h"

#pragma comment(lib, "ws2_32.lib")

#define BUFLEN 512
#define PORT 27861

void SendMessage(char message[], Client client);

SOCKET s;
WSADATA wsa;

struct sockaddr_in server;
int slen, recv_len;
char buf[BUFLEN];

bool isRunning = 1;
int main() {
	WSAStartup(MAKEWORD(2, 2), &wsa);
	s = socket(AF_INET, SOCK_DGRAM, 0);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	bind(s, (struct sockaddr *)&server, sizeof(server));

	GenerateMap();

	while (isRunning) {
		memset(buf, '\0', BUFLEN);
		recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&tempClient.address, &tempClient.addrLength);

		switch (ProcessCommand(buf)) {
			case 0 :
				tempClient.status = 1;
				if (AddConnection(tempClient, clientList)) SendMessage("connect", tempClient);

				std::cout << GetConnectionCount() << "/" << maxConnections << std::endl;
				break;
			case 1:
				SendMap(tempClient);
				break;
			case 2:
				std::string tempPosition;
				tempClient.player.position = Vector2(rand() % (SCREENWIDTH - 19), rand() % (SCREENHEIGHT - 19));
				tempPosition = std::to_string((int)tempClient.player.position.x);
				tempPosition += ":";
				tempPosition += std::to_string((int)tempClient.player.position.y);

				char tempPositionChar[255];
				strcpy(tempPositionChar, tempPosition.c_str());

				SendMessage(tempPositionChar, tempClient);
				break;
		}
	}

	closesocket(s);
	WSACleanup();

	return 0;
}

void SendMessage(char message[], Client client) {
	sendto(s, message, strlen(message), 0, (struct sockaddr *) &client.address, client.addrLength);
}

void ReceiveMessage(char message[], Client client) {
	recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &client.address, &client.addrLength);
}