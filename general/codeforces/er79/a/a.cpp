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

template <class T>
void print_d(T s, T e){
    for(auto iter = s; iter != e; iter++){
        cout << "(" << iter->first << "->" << iter->second << ") ";
    }
    cout << endl;
}

int main(){
    long long t;
    cin >> t;
    for(long long i = 0; i<t; i++){
        long long r, g, b;
        cin >> r >> g >> b;
        vector<long long> vals;
        vals.push_back(r);
        vals.push_back(g);
        vals.push_back(b);
        sort(vals.begin(), vals.end());
        //print(vals.begin(), vals.end());
        if(vals[0] + vals[1] + 1 >= vals[2]){
            cout << "Yes" << endl;
        }else{
            cout << "No" << endl;
        }
    }
    return 0;
}
