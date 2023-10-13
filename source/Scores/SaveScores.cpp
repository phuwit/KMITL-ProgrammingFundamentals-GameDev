#pragma once

#include <vector>
#include <fstream>
#include <iostream>

#include "Score.cpp"

void saveScore(std::vector<Score>& scores) {
    std::ofstream file;
    file.open("scores.csv", std::ios::out);
    for (int i = 0; i < scores.size(); i++) {
        file << scores[i].getName() << "," << scores[i].getScore() << std::endl;
    }
    file.close();
}
