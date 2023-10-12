#pragma once

#include "Score.hpp"

Score::Score() {
    m_Name = "no data";
    m_Score = 123;
}

Score::Score(std::string name, unsigned int score) {
    m_Name = name;
    m_Score = score;
}

std::string Score::getName() {
    return m_Name;
}

unsigned int Score::getScore() {
    return m_Score;
}