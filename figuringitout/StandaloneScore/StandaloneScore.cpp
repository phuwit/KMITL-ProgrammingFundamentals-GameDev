#include <vector>

#include "link/ReadScores.cpp"
#include "link/SaveScores.cpp"
#include "link/Score.cpp"
#include "link/SortScores.cpp"

int main () {
    std::vector<Score> scores;
    scores.push_back(Score("John", 100));
    scores.push_back(Score("Mary", 200));
    scores.push_back(Score("Peter", 50));
    scores.push_back(Score("Jane", 300));
    scores.push_back(Score("Paul", 150));

    sortScore(scores);
    saveScore(scores);
}