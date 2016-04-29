#pragma once
#include "client.h"
#include "connection.h"

static const int SCREENWIDTH = 800, SCREENHEIGHT = 600;

void SendMessage(char message[], Client client);
void SendMessage(char message[], std::vector<Client> clientList);
void SendMessage(char message[], Client negClient, std::vector<Client> clientList);
void ReceiveMessage(char message[], Client client);

extern std::vector<Client> clientList;
static Client tempClient;