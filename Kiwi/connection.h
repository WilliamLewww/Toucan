#pragma once
#include <vector>
#include "client.h"

static const int maxConnections = 5;
static int curConnections;

bool AddConnection(Client client, std::vector<Client> clientList);
void CheckConnection();