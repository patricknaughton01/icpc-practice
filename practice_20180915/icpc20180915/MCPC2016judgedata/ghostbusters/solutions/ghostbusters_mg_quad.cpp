// rather than group by columns and rows, we simply given in and do all pairs for conflicts

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
using namespace std;

#define GRID 1000000
#define MAX_N 10000
#define DEBUG false

int N;
vector<pair<int,int>> points;
vector<bool> relevant;

// will consider verts 0..N-1 to be horizontal and N...2N-1 to be the vertical ones
vector<pair<int,int>> conflicts;

vector<int> out[2*MAX_N];
vector<int> in[2*MAX_N];

int tree[2*MAX_N];

void dfs(const vector<int> adj[], const vector<int>& order, vector<int>& finished) {
    if (DEBUG) cerr << "Call to DFS starting..." << endl;
    for (int j=0; j < 2*N; j++)
        tree[j] = -1;
    int count=-1;
    for (int j=2*N-1; j >= 0; j--) {
        int s = order[j];
        if (tree[s] == -1) {
            // start dfs visit at vertex source s
            count++;
            tree[s] = count;
            stack<int> S;
            S.push(s);
            if (DEBUG) cerr << "Starting tree #" << count << endl;
            if (DEBUG) cerr << "discovered " << s << " (" << points[s%N].first << "," << points[s%N].second << ")" << endl;
            while (!S.empty()) {
                int u = S.top();
                bool foundMore = false;
                for (auto v : adj[u]) {
                    if (tree[v] == -1) {
                        foundMore = true;
                        tree[v] = count;
                        S.push(v);
			if (DEBUG) cerr << "discovered " << v << " (" << points[v%N].first << "," << points[v%N].second << ")" << endl;
			if (DEBUG) cerr << "  coming from " << u << " (" << points[u%N].first << "," << points[u%N].second << ")" << endl;
                    }
                }
                if (!foundMore) {
                    S.pop();
                    finished.push_back(u);
                    if (DEBUG) cerr << "finished " << u << endl;
                }
            }
        }
    }
}

bool feasible(int P) {
    if (DEBUG) cerr << "Testing feasibility for P=" << P << endl;

    // build graph for actual conflicts for this P value
    for (int j=0; j < 2*N; j++) {
        out[j].clear();
        in[j].clear();
    }

    for (auto pair : conflicts) {
        int u(pair.first), v(pair.second);
        auto pu(points[u%N]), pv(points[v%N]);
        if (abs(pu.first-pv.first) <= 2*P && abs(pu.second-pv.second) <= 2*P) {
            // real conflict exists between u and v
            int notV = (v+N)%(2*N);
            int notU = (u+N)%(2*N);
            out[u].push_back(notV);
            in[notV].push_back(u);
            out[v].push_back(notU);
            in[notU].push_back(v);
            if (DEBUG) cerr << "  Conflict identified between " << u << " and " << v << endl;
            if (DEBUG) cerr << "  " << u << " ==> " << notV << endl;
            if (DEBUG) cerr << "  " << v << " ==> " << notU << endl;
        }
    }

    vector<int> initial;
    for (int j=0; j < 2*N; j++)
        initial.push_back(j);
    vector<int> finishA;
    vector<int> finishB;
    dfs(out, initial, finishA);
    dfs(in, finishA, finishB);

    if (DEBUG) cerr << "What happens next?" << endl;
    for (int j=0; j < N; j++) {
        if (tree[j] == tree[N+j]) {
            if (DEBUG) cerr << "Feasibility for P=" << P << " failed due to " << j << endl;
            return false;    // exists some v such that v ==> notV
        }
    }
    if (DEBUG) cerr << "Feasibility for P=" << P << " succeeded" << endl;
    return true;
}



int main() {
    cin >> N;
    points.resize(N);
    relevant.resize(N);
    for (int j=0; j < N; j++) {
        int x,y;
        cin >> x >> y;  
        points[j] = {x,y};
    }

    // preprocess columns and rows to find potential conflicts
    for (int j=0; j < N; j++) {
      for (int k=1+j; k < N; k++) {
	if (points[j].first == points[k].first)  // same column
	  conflicts.push_back({j+N, k+N});
	if (points[j].second == points[k].second)  // same row
	  conflicts.push_back({j, k});
      }
    }

    // start by doubling while feasible
    int P=1;
    while (P < (1+GRID) && feasible(P))
        P *= 2;

    if (P >= 1+GRID)
        cout << "UNLIMITED" << endl;
    else {
        // now go to binary search
        int low(P/2), high(P);   // might be 0 and 1
        while (low != high-1) {
            int mid = (low+high)/2;
            if (feasible(mid)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        cout << low << endl;
    }
}
