#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

const int MAX_NEIGHBOR_ALLOWED = 4;

vector<string> readInput() {
    vector<string> input;

    string line;
    while(cin >> line) {
        input.push_back(line);
    }

    return input;
}

bool isIn(int x, int y, vector<string> grid) {
    return 0 <= x && x < (int)grid.size() && 0 <= y && y < (int)grid[x].size();
}

int getNeighborCount(int i, int j, vector<string> grid) {
    int result = 0;

    for (int k = -1; k <= 1; k++) {
        for (int p = -1; p <= 1; p++) {
            if (k == 0 && p == 0) {
                continue;
            }

            int x = i + k;
            int y = j + p;

            if (isIn(x, y, grid) && grid[x][y] == '@') {
                result++;
            }
        }
    }

    return result;
}

int solve(vector<string> grid) {
    int result = 0;

    vector<pair<int, int>> nextIterationRolls;
    for (int i = 0; i < (int)grid.size(); i++) {
        for (int j = 0; j < (int)grid[i].size(); j++) {
            if (grid[i][j] == '@') {
                nextIterationRolls.push_back({i, j});
            }
        }
    }

    vector<pair<int, int>> rolls;
    while(nextIterationRolls.size() != rolls.size()) {
        rolls = move(nextIterationRolls);

        for (auto it : rolls) {
            int x = it.first;
            int y = it.second;
            if (getNeighborCount(x, y, grid) < MAX_NEIGHBOR_ALLOWED) {
                grid[x][y] = 'X';
                result++;
            } else {
                nextIterationRolls.push_back(it);
            }
        }
    }

    return result;
}

int main(void) {
    vector<string> grid = readInput();

    int result = solve(grid);

    cout << result << '\n';

    return 0;
}
