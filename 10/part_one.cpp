#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

const int INF = (int)1e9;

struct Machine {
    int lightsMask;
    vector<int> buttons;
    vector<int> joltages;
};

int getLights(vector<string> inputMachine) {
    int lightsMask = 0;

    for (int i = (int)inputMachine[0].size() - 1; i >= 1; i--) {
        lightsMask *= 2;
        if (inputMachine[0][i] == '#') {
            lightsMask++;
        }
    }

    return lightsMask;
}

vector<int> getButtons(vector<string> inputMachine) {
    vector<int> buttons;

    for (int i = 1; i < (int)inputMachine.size() - 1; i++) {
        stringstream buttonSet(inputMachine[i].substr(1, (int)inputMachine[i].size() - 2));

        int curButton = 0;
        string lightToggle;
        while (getline(buttonSet, lightToggle, ',')) {
            int val = atoi(lightToggle.c_str());
            curButton |= 1 << val;
        }
        buttons.push_back(curButton);
    }

    return buttons;
}

vector<int> getJoltages(vector<string> inputMachine) {
    vector<int> joltages;

    int n = (int)inputMachine.size();
    stringstream inputJoltages(inputMachine[n - 1].substr(1, (int)inputMachine[n - 1].size() - 2));

    string joltage;
    while (getline(inputJoltages, joltage, ',')) {
        joltages.push_back(atoi(joltage.c_str()));
    }

    return joltages;
}

vector<Machine> readInput() {
    vector<Machine> input;

    string line;
    while(getline(cin, line)) {
        stringstream streamLine(line);

        vector<string> inputMachine;
        string machinePart;
        while(getline(streamLine, machinePart, ' ')) {
            inputMachine.push_back(machinePart);
        }

        input.push_back(Machine{getLights(inputMachine),
                                getButtons(inputMachine),
                                getJoltages(inputMachine)});
    }

    return input;
}

int solve(vector<Machine>& machines) {
    int result = 0;

    for (Machine machine : machines) {
        int minPresses = INF;

        for (int mask = 0; mask < (1 << machine.buttons.size()); mask++) {
            int curLightsOn = 0;
            int presses = 0;

            for (int i = 0; i < (int)machine.buttons.size(); i++) {
                int bit = (mask >> i) & 1;

                if (bit) {
                    presses++;
                    curLightsOn ^= machine.buttons[i];
                }
            }

            if (curLightsOn == machine.lightsMask) {
                minPresses = min(minPresses, presses);
            }
        }

        result += minPresses;
    }

    return result;
}

int main(void) {
    vector<Machine> machines = readInput();

    int result = solve(machines);

    cout << result << '\n';

    return 0;
}
