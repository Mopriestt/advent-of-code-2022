#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

struct Elf {
    int x, y, d, pd;
    bool alone;
    Elf(int _x, int _y, int _d) : x(_x), y(_y), d(_d) {}
};

vector<Elf> a;
set< pair<int, int> > pos;

bool alone(Elf &e) {
    for (int k = 0; k < 8; k ++)
        if (pos.find({e.x + dx[k], e.y + dy[k]}) != pos.end())
            return false;
    return true;
}

int next_dir(int dir) {
    if (dir == 1) return 5;
    if (dir == 5) return 7;
    if (dir == 7) return 3;
    if (dir == 3) return 1;
    throw;
}

int dir(Elf &e) {
    int t = e.d;
    for (int k = 0; k < 4; k ++) {
        bool legal = true;
        for (int i = -1; i <= 1; i ++) {
            int d = (t + i) % 8;
            if (pos.find({e.x + dx[d], e.y + dy[d]}) != pos.end())
                legal = false;
        }
        if (legal) return t;
        t = next_dir(t);
    }

    return -1;
}

bool dance() {
    map< pair<int, int>, int> position;

    for (auto &e : a) {
        e.alone = alone(e);
        if (e.alone) continue;

        e.pd = dir(e);
        if (e.pd == -1) continue;

        position[{e.x + dx[e.pd], e.y + dy[e.pd]}] ++;
    }

    bool moved = false;
    for (auto &e : a) {
        e.d = next_dir(e.d);
        if (e.alone || e.pd == -1) continue;

        if (position[{e.x + dx[e.pd], e.y + dy[e.pd]}] == 0) throw;
        if (position[{e.x + dx[e.pd], e.y + dy[e.pd]}] > 1) continue;

        pos.erase({e.x, e.y});
        e.x += dx[e.pd];
        e.y += dy[e.pd];
        pos.insert({e.x, e.y});
        moved = true;
    }
    return moved;
}

int main() {
    freopen("23.in", "r", stdin);
    freopen("23.out", "w", stdout);

    string e;
    int line = 0;
    while (cin >> e) {
        for (int i = 0; i < e.size(); i ++)
            if (e[i] == '#') a.push_back(Elf(line, i, 1)), pos.insert({line, i});
        ++ line;
    }

    for (int i = 1; ; i ++)
        if (!dance()) {
            cout<<i<<endl;
            break;
        }

    return 0;
}
