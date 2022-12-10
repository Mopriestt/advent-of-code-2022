#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

string op, curDir = "";
unordered_map< string, set<string> > dir;
unordered_map< string, unsigned > sz;
unsigned tot = 0, need;


inline void cd() {
    string der;
    cin>>der;
    if (der == "..") {
        curDir.pop_back();
        while (curDir.back() != '/') curDir.pop_back();
    } else {
        if (der == "/") curDir = "/";
        else curDir += der + "/";
    }
}

void der() {
    string der;
    cin>>der;
    der = curDir + der + "/";
    dir[curDir].insert(der);
}

void file() {
    unsigned size = stoi(op);
    string file;
    cin>>file;
    file = curDir + file;
    dir[curDir].insert(file);
    sz[file] = size;
    tot += size;
}

unsigned ans = 1 << 31;

int dfs(string der) {
    unsigned size = 0;
    for (auto obj : dir[der]) {
        if (obj.back() == '/') size += dfs(obj);
        else size += sz[obj];
    }
    sz[der] = size;
    if (size >= need) ans = min(ans, size);
    return size;
}

int main() {
    freopen("07.in", "r", stdin);
    freopen("07.out", "w", stdout);
    while (cin>>op) {
        if (op == "$") {
            cin>>op;
            if (op == "cd") cd();
        } else {
            if (op == "dir") der();
            else file();
        }
    }
    need = 30000000 - (70000000 - tot);
    dfs("/");
    cout<<ans<<endl;
    return 0;
}