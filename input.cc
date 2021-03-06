#include "input.h"

#include <SDL.h>

void Input::beginNewFrame()
{
        pressed.clear();
        released.clear();
        mouse.clear();
}

void Input::pressKey(SDL_Keycode key)
{
        pressed[key] = true;
        held[key] = true;
}

void Input::releaseKey(SDL_Keycode key)
{
        released[key] = true;
        held[key] = false;
}

bool Input::wasKeyPressed(SDL_Keycode key) const
{
        return pressed.find(key) != pressed.end();
}

bool Input::wasKeyReleased(SDL_Keycode key) const
{
        return released.find(key) != released.end();
}

bool Input::isKeyHeld(SDL_Keycode key) const
{
        auto it = held.find(key);
        return it != held.end() ? it->second : false;
}

void Input::mouseClick(int button, int x, int y)
{
        mouse[button] = {x, y};
}

bool Input::wasMouseClicked(int button) const
{
        return mouse.find(button) != mouse.end();
}

Vector<int> Input::getMouseClickPosition(int button) const
{
        return mouse.at(button);
}

Vector<float> Input::getAxis() const
{
        return {x / 32768.0f, y / 32768.0f};
}

Input::JoystickButtonState Input::getButton(unsigned int index) const
{
        if (joystick_buttons_.size() <= index)
                return NOT_PRESSED;
        return joystick_buttons_.at(index);
}

bool Input::isButtonHeld(unsigned int index) const
{
        if (joystick_buttons_.size() <= index)
                return false;
        switch (joystick_buttons_.at(index)) {
        case HELD:
        case PRESSED:
                return true;
        default:
                return false;
        }
}

bool Input::wasButtonPressed(unsigned int index) const
{
        if (joystick_buttons_.size() <= index)
                return false;
        return joystick_buttons_.at(index) == PRESSED;
}

void Input::handleEvent(const SDL_Event &e)
{
        switch (e.type) {
        case SDL_KEYDOWN:
                if (!e.key.repeat)
                        pressKey(e.key.keysym.sym);
                break;
        case SDL_KEYUP:
                releaseKey(e.key.keysym.sym);
                break;
        case SDL_MOUSEBUTTONDOWN:
                mouseClick(e.button.button, e.button.x, e.button.y);
                break;
        }
}

void Input::openJoystick(unsigned int index)
{
        joysticks_.push_back(SDL_JoystickOpen(index));
        auto js = joysticks_[joysticks_.size() - 1];
        if (js) {
                printf("Opened Joystick 0\n");
                printf("Name: %s\n", SDL_JoystickNameForIndex(0));
                printf("Number of Axes: %d\n", SDL_JoystickNumAxes(js));
                printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(js));
                printf("Number of Balls: %d\n", SDL_JoystickNumBalls(js));
                joystick_buttons_.assign(SDL_JoystickNumButtons(js),
                                         NOT_PRESSED);
        }
}

void Input::handleJoystick(unsigned int index)
{
        if (joysticks_.size() <= index)
                return;

        x = SDL_JoystickGetAxis(joysticks_[index], 0);
        y = SDL_JoystickGetAxis(joysticks_[index], 1);

        for (unsigned int i = 0; i < joystick_buttons_.size(); i++) {
                switch (joystick_buttons_[i]) {
                case NOT_PRESSED:
                        if (SDL_JoystickGetButton(joysticks_[index], i))
                                joystick_buttons_[i] = PRESSED;
                        break;
                case PRESSED:
                case HELD:
                        if (SDL_JoystickGetButton(joysticks_[index], i))
                                joystick_buttons_[i] = HELD;
                        else
                                joystick_buttons_[i] = RELEASED;
                        break;
                case RELEASED:
                        if (SDL_JoystickGetButton(joysticks_[index], i))
                                joystick_buttons_[i] = PRESSED;
                        else
                                joystick_buttons_[i] = NOT_PRESSED;
                        break;
                }
        }
}
