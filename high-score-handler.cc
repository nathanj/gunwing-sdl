#include "high-score-handler.h"

void HighScoreHandler::handleInput(const Input &input)
{
        if (input.wasKeyPressed(SDLK_UP))
                initials_[initial_position_] = upChar(initials_[initial_position_]);
        else if (input.wasKeyPressed(SDLK_DOWN))
                initials_[initial_position_] = downChar(initials_[initial_position_]);
}

char HighScoreHandler::upChar(char c)
{
        const char *str = "_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        if (c == '9')
                return '_';
        return str[strchr(str, c) - str + 1];
}

char HighScoreHandler::downChar(char c)
{
        const char *str = "_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        if (c == '_')
                return '9';
        return str[strchr(str, c) - str - 1];
}
