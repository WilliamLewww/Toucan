#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include "main.h"
#include "net.h"
#include "joiner.h"
#include "input.h"
#include "player.h"
#include "environment.h"
#include <iostream>

static const int SCREENWIDTH = 800, SCREENHEIGHT = 600;
static SDL_Window* displayWindow;

static bool connected;