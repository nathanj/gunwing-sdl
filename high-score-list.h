#pragma once

#include <vector>
#include <utility>
#include <string>

class HighScoreList {
public:
        HighScoreList();
        void clearHighScores();
        int findPosition(int score);
        void insert(std::string initials, int score);
        void saveHighScores();
        void loadHighScores();
private:
        std::vector<std::pair<int, std::string>> list_;
        static constexpr char const *filename_{"highscores.txt"};
};
