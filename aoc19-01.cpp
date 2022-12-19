#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int n = 0, scripts[100][5][3], cur_script;
unordered_map<long long, short> f;
unordered_set<long long> inq;
int max_need[4];

void input(string &fmt) {
    memset(scripts, 0, sizeof(scripts));
    int _;
    while (~scanf(
        fmt.c_str(),
        &_,
        &scripts[n][0][0],
        &scripts[n][1][0],
        &scripts[n][2][0],
        &scripts[n][2][1],
        &scripts[n][3][0],
        &scripts[n][3][2]
    )) ++ n;
}

inline long long compress(vector<short> &state) {
    long long p = 1, ret = 0;
    for (int i = 0; i < state.size(); i ++) {
        ret += p * state[i];
        p *= 100;
    }
    return ret;
}

inline long long dist(vector<short> &state) {
    long long s = compress(state);
    if (f.find(s) == f.end()) return -1;
    return f[s];
}

inline void generate(vector<short> &state) {
    state[0] --;
    // Threshold pruning
    state[4] = min(state[1] + state[4], max_need[0] * 2);
    state[5] = min(state[2] + state[5], max_need[1] * 2);
    state[6] = min(state[3] + state[6], max_need[2] * 2);
}

inline void relax(queue<vector<short>> &q, vector<short> &state, short dis) {
    if (dist(state) < dis) {
        long long comp = compress(state);
        f[comp] = dis;
        if (inq.find(comp) == inq.end()) {
            q.push(state);
            inq.insert(comp);
        }
    }
}

// State: {time, robot_1, robot_2, robot_3, resource_1, resource_2, resource3}
short dp(int cs) {
    short ret = 0;
    vector<short> start = {32, 1, 0, 0, 0, 0, 0};
    f[compress(start)] = 0;
    queue<vector<short>> q;
    q.push(start);
    while (!q.empty()) {
        vector<short> u = q.front();
        q.pop();
        short dis = dist(u);
        ret = max(ret, dis);
        if (u[0] * (u[0] - 1) / 2 + dis <= ret) continue;
        if (u[0] == 1) continue;
        // Threshold pruning
        if (u[1] > max_need[0]) continue;
        if (u[2] > max_need[1]) continue;
        if (u[3] > max_need[2]) continue;

        // Do nothing
        auto v = u;
        generate(v);
        relax(q, v, dis);

        // Build one robot
        for (int i = 3; i >= 0; i --) {
            if (i < 3 && u[i + 4] >= (max_need[i] - u[i + 1]) * u[0]) continue; // No need to build more of this type
            if (u[4] >= scripts[cur_script][i][0] && u[5] >= scripts[cur_script][i][1] && u[6] >= scripts[cur_script][i][2]) {
                auto v = u;
                v[4] -= scripts[cur_script][i][0];
                v[5] -= scripts[cur_script][i][1];
                v[6] -= scripts[cur_script][i][2];
                generate(v);
                if (i != 3) v[i + 1] ++;
                relax(q, v, dis + (i == 3 ? v[0] : 0));
            }
        }
    }
    return ret;
}

int main() {
    freopen("19.in", "r", stdin);
    freopen("19.out", "w", stdout);

    string fmt = "Blueprint %d: Each ore robot costs %d ore. ";
    fmt += "Each clay robot costs %d ore. ";
    fmt += "Each obsidian robot costs %d ore and %d clay. ";
    fmt += "Each geode robot costs %d ore and %d obsidian.\n";

    input(fmt);

    int ans = 1;
    for (cur_script = 0; cur_script < 3; cur_script ++) {
        for (int i = 0; i < 3; i ++)
            for (int j = 0; j < 4; j ++)
                max_need[i] = max(max_need[i], scripts[cur_script][j][i]);
        inq.clear();
        f.clear();
        ans *= dp(cur_script);
    }

    cout << ans <<endl;

    return 0;
}
