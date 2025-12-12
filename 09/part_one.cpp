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
};

vector<Point> readInput() {
    vector<Point> input;

    string line;
    long long x, y;
    while(scanf("%lld,%lld", &x, &y) != EOF) {
        input.push_back(Point{x, y});
    }

    return input;
}

long long getArea(Point& a, Point& b) {
    long long dx = abs(a.x - b.x + 1);
    long long dy = abs(a.y - b.y + 1);

    return dx * dy;
}

long long solve(vector<Point>& points) {
    long long result = 0;

    for (int i = 0; i < (int)points.size(); i++) {
        for (int j = i + 1; j < (int)points.size(); j++) {
            result = max(result, getArea(points[i], points[j]));
        }
    }

    return result;
}

int main(void) {
    vector<Point> points = readInput();

    long long result = solve(points);

    cout << result << '\n';

    return 0;
}
