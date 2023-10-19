#include "SaveScores.hpp"

void saveScore(std::vector<Score>& scores) {
    std::ofstream file;
    file.open("scores.csv", std::ios::out);
    for (auto & score : scores) {
        file << score.getName() << "," << score.getScore() << std::endl;
    }
    file.close();
}
