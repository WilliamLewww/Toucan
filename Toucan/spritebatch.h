#pragma once
#include "main.h"
#include "vector2.h"
#include <SOIL.h>
#include <SDL_opengl.h>

GLuint LoadTexture(const char* path);
void DrawRect(Vector2 position, int width, int height);
void DrawRect(Vector2 position, int width, int height, int color[3]);
void DrawRect(GLuint texture, Vector2 position, int width, int height);