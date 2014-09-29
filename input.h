#pragma once

#include <map>

#include <SDL.h>

#include "vector.h"

class Input {
public:
	void beginNewFrame();
	void handleEvent(const SDL_Event& e);
	void pressKey(SDL_Keycode key);
	void releaseKey(SDL_Keycode key);
	bool wasKeyPressed(SDL_Keycode key) const;
	bool wasKeyReleased(SDL_Keycode key) const;
	bool isKeyHeld(SDL_Keycode key) const;
	void mouseClick(int button, int x, int y);
	bool wasMouseClicked(int button) const;
	Vector<int> getMouseClickPosition(int button) const;
private:
	std::map<SDL_Keycode, bool> pressed;
	std::map<SDL_Keycode, bool> released;
	std::map<SDL_Keycode, bool> held;
	std::map<int, Vector<int>> mouse;
};
