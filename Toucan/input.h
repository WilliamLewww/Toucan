#pragma once
#include <SDL.h>
#include <vector>
#include <algorithm>
class Input
{
public:
	static void GetKeys(SDL_Event event);
	static std::vector<SDL_Keycode> keyList;

	static void GetButtons(SDL_Event event);
	static bool leftButtonDown;
	static int mouseX, mouseY;
};