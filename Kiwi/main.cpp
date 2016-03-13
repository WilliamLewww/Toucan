#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

#define BUFLEN 512
#define PORT 27861

bool isRunning = 1;
int main() {
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[BUFLEN];
	WSADATA wsa;

	slen = sizeof(si_other);

	WSAStartup(MAKEWORD(2, 2), &wsa);
	s = socket(AF_INET, SOCK_DGRAM, 0);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	bind(s, (struct sockaddr *)&server, sizeof(server));

	while (isRunning) {
		printf("Waiting for data...\n");

		memset(buf, '\0', BUFLEN);
		recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);

		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n", buf);

		sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen);
	}

	closesocket(s);
	WSACleanup();

	return 0;
}