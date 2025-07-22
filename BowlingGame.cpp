#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getRollValue(const string& roll) {
    if (roll == "X") return 10;
    if (roll == "/") return -1; // Placeholder for spare
    return stoi(roll);
}

int calculateScore(const vector<string>& rolls) {
    int score = 0;
    int rollIndex = 0;
    
    for (int frame = 1; frame <= 10; ++frame) {
        string roll1 = rolls[rollIndex];
        
        if (roll1 == "X") {
            // Strike
            score += 10;
            string next1 = rolls[rollIndex + 1];
            string next2 = rolls[rollIndex + 2];

            int bonus1 = (next1 == "X") ? 10 : getRollValue(next1);
            int bonus2;
            if (next2 == "/") {
                bonus2 = 10 - bonus1;
            } else {
                bonus2 = (next2 == "X") ? 10 : getRollValue(next2);
            }

            score += bonus1 + bonus2;
            rollIndex += 1;
        } else {
            // Normal frame or spare
            int firstRoll = getRollValue(roll1);
            string roll2 = rolls[rollIndex + 1];
            int secondRoll;

            if (roll2 == "/") {
                secondRoll = 10 - firstRoll;
                string nextRoll = rolls[rollIndex + 2];
                int bonus = (nextRoll == "X") ? 10 : getRollValue(nextRoll);
                score += 10 + bonus;
            } else {
                secondRoll = getRollValue(roll2);
                score += firstRoll + secondRoll;
            }

            rollIndex += 2;
        }
    }

    return score;
}

int main() {
    vector<string> rolls = { "1", "4", "4", "5", "6", "5", "X", "0", "1", "7", "2", "6", "/", "X", "2", "6" };

    int totalScore = calculateScore(rolls);
    cout << "Total Bowling Score: " << totalScore << endl;

    return 0;
}
