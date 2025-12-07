#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Range {
    long long start;
    long long end;
};

vector<Range> readInput() {
    string input;

    cin >> input;
    stringstream inputStream(input);

    vector<Range> ranges;
    string inputRange;
    while(getline(inputStream, inputRange, ',')) {
        stringstream separatedRange(inputRange);

        string segStart;
        string segEnd;

        getline(separatedRange, segStart, '-');
        getline(separatedRange, segEnd, '-');

        ranges.push_back(Range{stoll(segStart), stoll(segEnd)});
    }

    return ranges;
}

long long getInvalidIdFromPrefix(int idPrefix) {
    string nextIdAsString = to_string(idPrefix) + to_string(idPrefix);

    long long nextID = stoll(nextIdAsString);

    return nextID;
}

long long getLargestID(vector<Range> &ranges) {
    long long maxi = ranges[0].end;

    for(auto range : ranges) {
        maxi = max(maxi, range.end);
    }

    return maxi;
}

long long getInvalidCount(vector<Range> &ranges) {
    long long result = 0;

    long long idPrefix = 1;
    long long nextInvalidID = getInvalidIdFromPrefix(idPrefix);

    long long largestID = getLargestID(ranges);

    while(nextInvalidID <= largestID) {
        for (auto range : ranges) {
            if (range.start <= nextInvalidID && nextInvalidID <= range.end) {
                result += nextInvalidID;
            }
        }

        idPrefix++;
        nextInvalidID = getInvalidIdFromPrefix(idPrefix);
    }

    return result;
}

long long solve(vector<Range> &ranges) {
    long long result = getInvalidCount(ranges);

    return result;
}

int main(void) {
    vector<Range> ranges = readInput();

    long long result = solve(ranges);

    cout << result << '\n';

    return 0;
}
