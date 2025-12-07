#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

vector<string> readInput() {
    vector<string> input;

    string line;
    while(cin >> line) {
        input.push_back(line);
    }

    return input;
}

bool isColInGrid(vector<string>& grid, int row, int col) {
    return 0 <= col && col < (int)grid[row].size();
}

long long solve(vector<string>& grid) {
    map<int, long long> beamCols;

    for (int j = 0; j < (int)grid[0].size(); j++) {
        if (grid[0][j] == 'S') {
            beamCols[j] = 1;
        }
    }

    map<int, long long> nextBeamCols;
    for (int i = 0; i < (int)grid.size() - 1; i++) {
        for (auto it : beamCols) {
            if (it.second == 0) {
                continue;
            }

            int col = it.first;
            if (isColInGrid(grid, i, col) && grid[i][col] == '^') {
                nextBeamCols[col - 1] += beamCols[col];
                nextBeamCols[col + 1] += beamCols[col];
            } else {
                nextBeamCols[col] += beamCols[col];
            }
        }

        beamCols = move(nextBeamCols);
    }

    long long result = 0;
    for (auto it : beamCols) {
        result += it.second;
    }

    return result;
}

int main(void) {
    vector<string> grid = readInput();

    long long result = solve(grid);

    cout << result << '\n';

    return 0;
}
