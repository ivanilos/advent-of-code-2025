#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

vector<string> readInput() {
    vector<string> input;

    string line;
    while(getline(cin, line)) {
        input.push_back(line);
    }

    return input;
}

long long mul(vector<string>& homework, int startCol, int endCol) {
    long long result = 1;

    for (int j = startCol; j <= endCol; j++) {
        string curOperand;
        for (int i = 0; i < (int)homework.size() - 1; i++) {
            curOperand += homework[i][j];
        }
        result *= stoll(curOperand);
    }


    return result;
}

long long add(vector<string>& homework, int startCol, int endCol) {
    long long result = 0;

    for (int j = startCol; j <= endCol; j++) {
        string curOperand;
        for (int i = 0; i < (int)homework.size() - 1; i++) {
            curOperand += homework[i][j];
        }
        result += stoll(curOperand);
    }

    return result;
}

vector<int> getSeparators(vector<string>& homework) {
    vector<int> separators;

    separators.push_back(-1);

    for (int j = 0; j < (int)homework[0].size(); j++) {
        bool isSeparator = true;
        for (int i = 0; i < (int)homework.size(); i++) {
            if (homework[i][j] != ' ') {
                isSeparator = false;
                break;
            }
        }

        if (isSeparator) {
            separators.push_back(j);
        }
    }

    separators.push_back(homework[0].size());
    return separators;
}

long long solve(vector<string>& homework) {
    long long result = 0;

    int n = homework.size();

    vector<int> separators = getSeparators(homework);

    for (int i = 1; i < (int)separators.size(); i++) {
        int startCol = separators[i - 1] + 1;
        int endCol = separators[i] - 1;

        if (homework[n - 1][startCol] == '+') {
            result += add(homework, startCol, endCol);
        } else {
            result += mul(homework, startCol, endCol);
        }
    }

    return result;
}

int main(void) {
    vector<string> homework = readInput();

    long long result = solve(homework);

    cout << result << '\n';

    return 0;
}
