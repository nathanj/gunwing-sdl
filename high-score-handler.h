#pragma once

#include "input.h"

class HighScoreHandler {
public:
        void handleInput(const Input &input);
        char upChar(char c);
        char downChar(char c);
private:
        char initials_[3]{ 'A', 'A', 'A' };
        int initial_position_{0};
};
