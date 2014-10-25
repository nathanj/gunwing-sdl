#pragma once

#include <vector>
#include <utility>
#include <string>

struct HighScoreEntry {
	int score;
	std::string initials;
};

class HighScoreList
{
  public:
        HighScoreList();
        void clearHighScores();
        int findPosition(int score);
	HighScoreEntry getPosition(int index);
        void insert(std::string initials, int score);
        void update(int position, std::string initials, int score);
        void saveHighScores();
        void loadHighScores();

  private:
        std::vector<HighScoreEntry> list_;
        static constexpr char const *filename_{"highscores.txt"};
};
