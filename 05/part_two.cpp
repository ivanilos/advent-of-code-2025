#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
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

bool operator< (const Range& a, const Range& b) {
    return a.l < b.l;
}

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

long long solve(vector<Range> &ranges) {
    sort(ranges.begin(), ranges.end());

    long long result = 0;
    long long curMax = 0;

    for (auto range : ranges) {
        long long added = max(0LL, range.r - max(range.l - 1LL, curMax));
        result += added;

        curMax = max(curMax, range.r);
    }

    return result;
}

int main(void) {
    Input input = readInput();

    long long result = solve(input.ranges);

    cout << result << '\n';

    return 0;
}

