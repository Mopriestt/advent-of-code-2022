#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <queue>

using namespace std;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

struct Blizzard {
    int x, y, d;
    Blizzard(int _x, int _y, int _d) : x(_x), y(_y), d(_d) {} 
};

set< pair<int, int> > blz;

vector<Blizzard> a;
vector<string> g;

int n = 0, m, cycle;

pair<int, int> dest;
pair<int, int> final_dest;

void blow() {
    blz.clear();
    for (auto &b : a) {
        int x = b.x + dx[b.d];
        int y = b.y + dy[b.d];
        if (g[x][y] != '#') {
            b.x = x;
            b.y = y;
        } else {
            if (b.d == 0) b.y = m - 2;
            if (b.d == 1) b.x = 1;
            if (b.d == 2) b.y = 1;
            if (b.d == 3) b.x = n - 2;
        }
        blz.insert({b.x, b.y});
    }
}

long long encode(vector<int> &state) {
    return state[2] % cycle + state[1] * 10000LL + state[0] * 100000000LL;
}

int gcd(int a, int b) {
    if (a % b == 0) return b;
    return gcd(b, a % b);
}

int find_path(int target) {
    blz.clear();
    for (auto &b : a) blz.insert({b.x, b.y});
    int step = 0;
    unordered_set<long long> vis;
    queue<vector<int>> q;
    if (target == 0) {
        q.push({0, 1, 0});
        dest = final_dest;
    } else {
        q.push({final_dest.first, final_dest.second, 0});
        dest = {0, 1};
    }

    while (true) {
        auto u = q.front();
        q.pop();
        if (u[0] == dest.first && u[1] == dest.second) return u[2];
        if (u[2] != step) {
            step ++;
            blow();
        }
        if (blz.find({u[0], u[1]}) != blz.end()) continue;
        if (vis.find(encode(u)) != vis.end()) continue;
        vis.insert(encode(u));

        q.push({u[0], u[1], step + 1});
        for (int k = 0; k < 4; k ++) {
            int x = u[0] + dx[k], y = u[1] + dy[k];
            if (x < 0 || x == n || g[x][y] == '#' ) continue;
            q.push({x, y, step + 1});
        }
    }
    throw;
}

int main() {
    freopen("24.in", "r", stdin);
    freopen("24.out", "w", stdout);
    string s;
    while (cin >> s) {
        for (int i = 0; i < s.size(); i ++) {
            if (s[i] == '<') a.push_back(Blizzard(n, i, 0));
            if (s[i] == 'v') a.push_back(Blizzard(n, i, 1));
            if (s[i] == '>') a.push_back(Blizzard(n, i, 2));
            if (s[i] == '^') a.push_back(Blizzard(n, i, 3));
            if (n > 0 && s[i] == '.' && s[i - 1] == '#' && s[i + 1] == '#' )
                final_dest = {n, i};
        }
        g.push_back(s);
        n ++;
    }
    m = g[0].size();
    cycle = (n - 2) * (m - 2) / gcd(n - 2 , m - 2);

    cout<< find_path(0) + find_path(1) + find_path(0) << endl;
    return 0;
}
