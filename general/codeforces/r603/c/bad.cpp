#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>

#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))

using namespace std;

int main(){
    int t;
    cin >> t;
    for(int i = 0; i<t; i++){
        long long n;
        cin >> n;
        long long div = 1;
        set<long long> ranks;
        while(div <= n){
            long long this_r = n/div;
            ranks.insert(this_r);
            div++;
        }
        ranks.insert(0);
        cout << ranks.size() << endl;
        /*for(long long j = 0; j<ranks.size(); j++){
            cout << ranks[j] << " ";
        }*/
        for(auto iter = ranks.begin(); iter != ranks.end(); iter++){
            cout << *iter << " ";
        }
        cout << endl;
    }
    return 0;
}
