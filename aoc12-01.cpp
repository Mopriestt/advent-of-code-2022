#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <queue>

using namespace std;

const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};

int shortestPath(vector<string> &g, pair<int, int> &E) {
    int n = g.size(), m = g[0].size();
    vector<vector<int>> d(n, vector<int>(m, 1e9));
    queue<pair<int, int>> q;

    q.push(E);
    d[E.first][E.second] = 0;

    int res = 1e9;
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        if (g[u.first][u.second] == 'a') res = min(res, d[u.first][u.second]);

        for (int k = 0; k < 4; k ++) {
            int x = dx[k] + u.first;
            int y = dy[k] + u.second;
            if (x < 0 || x >= n || y < 0 || y >= m) continue;
            if (g[u.first][u.second] - g[x][y] < 2 && d[x][y] > d[u.first][u.second] + 1) {
                d[x][y] = d[u.first][u.second] + 1;
                q.push({x, y});
            }
        }
    }

    return res;
}

int main() {
    freopen("12.in", "r", stdin);
    freopen("12.out", "w", stdout);
    vector<string> g;
    string s;
    while (cin >> s) g.push_back(s);
    pair<int, int> S, E;
    for (int i = 0; i < g.size(); i ++) {
        if (g[i].find('S') != string::npos) S = {i, g[i].find('S')};
        if (g[i].find('E') != string::npos) E = {i, g[i].find('E')};
    }
    g[S.first][S.second] = 'a';
    g[E.first][E.second] = 'z';

    cout<<shortestPath(g, E);
    return 0;
}