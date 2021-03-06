#pragma once
#include <vector>
#include <string>
#include <thread>
#include <ctime>
#include <iostream>
#include "client.h"
#include "main.h"

#define BUFLEN 512

static const int maxConnections = 100;
static int curConnections;

bool AddConnection(Client client);
void CheckConnection();
int ProcessCommand(char buf[]);

int GetConnectionCount();
void InitializePlayer(Client &client);
void RequestPlayer(Client client);
void UpdatePosition(Client &client, char buf[]);