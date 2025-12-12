#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <queue>
using namespace std;

const string SVR = "svr";
const string START = "you";
const string END = "out";

const string DAC = "dac";
const string FFT = "fft";

map<string, vector<string>> readInput() {
    map<string, vector<string>> adjList;

    string line;
    while(getline(cin, line)) {
        stringstream streamLine(line);

        vector<string> inputMachine;

        string node;
        getline(streamLine, node, ' ');
        node = node.substr(0, (int)node.size() - 1);

        string neighbour;
        while(getline(streamLine, neighbour, ' ')) {
            adjList[node].push_back(neighbour);
        }
    }

    return adjList;
}

vector<string> getTopologicalOrder(map<string, vector<string>>& adjList) {
    map<string, int> indegree;

    for (auto it : adjList) {
        for (string neighbour : it.second) {
            indegree[neighbour]++;
        }
    }

    queue<string> toProcess;
    for (auto it : adjList) {
        if (indegree[it.first] == 0) {
            toProcess.push(it.first);
        }
    }

    vector<string> topologicalOrder;
    while(!toProcess.empty()) {
        string next = toProcess.front();
        toProcess.pop();

        topologicalOrder.push_back(next);

        for (string neighbour : adjList[next]) {
            indegree[neighbour]--;

            if (indegree[neighbour] == 0) {
                toProcess.push(neighbour);
            }
        }
    }

    return topologicalOrder;
}

long long solve(map<string, vector<string>>& adjList, vector<string>& checkpoints) {
    vector<string> topologicalOrder = getTopologicalOrder(adjList);

    vector<string> interestingNodes;
    for (int i = 0; i < (int)topologicalOrder.size(); i++) {
        for (string interestingNode : checkpoints) {
            if (topologicalOrder[i] == interestingNode) {
                interestingNodes.push_back(interestingNode);
                break;
            }
        }
    }

    map<string, long long> ways;
    ways[SVR] = 1;

    int nextInterestIdx = 0;
    for (int i = 0; i < (int)topologicalOrder.size(); i++) {
        string node = topologicalOrder[i];
        if (nextInterestIdx < (int)interestingNodes.size() && node == interestingNodes[nextInterestIdx]) {
            for (auto it : adjList) {
                if (it.first != node) {
                    ways[it.first] = 0;
                }
            }

            nextInterestIdx++;
        }

        for (auto neighbour : adjList[node]) {
            ways[neighbour] += ways[node];
        }
    }

    return ways[END];
}

int main(void) {
    map<string, vector<string>> adjList = readInput();

    vector<string> interestingNodes = {SVR, DAC, FFT, END};
    long long result = solve(adjList, interestingNodes);

    cout << result << '\n';

    return 0;
}
