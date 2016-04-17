#pragma once
#include <SDL.h>
#include <vector>
#include <algorithm>

void GetKeys(SDL_Event event);
extern std::vector<SDL_Keycode> keyList;

void GetButtons(SDL_Event event);
extern bool leftButtonDown;
extern int mouseX, mouseY;