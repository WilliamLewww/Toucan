#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <thread>
#include <ctime>
#include <iostream>

#define BUFLEN 512
#define PORT 27861

static WSADATA wsa;
static struct sockaddr_in server;
static int s, slen = sizeof(server);
static char buf[BUFLEN];

static bool messageReceived;

void SendMessage(char message[]);
void SendMessageWithTimer(char message[]);

std::string ReceiveInitialMessage();
void Initialize();
void CleanUp();
void SetServerIP(char IP[]);

void SendMessageTimer();
extern bool resetTimer;

void ReceiveMessage();
void ResetAdvert();
void ResetReply();
extern std::string newestReply;
extern std::string newestAdvert;

int ProcessMessage(std::string message);