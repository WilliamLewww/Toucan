#include "net.h"

void ReceiveTimeout();

void Initialize() {
	WSAStartup(MAKEWORD(2, 2), &wsa);
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset((char *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
}

void CleanUp() {
	closesocket(s);
	WSACleanup();
}

void SendMessage(char message[]) {
	sendto(s, message, strlen(message), 0, (struct sockaddr *) &server, slen);
}

std::string ReceiveMessage() {
	messageReceived = false;
	memset(buf, '\0', BUFLEN);
	std::thread tryReceive(ReceiveTimeout);

	std::clock_t start;
	double duration = 0;
	start = std::clock();

	while (duration < 5 && messageReceived == false) {
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	}

	tryReceive.detach();
	return std::string(buf);
}

void ReceiveTimeout() {
	recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &server, &slen);
	messageReceived = true;
}

void SetServerIP(char IP[]) {
	server.sin_addr.S_un.S_addr = inet_addr(IP);
}