#pragma once
#include "client.h"
#include "connection.h"

static const int SCREENWIDTH = 800, SCREENHEIGHT = 600;

void SendMessage(char message[], Client client);
void ReceiveMessage(char message[], Client client);

static std::vector<Client> clientList;
static Client tempClient;