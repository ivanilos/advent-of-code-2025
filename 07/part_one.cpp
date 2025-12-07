#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <set>
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
    set<int> beamCols;

    for (int j = 0; j < (int)grid[0].size(); j++) {
        if (grid[0][j] == 'S') {
            beamCols.insert(j);
        }
    }

    int result = 0;
    set<int> nextBeamCols;
    for (int i = 0; i < (int)grid.size() - 1; i++) {
        for (int col : beamCols) {
            if (isColInGrid(grid, i, col) && grid[i][col] == '^') {
                result++;
                nextBeamCols.insert(col - 1);
                nextBeamCols.insert(col + 1);
            } else {
                nextBeamCols.insert(col);
            }
        }

        beamCols = move(nextBeamCols);
    }

    return result;
}

int main(void) {
    vector<string> grid = readInput();

    long long result = solve(grid);

    cout << result << '\n';

    return 0;
}
