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
void SendMessage(char message[], std::vector<Client> clientList);

SOCKET s;
WSADATA wsa;

struct sockaddr_in server;
int slen, recv_len;
char buf[BUFLEN];

int incrementID = 0;
int incrementIndex = -1;

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
		incrementIndex = -1;

		memset(buf, '\0', BUFLEN);
		recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&tempClient.address, &tempClient.addrLength);

		for (int x = 0; x < clientList.size(); x++) {
			if (tempClient.address.sin_port == clientList[x].address.sin_port) incrementIndex = x;
		}

		switch (ProcessCommand(buf)) {
			case 0 :
				tempClient.uniqueID = incrementID;
				incrementID += 1;

				if (AddConnection(tempClient)) SendMessage("connect", tempClient);

				std::cout << GetConnectionCount() << "/" << maxConnections << std::endl;
				break;
			case 1:
				SendMap(clientList[incrementIndex]);
				break;
			case 2:
				InitializePlayer(clientList[incrementIndex]);
				break;
			case 3:
				RequestPlayer(clientList[incrementIndex]);
				break;
		}

		std::cout << buf << std::endl;
	}

	closesocket(s);
	WSACleanup();

	return 0;
}

void SendMessage(char message[], Client client) {
	sendto(s, message, strlen(message), 0, (struct sockaddr *) &client.address, client.addrLength);
}

void SendMessage(char message[], std::vector<Client> clientList) {
	for (auto &client : clientList) SendMessage(message, client);
}

void ReceiveMessage(char message[], Client client) {
	recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &client.address, &client.addrLength);
}