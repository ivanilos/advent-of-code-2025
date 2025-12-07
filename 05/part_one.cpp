#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Range {
    long long l;
    long long r;
};

struct Input {
    vector<Range> ranges;
    vector<long long> ingredients;
};

Input readInput() {
    vector<Range> ranges;
    vector<long long> ingredients;

    string line;
    bool firstInputPart = true;
    while(getline(cin, line)) {
        if (line.empty()) {
            firstInputPart = false;
            continue;
        }

        if (firstInputPart) {
            long long l, r;
            sscanf(line.c_str(), "%lld-%lld", &l, &r);
            ranges.push_back(Range{l, r});
        } else {
            long long ingredient;
            sscanf(line.c_str(), "%lld", &ingredient);
            ingredients.push_back(ingredient);
        }
    }

    return Input{ranges, ingredients};
}

int solve(vector<Range> &ranges, vector<long long>& ingredients) {
    int result = 0;
    for (long long ingredient : ingredients) {
        for (auto range : ranges) {
            if (range.l <= ingredient && ingredient <= range.r) {
                result++;
                break;
            }
        }
    }

    return result;
}

int main(void) {
    Input input = readInput();

    int result = solve(input.ranges, input.ingredients);

    cout << result << '\n';

    return 0;
}

