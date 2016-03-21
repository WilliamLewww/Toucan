#include "connection.h"

bool AddConnection(Client client, std::vector<Client> clientList) {
	CheckConnection();

	if (curConnections < maxConnections) {
		clientList.push_back(client);
		curConnections += 1;
		return true;
	}

	return false;
}

void CheckConnection() {

}