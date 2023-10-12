#pragma once

#include <vector>
#include <fstream>
#include <iostream>

#include "Score.cpp"

std::vector<Score> readScore() {
    std::vector<Score> score;
    std::ifstream file("scores.bin", std::ios::binary);
    if (file.is_open()) {
        while (!file.eof()) {
            Score tempScore;
            file.read((char*)&tempScore, sizeof(Score));
            score.push_back(tempScore);
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    file.close();
    return score;
}
