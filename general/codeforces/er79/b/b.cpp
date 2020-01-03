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
        long long n, s;
        cin >> n >> s;
        vector<long long>a;
        for(long long j = 0; j<n; j++){
            long long val;
            cin >> val;
            a.push_back(val);
        }
        long long max = 0;
        long long max_ind = 0;
        long long j = 0;
        long long time = 0;
        while(j < a.size() && time < s){
            time += a[j];
            if(a[j] > max){
                max = a[j];
                max_ind = j;
            }
            j++;
        }
        if(time > s){
            j--;
            time -= a[j];
        }
        if(j == a.size() || j == a.size()-1){
            cout << 0 << endl;
        }else{
            if(max > a[j] || max_ind == j){
                cout << max_ind + 1 << endl;
            }else{
                cout << 0 << endl;
            }
        }
    }
    return 0;
}
