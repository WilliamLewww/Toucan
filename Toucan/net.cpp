#include "net.h"

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

char * SendMessage(char message[]) {
	sendto(s, message, strlen(message), 0, (struct sockaddr *) &server, slen);
	memset(buf, '\0', BUFLEN);
	recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &server, &slen);
	return buf;
}

void SetServerIP(char IP[]) {
	server.sin_addr.S_un.S_addr = inet_addr(IP);
}