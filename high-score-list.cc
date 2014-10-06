#include "high-score-list.h"

#include <algorithm>
#include <fstream>
#include <cstring>

#include "utils.h"

HighScoreList::HighScoreList() :
        list_(5)
{
        list_.reserve(6);
        loadHighScores();
}

void HighScoreList::clearHighScores()
{
        for (auto& e : list_) {
                e.first = 0;
                e.second = "---";
        }
}

int HighScoreList::findPosition(int score)
{
        for (int i = 0; i < 5; i++)
                if (score > list_[i].first)
                        return i;

        return -1;
}

void HighScoreList::insert(std::string initials, int score)
{
        auto it = std::find_if(std::begin(list_), std::end(list_),
                               [&](std::pair<int, std::string> value) {
                                       return score > value.first;
                               });
        if (it == list_.end())
                return;

        list_.insert(it, std::make_pair(score, initials));
        list_.pop_back();
}

void HighScoreList::saveHighScores()
{
        using std::ios;
        std::ofstream os{filename_, ios::out | ios::trunc | ios::binary};

        for (const auto& e : list_)
                os << e.first << " " << e.second << std::endl;
}

void HighScoreList::loadHighScores()
{
        std::ifstream is{filename_};

        if (is.fail()) {
                LOG("error opening " << filename_ << ": " << strerror(errno));
                clearHighScores();
                return;
        }

        for (auto& e : list_)
                is >> e.first >> e.second;
}
