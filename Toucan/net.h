#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <iostream>;

#define BUFLEN 512
#define PORT 27861

static WSADATA wsa;
static struct sockaddr_in server;
static int s, slen = sizeof(server);
static char buf[BUFLEN];

char * SendMessage(char message[]);
void Initialize();
void CleanUp();
void SetServerIP(char IP[]);