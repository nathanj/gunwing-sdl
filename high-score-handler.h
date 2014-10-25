#pragma once

#include "input.h"
#include "graphics.h"
#include "high-score-list.h"

class HighScoreHandler
{
  public:
        HighScoreHandler(int score, bool won);
        void handleInput(const Input& input);
        void draw(Graphics& graphics);
        char upChar(char c);
        char downChar(char c);
        bool finished()
        {
                return finished_;
        }

  private:
        char initials_[4]{'A', 'A', 'A', '\0'};
        int position_{0};
        int high_position_{0};
        int score_{0};
        bool won_{false};
        bool finished_{false};
        void drawHighScoreLine(Graphics& graphics, const std::string& label,
                               const std::string& initials, int score, int x,
                               int y, Color* color);
        void finalizeHighScore();
        HighScoreList high_score_list_;
};
