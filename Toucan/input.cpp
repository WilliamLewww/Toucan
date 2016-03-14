#include "input.h"

std::vector<SDL_Keycode> Input::keyList;
bool Input::leftButtonDown;
int Input::mouseX, Input::mouseY;

void Input::GetKeys(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		if (std::find(Input::keyList.begin(), Input::keyList.end(), event.key.keysym.sym) == Input::keyList.end()) {
			Input::keyList.push_back(event.key.keysym.sym);
		}
	}

	if (event.type == SDL_KEYUP) {
		Input::keyList.erase(std::remove(Input::keyList.begin(), Input::keyList.end(), event.key.keysym.sym), Input::keyList.end());
	}
}

void Input::GetButtons(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			leftButtonDown = true;
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			leftButtonDown = false;
		}
	}

	if (event.type == SDL_MOUSEMOTION) {
		mouseX = event.motion.x;
		mouseY = event.motion.y;
	}
}