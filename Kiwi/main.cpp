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
		std::cout << buf << std::endl;

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
				InitializePlayer(tempClient);
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

void SendMessage(char message[], std::vector<Client> clientList) {
	for (auto &client : clientList) SendMessage(message, client);
}

void ReceiveMessage(char message[], Client client) {
	recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &client.address, &client.addrLength);
}