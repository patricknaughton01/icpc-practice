#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))
#define ABS(x) ((x)>0?(x):(-(x)))

using namespace std;

template <class T>
void print(T s, T e){
    for(auto iter = s; iter != e; iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

template<class T>
void print_g(unordered_map<T, unordered_map<T, T>> g){
    for(auto vert_iter = g.begin(); vert_iter!=g.end(); vert_iter++){
        cout << vert_iter->first << ": {";
        for(auto n_iter = vert_iter->second.begin(); n_iter!=vert_iter->second.end(); n_iter++){
            cout << "(" << n_iter->first << "," << n_iter->second << "), ";
        }
        cout << "}" << endl;
    }
}

template <class T>
vector<T> threechain(const unordered_map<T, unordered_map<T, T>> &g, T start){
    vector<T> stack;
    stack.push_back(start);
    unordered_set<T> visited;
    visited.insert(start);
    while(stack.size() > 0 && stack.size() < 3){
        bool has_unvisited_neighbors = false;
        for(auto iter = g.at(stack[stack.size()-1]).begin(); iter!=g.at(stack[stack.size()-1]).end(); iter++){
            if(visited.find(iter->first) == visited.end() && iter->second != 0){
                // haven't visited this node yet, explore it
                visited.insert(iter->first);
                stack.push_back(iter->first);
                has_unvisited_neighbors = true;
                break;
            }
        }
        if(!has_unvisited_neighbors){
            stack.pop_back();
        }
    }
    return stack;
}

template <class T>
T twocycle(const unordered_map<T, unordered_map<T, T>> &g, T start){
    for(auto iter = g.at(start).begin(); iter!=g.at(start).end(); iter++){
        if(g.at(iter->first).find(start) != g.at(iter->first).end()
            && g.at(iter->first).at(start) != 0 && g.at(start).at(iter->first) != 0){
            return iter->first;
        }
    }
    return -1;
}

int main(){
    // u->{v1->d1, v2->d2, ...}
    unordered_map<long long, unordered_map<long long, long long>>g;
    long long n, m;
    cin >> n >> m;
    // initialize everyone with an empty list of neighbors
    for(long long i = 0; i<n; i++){
        unordered_map<long long, long long> neighbors;
        g[i+1] = neighbors;
    }
    for(long long i = 0; i<m; i++){
        long long u, v, d;
        cin >> u >> v >> d;
        if(g[u].find(v) == g[u].end()){
            g[u][v] = d;
        }else{
            g[u][v] += d;
        }
    }
    //print_g(g);
    for(auto vert_iter = g.begin(); vert_iter != g.end(); vert_iter++){
        vector<long long> stack = threechain(g, vert_iter->first);
        while(stack.size() > 0){
            long long z = MIN(g[vert_iter->first][stack[1]], g[stack[1]][stack[2]]);
            g[stack[0]][stack[1]] -= z;
            g[stack[1]][stack[2]] -= z;
            if(g[stack[0]].find(stack[2]) != g[stack[0]].end()){
                g[stack[0]][stack[2]] += z;
            }else{
                g[stack[0]][stack[2]] = z;
            }
            // Get rid of 0 edges
            if(g[stack[0]][stack[1]] == 0){
                g[stack[0]].erase(stack[1]);
            }
            if(g[stack[1]][stack[2]] == 0){
                g[stack[1]].erase(stack[2]);
            }
            stack = threechain(g, vert_iter->first);
        }
        //print_g(g);
        long long cycle = twocycle(g, vert_iter->first);
        while(cycle != -1){
            //cout << cycle << endl;
            if(g[vert_iter->first][cycle] > g[cycle][vert_iter->first]){
                g[vert_iter->first][cycle] -= g[cycle][vert_iter->first];
                //g[cycle][vert_iter->first] = 0;
                g[cycle].erase(vert_iter->first);
            }else{
                g[cycle][vert_iter->first] -= g[vert_iter->first][cycle];
                //g[vert_iter->first][cycle] = 0;
                g[vert_iter->first].erase(cycle);
            }
            //print_g(g);
            cycle = twocycle(g, vert_iter->first);
        }
    }
    //print_g(g);
    long long total_edges = 0;
    vector<vector<long long>> edges;
    for(auto vert_iter = g.begin(); vert_iter != g.end(); vert_iter++){
        for(auto iter = g[vert_iter->first].begin(); iter != g[vert_iter->first].end(); iter++){
            if(iter->second != 0){
                total_edges++;
                vector<long long> edge;
                edge.push_back(vert_iter->first);
                edge.push_back(iter->first);
                edge.push_back(iter->second);
                edges.push_back(edge);
            }
        }
    }
    cout << total_edges << endl;
    for(auto iter = edges.begin(); iter != edges.end(); iter++){
        cout << (*iter)[0] << " " << (*iter)[1] << " " << (*iter)[2] << endl;
    }
    return 0;
}
