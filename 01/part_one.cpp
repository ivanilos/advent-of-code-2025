#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int INITIAL_POS = 50;
const int TOTAL_POS = 100;

struct Operation {
    char side;
    int qt;
};

vector<Operation> readInput() {
    vector<Operation> input;

    string line;
    while(cin >> line) {
        Operation op = Operation{line[0], 0};
        for (int i = 1; i < (int)line.size(); i++) {
            op.qt = 10 * op.qt + line[i] - '0';
        }

        input.push_back(op);
    }

    return input;
}

int main(void) {
    vector<Operation> operations = readInput();

    int result = 0;
    int pos = 50;
    for (auto op : operations) {
        int sign = -1;

        if (op.side == 'R') {
            sign = 1;
        }

        pos = (((pos + sign * op.qt) % TOTAL_POS) + TOTAL_POS) % TOTAL_POS;

        if (pos == 0) {
            result++;
        }
    }

    cout << result << '\n';

    return 0;
}
