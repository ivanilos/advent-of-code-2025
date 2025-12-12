#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

const int TO_JOIN = 1000;

struct Point {
    long long x;
    long long y;
    long long z;
};

struct Edge {
    int a;
    int b;
    long long distSquare;
};

bool operator <(const Edge& a, const Edge& b) {
    return a.distSquare < b.distSquare;
}

struct DSU {
    vector<int> curSet;
    vector<int> sz;

    DSU(int n) {
        curSet.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            sz[i] = 1;
            curSet[i] = i;
        }
    }

    int find(int i) {
        if (curSet[i] == i) {
            return i;
        }
        return curSet[i] = find(curSet[i]);
    }

    int unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) {
            return 0;
        }

        sz[x] += sz[y];
        curSet[y] = curSet[x];

        return 1;
    }
};

vector<Point> readInput() {
    vector<Point> input;

    string line;
    long long x, y, z;
    while(scanf("%lld,%lld,%lld", &x, &y, &z) != EOF) {
        input.push_back(Point{x, y, z});
    }

    return input;
}

long long getDistSquare(Point& a, Point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long dz = a.z - b.z;

    return dx * dx + dy * dy + dz * dz;
}

int solve(vector<Point>& points) {
    vector<Edge> edges;

    for (int i = 0; i < (int)points.size(); i++) {
        for (int j = i + 1; j < (int)points.size(); j++) {
            edges.push_back(Edge{i, j, getDistSquare(points[i], points[j])});
        }
    }

    sort(edges.begin(), edges.end());

    DSU dsu = DSU{(int)points.size()};
    for (int i = 0; i < min(TO_JOIN, (int)edges.size()); i++) {
        dsu.unite(edges[i].a, edges[i].b);
    }

    priority_queue<int> largestThree;
    set<int> connectedIdx;
    for (int i = 0; i < (int)points.size(); i++) {
        int setIdx = dsu.find(i);

        if (!connectedIdx.count(setIdx)) {
            connectedIdx.insert(setIdx);
            largestThree.push(-dsu.sz[setIdx]);

            if (largestThree.size() > 3) {
                largestThree.pop();
            }
        }
    }

    int result = 1;
    while (largestThree.size() > 0) {
        result *= -largestThree.top();
        largestThree.pop();
    }

    return result;
}

int main(void) {
    vector<Point> points = readInput();

    int result = solve(points);

    cout << result << '\n';

    return 0;
}
