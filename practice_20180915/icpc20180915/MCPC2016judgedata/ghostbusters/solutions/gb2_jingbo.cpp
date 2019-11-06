#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1000000;

struct Laser
{
    int id, x, y;

    Laser(int id) : id(id) {
        scanf("%d%d", &x, &y);
    }

    int dist(const Laser& other) const {
        return abs(x - other.x) + abs(y - other.y);
    }
};

inline bool operator < (const Laser &a, const Laser &b)
{
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

vector<Laser> lasers;
unordered_map<int, vector<Laser>> x2id, y2id;

vector<vector<int>> adj;
vector<int> color, low, myStack;
int dfn, nColors;
vector<bool> mark;

void dfs(int u)
{
    mark[u] = true;
    int mini = low[u] = ++ dfn;
    myStack.push_back(u);

    for (int v : adj[u]) {
        if (!mark[v]) {
            dfs(v);
        }
        mini = min(low[v], mini);
    }

    if (low[u] == mini) {
        int v;
        ++ nColors;
        do {
            v = myStack.back();
            myStack.pop_back();
            low[v] = low.size() + 1;
            color[v] = nColors;
        } while (u != v);
    } else {
        low[u] = mini;
    }
}

inline void addEdge(int a, int b)
{
    adj[a].push_back(b);
}

bool check(int power)
{
    adj.clear();
    adj.resize(lasers.size() * 2, vector<int>());

    for (auto& iter : x2id) {
        for (int i = 0, j = 0; i < iter.second.size(); ++ i) {
            const Laser& a = iter.second[i];
            if (j < i) {
                j = i;
            }
            while (j < iter.second.size() && a.dist(iter.second[j]) <= power * 2) {
                ++ j;
            }
            for (int k = i + 1; k < j; ++ k) {
                const Laser& b = iter.second[k];
                addEdge(a.id, b.id + lasers.size());
                addEdge(b.id, a.id + lasers.size());
            }
        }
    }
    for (auto& iter : y2id) {
        for (int i = 0, j = 0; i < iter.second.size(); ++ i) {
            const Laser& a = iter.second[i];
            if (j < i) {
                j = i;
            }
            while (j < iter.second.size() && a.dist(iter.second[j]) <= power * 2) {
                ++ j;
            }
            for (int k = i + 1; k < j; ++ k) {
                const Laser& b = iter.second[k];
                addEdge(b.id + lasers.size(), a.id);
                addEdge(a.id + lasers.size(), b.id);
            }
        }
    }

    mark = vector<bool>(lasers.size() * 2, false);
    color = vector<int>(lasers.size() * 2, 0);
    low = vector<int>(lasers.size() * 2, 0);
    myStack.clear();
    dfn = nColors = 0;
    for (int i = 0; i < 2 * lasers.size(); ++ i) {
        if (!mark[i]) {
            dfs(i);
        }
    }

    for (int i = 0; i < lasers.size(); ++ i) {
        if (color[i] == color[i + lasers.size()]) {
            return false;
        }
    }
    return true;
}

int main()
{
  //    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        lasers.push_back(Laser(i));
        x2id[lasers[i].x].push_back(lasers[i]);
        y2id[lasers[i].y].push_back(lasers[i]);
    }

    for (auto& iter : x2id) {
        sort(iter.second.begin(), iter.second.end());
    }
    for (auto& iter : y2id) {
        sort(iter.second.begin(), iter.second.end());
    }

    int left = 0, right = INF * 2;
    while (left + 1 < right) {
        int mid = left + right >> 1;
        if (check(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    if (left > INF) {
        puts("UNLIMITED");
    } else {
        printf("%d\n", left);
    }

    return 0;
}
