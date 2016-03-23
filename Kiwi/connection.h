#pragma once
#include <vector>
#include <string>
#include <thread>
#include <ctime>
#include "client.h"
#include "main.h"

#define BUFLEN 512

static const int maxConnections = 5;
static int curConnections;

bool AddConnection(Client client, std::vector<Client> clientList);
void CheckConnection();

//TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST
//TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST
//TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST
bool PingClient(Client client);