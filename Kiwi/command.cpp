#include "command.h"

int ProcessCommand(char buf[]) {
	std::string command(buf);
	if (command.compare("connect") == 0) return 0;

	return -1;
}