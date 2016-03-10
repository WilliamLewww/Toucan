#include <winsock2.h>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include "main.h"

#pragma comment(lib, "ws2_32.lib")

#define SERVER "127.0.0.1"
#define BUFLEN 512
#define PORT 27861

void Update(int gameTime);
void Render(SDL_Window* window, SDL_GLContext context);
char * SendMessage(char message[]);

WSADATA wsa;
SDL_Event event;
SDL_GLContext context;

struct sockaddr_in si_other;
int s, slen = sizeof(si_other);
char buf[BUFLEN];

bool isRunning = true;
int frameStart, frameEnd, deltaTime = 0;
int main(int argc, char *argv[]) {
	displayWindow = SDL_CreateWindow("Mallard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(displayWindow);
	glOrtho(-SCREENWIDTH / 2, SCREENWIDTH / 2, SCREENHEIGHT / 2, -SCREENHEIGHT / 2, 0, 1);

	WSAStartup(MAKEWORD(2, 2), &wsa);
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				isRunning = false;
		}

		if (deltaTime < 1) {
			frameStart = SDL_GetTicks();
			SDL_Delay(1);
			frameEnd = SDL_GetTicks();
			deltaTime = frameEnd - frameStart;
		}
		frameStart = SDL_GetTicks();
		Update(deltaTime);
		Render(displayWindow, context);
		frameEnd = SDL_GetTicks();
		deltaTime = frameEnd - frameStart;
	}

	closesocket(s);
	WSACleanup();

	return 0;
}

void Update(int gameTime) {

}

void Render(SDL_Window* window, SDL_GLContext context) {
	SDL_GL_MakeCurrent(window, context);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	SDL_GL_SwapWindow(window);
}

char * SendMessage(char message[]) {
	sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen);
	memset(buf, '\0', BUFLEN);
	recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
	return buf;
}