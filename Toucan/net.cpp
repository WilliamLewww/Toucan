#include "net.h"

std::string newestReply;
std::string newestAdvert;

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

void ReceiveMessage() {
	while (true) {
		recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &server, &slen);
		std::string message(buf);

		if (message.substr(0, 5).compare("reply") == 0) newestReply = buf;
		else if (message.substr(0, 6).compare("advert") == 0) newestAdvert = buf;
	}
}

std::string ReceiveInitialMessage() {
start:
	messageReceived = false;
	memset(buf, '\0', BUFLEN);
	std::thread tryReceive(ReceiveTimeout);

	std::clock_t initial;
	double duration = 0;
	initial = std::clock();

	while (duration < 5 && messageReceived == false) {
		duration = (std::clock() - initial) / (double)CLOCKS_PER_SEC;
	}

	tryReceive.detach();

	std::string message(buf);
	if (message.substr(0, 5).compare("reply") == 0 || message.substr(0, 6).compare("advert") == 0) goto start;

	return message;
}

void ReceiveTimeout() {
	recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &server, &slen);
	messageReceived = true;
}

void SetServerIP(char IP[]) {
	server.sin_addr.S_un.S_addr = inet_addr(IP);
}