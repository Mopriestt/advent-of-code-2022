#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const int N = 26 * 26;

int G[N][N];
int value[N];

inline int id(const char* valve) {
    return (*valve - 'A') * 26 + *(valve + 1) - 'A';
}

void floyd() {
    for (int k = 0; k < N; k ++)
        for (int i = 0 ; i < N; i ++)
            for (int j = 0; j < N; j ++)
                if (G[i][k] + G[k][j] < G[i][j])
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
}

int d[N][N];
int V[N];
vector<int> prev_nodes[18];
int n = 0;

void compress_nodes() {
    for (int i = 0; i < N; i ++)
        for (int j = 0; j < N; j ++)
            d[i][j] = 10000;

    map<int, int> hash;
    n = 0;
    for (int i = 0; i < N; i ++)
        if (value[i] != 0 || i == 0) {
            hash[i] = n ++;
            V[hash[i]] = value[i];
        }
    
    for (int i = 0; i < N; i ++)
        for (int j = 0; j < N; j ++)
            if ((i == 0 || value[i] != 0) && (j == 0 || value[j] != 0) && i != j && G[i][j] <= 30) {
                prev_nodes[hash[j]].push_back(hash[i]);
                d[hash[i]][hash[j]] = G[i][j];
            }
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
            for (int k = 0; k < n; k ++)
                if (d[i][k] + d[k][j] == d[i][j]) {
                    for (int pos = 0; pos < prev_nodes[j].size(); pos ++)
                        if (prev_nodes[j][pos] == i) {
                            swap(prev_nodes[j][pos], prev_nodes[j][prev_nodes[j].size() - 1]);
                            prev_nodes[j].pop_back();
                            break;
                        }
                    break;
                }
}

int f[31][18][1 << 18];
int ans = 0;
void dp() {
    for (int i = 0; i <= 30; i ++)
        for (int j = 0; j < n; j ++)
            for (int k = 0; k < 1 << n; k ++)
                f[i][j][k] = -1e7;
    f[30][0][0] = 0;
    for (int i = 29; i >= 0; i --)
        for (int j = 0; j < n; j ++)
            for (int k = 0; k < 1 << n; k ++) {
                f[i][j][k] = f[i + 1][j][k];
                if ((1 << j) & k) {
                    int before = (1 << j) ^ k;
                    f[i][j][k] = max(f[i][j][k], f[i + 1][j][before] + i * V[j]);
                }
                for (int prev : prev_nodes[j]) {
                    int dist = d[prev][j];
                    if (dist + i > 30) continue;
                    f[i][j][k] = max(f[i][j][k], f[i + dist][prev][k]);
                }
                ans = max(ans, f[i][j][k]);
            }
}

void input() {
    char fmt[] = "Valve %s has flow rate=%d;";
    char valve[4], _[100];
    int rate;
    for (int i = 0; i < N; i ++)
        for (int j = 0; j < N; j ++)
            G[i][j] = 10000;
    while (~scanf(fmt, valve, &rate)) {
        scanf("%s%s%s%s", _, _, _, _);
        int u = id(valve);
        value[u] = rate;
        while (true) {
            scanf("%s", valve);
            G[u][id(valve)] = 1;
            if (valve[2] != ',') break;
        }
        scanf("\n");
    }
}

int main() {
    freopen("16.in", "r", stdin);
    freopen("16.out", "w", stdout);

    input();

    floyd();

    compress_nodes();

    dp();

    cout<<ans<<endl;

    return 0;
}