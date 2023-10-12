#pragma once

#include <vector>
#include <algorithm>

#include "Score.cpp"

bool scoreGreater(Score& score1, Score& score2) {
    return score1.getScore() > score2.getScore();
}

void sortScore(std::vector<Score>& score) {
    std::sort(score.begin(), score.end(), scoreGreater);

    if (score.size() > 5) {
        score.resize(5);
    }
}
