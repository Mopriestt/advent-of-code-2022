#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

const unsigned MAX_SIZE = 100000;

string op, curDir = "";
unordered_map< string, set<string> > dir;
unordered_map< string, unsigned > sz;


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
}

unsigned ans = 0;

int dfs(string der) {
    unsigned size = 0;
    for (auto obj : dir[der]) {
        if (obj.back() == '/') size += dfs(obj);
        else size += sz[obj];
    }
    sz[der] = size;
    if (size <= MAX_SIZE) ans += size;
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

    dfs("/");
    cout<<ans<<endl;
    return 0;
}