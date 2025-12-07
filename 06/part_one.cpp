#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

vector<vector<string>> readInput() {
    vector<vector<string>> input;

    string line;
    while(getline(cin, line)) {
        input.push_back(vector<string>());

        stringstream inputStream(line);

        string operand;
        while(inputStream >> operand) {
            input[input.size() - 1].push_back(operand);
        }
    }

    return input;
}

long long mul(vector<vector<string>>& homework, int col) {
    long long result = 1;

    for (int i = 0; i < (int)homework.size() - 1; i++) {
        result *= stoll(homework[i][col]);
    }

    return result;
}

long long add(vector<vector<string>>& homework, int col) {
    long long result = 0;

    for (int i = 0; i < (int)homework.size() - 1; i++) {
        result += stoll(homework[i][col]);
    }

    return result;
}

long long solve(vector<vector<string>>& homework) {
    long long result = 0;

    int n = homework.size();
    for (int j = 0; j < (int)homework[0].size(); j++) {
        if (homework[n - 1][j] == "+") {
            result += add(homework, j);
        } else {
            result += mul(homework, j);
        }
    }

    return result;
}

int main(void) {
    vector<vector<string>> homework = readInput();

    long long result = solve(homework);

    cout << result << '\n';

    return 0;
}
