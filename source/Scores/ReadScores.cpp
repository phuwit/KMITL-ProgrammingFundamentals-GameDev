#include "ReadScores.hpp"

std::vector<Score> readScore() {
    std::vector<Score> scores;
    std::ifstream file("scores.csv", std::ios::in);
    while (file.good()) {
        std::string name;
        int score;
        std::getline(file, name, ',');
        file >> score;
        file.ignore();
        Score tempScore(name, score);
        scores.push_back(tempScore);
    }
    file.close();
    return scores;
}
