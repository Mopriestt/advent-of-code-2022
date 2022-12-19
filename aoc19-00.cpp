#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

int n = 0, scripts[100][5][3], cur_script;

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

bool buildable(int robot, vector<int> &resources) {
    if (resources[0] < scripts[cur_script][robot][0]) return false;
    if (robot == 2) return resources[1] >= scripts[cur_script][2][1];
    if (robot == 3) return resources[2] >= scripts[cur_script][3][2];
    return true;
}

const int end_time = 24;
int cur_best, max_need[4];

void dfs(int time, vector<int> &robots, vector<int> &resources, int cur) {
    if (time == 0) {
        cur_best = max(cur, cur_best);
        return;
    }
    if (time * (time - 1) / 2 + cur <= cur_best) return;
    bool built = false;
    vector<int> new_robots, new_resources;
    for (int i = 3; i >= 0; i --) {
        if (i < 3 && resources[i] >= (max_need[i] - robots[i]) * time) continue;
        if (buildable(i, resources)) {
            new_robots = robots;
            new_resources = resources;
            if (i != 3) new_robots[i] ++;
            for (int j = 0; j < 3; j ++) new_resources[j] += robots[j] - scripts[cur_script][i][j];
            dfs(time - 1, new_robots, new_resources, cur + (i == 3 ? time - 1 : 0));
            built = true;
        }
    }
    new_resources = resources;
    for (int j = 0; j < 3; j ++) new_resources[j] += robots[j];
    dfs(time - 1, robots, new_resources, cur);
}

int main() {
    freopen("19.in", "r", stdin);
    freopen("19.out", "w", stdout);

    string fmt = "Blueprint %d: Each ore robot costs %d ore. ";
    fmt += "Each clay robot costs %d ore. ";
    fmt += "Each obsidian robot costs %d ore and %d clay. ";
    fmt += "Each geode robot costs %d ore and %d obsidian.\n";

    input(fmt);

    int ans = 0;
    for (cur_script = 0; cur_script < n; cur_script ++) {
        vector<int> robots = {1, 0, 0}, resources = {0, 0, 0};
        cur_best = 0;
        memset(max_need, 0, sizeof(max_need));
        for (int i = 0; i < 4; i ++)
            for (int j = 0; j < 4; j ++)
                max_need[i] = max(max_need[i], scripts[cur_script][j][i]);
        dfs(end_time, robots, resources, 0);
        ans += cur_best * (cur_script + 1);
        cout<<cur_best<<endl;
    }

    cout << ans <<endl;

    return 0;
}
