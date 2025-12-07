#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

const int NEEDED_DIGITS = 12;

vector<string> readInput() {
    vector<string> input;

    string line;
    while(cin >> line) {
        input.push_back(line);
    }

    return input;
}

bool enoughDigitsLeft(int curIdx, int bankSize, int curSize) {
    int digitsLeft = bankSize - curIdx;
    return digitsLeft >= NEEDED_DIGITS - curSize + 1;
}

long long solve(vector<string> banks) {
    long long  result = 0;

    for (auto bank : banks) {
        stack<int> st;

        for (int i = 0; i < (int)bank.size(); i++) {
            int curJoltage = bank[i] - '0';

            while(st.size() > 0 && enoughDigitsLeft(i, bank.size(), st.size()) && st.top() < curJoltage) {
                st.pop();
            }
            st.push(curJoltage);
        }

        long long base = 1;
        long long best = 0;
        while(st.size() > NEEDED_DIGITS) {
            st.pop();
        }

        while(!st.empty()) {
            best += st.top() * base;

            st.pop();
            base *= 10;
        }

        result += best;
    }

    return result;
}

int main(void) {
    vector<string> banks = readInput();

    long long  result = solve(banks);

    cout << result << '\n';

    return 0;
}
