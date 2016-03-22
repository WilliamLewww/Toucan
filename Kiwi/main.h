#pragma once
#include "client.h"
#include "command.h"
#include "connection.h"

void SendMessage(char message[], Client client);
void ReceiveMessage(char message[], Client client);