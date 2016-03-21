#include <winsock2.h>
#include <iostream>
#include <vector>
#include "client.h"
#include "command.h"
#include "connection.h"

#pragma comment(lib, "ws2_32.lib")

#define BUFLEN 512
#define PORT 27861

void SendMessage(char message[], Client client);

SOCKET s;
WSADATA wsa;

std::vector<Client> clientList;
Client tempClient;

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

	while (isRunning) {
		printf("Waiting for data...\n");

		memset(buf, '\0', BUFLEN);
		recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&tempClient.address, &tempClient.addrLength);
		if (ProcessCommand(buf) == 0) {
			AddConnection(tempClient, clientList);
			SendMessage("connect", tempClient);
		}
	}

	closesocket(s);
	WSACleanup();

	return 0;
}

void SendMessage(char message[], Client client) {
	sendto(s, message, strlen(message), 0, (struct sockaddr *) &client.address, client.addrLength);
}