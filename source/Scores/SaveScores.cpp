#pragma once

#include <vector>
#include <fstream>
#include <iostream>

#include "Score.cpp"

void saveScore(std::vector<Score>& score) {
    std::ofstream file("scores.bin", std::ios::binary);
    for (int i = 0; i < score.size(); i++) {
        file.write((char*)&score[i], sizeof(Score));
    }
    file.close();
}
