#include "high-score-handler.h"

#include "text.h"
#include "font-score.h"
#include "utils.h"

HighScoreHandler::HighScoreHandler(int score, bool won)
    : score_{score}, won_{won}
{
        TRACE(score_);
        TRACE(won_);
        high_position_ = high_score_list_.findPosition(score_);
        if (high_position_ != -1)
                high_score_list_.insert(initials_, score_);
}

void HighScoreHandler::handleInput(const Input& input)
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
        const std::string labels[] = {"1st", "2nd", "3rd", "4th", "5th"};
        Text::drawString(graphics, won_ ? "You Win!" : "Game Over", 70, 30);
        for (int i = 0; i < 5; i++) {
                if (high_position_ == i) {
                        auto c = Color{0.7f, 0.7f, 0.3f, 1.0f};
                        drawHighScoreLine(graphics, labels[i], initials_,
                                          score_, 10, 100 + 60 * i, &c);
                        Text::drawChar(graphics, '_', 10 + 133 + position_ * 31,
                                       100 + 60 * i, &c);
                } else {
                        auto c = Color{0.0f, 0.0f, 0.0f, 1.0f};
                        if (won_)
                                c = Color{1.0f, 1.0f, 1.0f, 1.0f};
                        auto e = high_score_list_.getPosition(i);
                        drawHighScoreLine(graphics, labels[i], e.initials,
                                          e.score, 10, 100 + 60 * i, &c);
                }
        }
}

void HighScoreHandler::drawHighScoreLine(Graphics& graphics,
                                         const std::string& label,
                                         const std::string& initials, int score,
                                         int x, int y, Color* color)
{
        Text::drawString(graphics, label, x, y, color);
        Text::drawString(graphics, initials, x + 100, y, color);
        FontScore::draw(graphics, score, x + 240, y + 13);
}

void HighScoreHandler::finalizeHighScore()
{
        high_score_list_.update(high_position_, initials_, score_);
        high_score_list_.saveHighScores();
        finished_ = true;
}

char HighScoreHandler::upChar(char c)
{
        const char* str = "-_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        if (c == '9')
                return '-';
        return str[strchr(str, c) - str + 1];
}

char HighScoreHandler::downChar(char c)
{
        const char* str = "-_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        if (c == '-')
                return '9';
        return str[strchr(str, c) - str - 1];
}
