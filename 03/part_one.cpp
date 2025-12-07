#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> readInput() {
    vector<string> input;

    string line;
    while(cin >> line) {
        input.push_back(line);
    }

    return input;
}

int solve(vector<string> banks) {
    int result = 0;

    for (auto bank : banks) {
        int best = 0;
        int maxJoltageSeen = 0;

        for (int i = 0; i < (int)bank.size(); i++) {
            best = max(best, 10 * maxJoltageSeen + bank[i] - '0');
            maxJoltageSeen = max(maxJoltageSeen, bank[i] - '0');
        }

        result += best;
    }

    return result;
}

int main(void) {
    vector<string> banks = readInput();

    int result = solve(banks);

    cout << result << '\n';

    return 0;
}
