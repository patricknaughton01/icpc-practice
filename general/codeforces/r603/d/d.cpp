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
    long long n;
    cin >> n;
    unordered_map<char, char> reps;
    for(long long i = 0; i<n; i++){
        string c;
        cin >> c;
        for(int i = 0; i<c.size(); i++){
            if(reps.find(c[i]) == reps.end()){
                reps[c[i]] = c[i];
            }
        }
        for(int i = 0; i<c.size(); i++){
            reps[c[i]] = c[0];
        }
    }
    unordered_set<char> diff_reps;
    for(auto iter = reps.begin(); iter != reps.end(); iter++){
        diff_reps.insert(iter->second);
    }
    cout << diff_reps.size() << endl;
    return 0;
}
