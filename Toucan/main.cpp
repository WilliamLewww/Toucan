#include "main.h"

void Update(int gameTime);
void Render(SDL_Window* window, SDL_GLContext context);

SDL_Event event;
SDL_GLContext context;

Joiner joiner;

bool isRunning = true;
int frameStart, frameEnd, deltaTime = 0;
int main(int argc, char *argv[]) {
	Initialize();

	char tempServer[512];
	std::string connectString = "connect";
	while (!connected) {
		std::cin >> tempServer;
		SetServerIP(tempServer);

		SendMessage("connect");
		if (ReceiveInitialMessage().compare("connect") == 0) {
			connected = true;
		}
	}

	GetMap();
	InitializePlayer();
	RequestPlayer();

	displayWindow = SDL_CreateWindow("Toucan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(displayWindow);
	glOrtho(-SCREENWIDTH / 2, SCREENWIDTH / 2, SCREENHEIGHT / 2, -SCREENHEIGHT / 2, 0, 1);

	std::thread listener(ReceiveMessage);

	joiner.LoadContent();

	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				isRunning = false;

			GetKeys(event);
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

	listener.detach();
	CleanUp();
	return 0;
}

void Update(int gameTime) {
	joiner.Update(gameTime);

	if (ProcessMessage(newestAdvert) == 1) {
		UpdatePlayer(newestAdvert);
	}
}

void Render(SDL_Window* window, SDL_GLContext context) {
	SDL_GL_MakeCurrent(window, context);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	joiner.Render();

	SDL_GL_SwapWindow(window);
}