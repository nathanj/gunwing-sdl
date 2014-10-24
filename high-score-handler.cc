#include "high-score-handler.h"

#include "text.h"
#include "font-score.h"

HighScoreHandler::HighScoreHandler(int score, bool won)
	: score_{score},
	won_{won}
{
}

void HighScoreHandler::handleInput(const Input &input)
{
        if (input.wasKeyPressed(SDLK_UP))
                initials_[position_] = upChar(initials_[position_]);
        else if (input.wasKeyPressed(SDLK_DOWN))
                initials_[position_] = downChar(initials_[position_]);
	else if (input.wasKeyPressed(SDLK_LEFT))
		position_ = (position_ - 1 + 3) % 3;
	else if (input.wasKeyPressed(SDLK_RIGHT))
		position_ = (position_ + 1) % 3;
	else if (input.wasKeyPressed(SDLK_SPACE))
		finalizeHighScore();
}

void HighScoreHandler::draw(Graphics& graphics)
{
	const std::string labels[] = { "1st", "2nd", "3rd", "4th", "5th" };
	Text::drawString(graphics, won_ ? "You Win!" : "Game Over", 100, 30);
	for (int i = 0; i < 5; i++) {
		auto e = high_score_list_.getPosition(i);
		drawHighScoreLine(graphics, labels[i], e.initials, e.score,
				  50, 100 + 60 * i);
	}
}

void HighScoreHandler::drawHighScoreLine(Graphics& graphics,
					 const std::string& label,
					 const std::string& initials,
					 int score, int x, int y)
{
	Text::drawString(graphics, label, x, y);
	// todo yellow
	Text::drawString(graphics, initials, x + 100, y);
	FontScore::draw(graphics, score, x + 200, y + 13);
}

void HighScoreHandler::finalizeHighScore()
{
	high_score_list_.insert(std::string(initials_, 3), score_);
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
