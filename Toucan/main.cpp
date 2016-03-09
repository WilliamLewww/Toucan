#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

#define SERVER "127.0.0.1"
#define BUFLEN 512
#define PORT 27861

int main(void)
{
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;

	WSAStartup(MAKEWORD(2, 2), &wsa);
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	while (1)
	{
		printf("Enter message : ");
		std::cin >> (message);

		sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen);
		memset(buf, '\0', BUFLEN);
		recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
		std::cout << buf << std::endl;
	}

	closesocket(s);
	WSACleanup();

	return 0;
}