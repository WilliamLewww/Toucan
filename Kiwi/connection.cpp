#include "connection.h"

bool AddConnection() {
	CheckConnection();

	if (curConnections < maxConnections) {
		curConnections += 1;
		return true;
	}

	return false;
}

void CheckConnection() {

}