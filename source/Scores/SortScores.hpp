#pragma once

#include <vector>
#include <algorithm>

#include "Score.hpp"

bool scoreGreater(Score& score1, Score& score2);
void sortScore(std::vector<Score>& score);