#pragma once

#include <string>

class Score {
private:
    std::string m_Name;
    unsigned int m_Score;
public:
    Score();
    Score(std::string name, unsigned int score);
    std::string getName();
    unsigned int getScore();
};