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
#define ABS(x) ((x)<0?(-(x)):(x))

using namespace std;

/*long long find_small_dom(const vector<long long> &vec, long long start, long long end){
    if(end-start == 1){
        return -1;
    }
    long long mid = (end-start)/2 + start;
    long long resl = find_small_dom(vec, start, mid);
    long long resr = find_small_dom(vec, mid, end);
    long long min;
    if(resl != -1 && resr != -1){
        min = MIN(resl, resr);
    }else if(resl != -1){
        min
    }
}*/

int main(){
    long long t;
    cin >> t;
    for(long long i = 0; i<t; i++){
        long long n;
        cin >> n;
        vector<long long> nums;
        long long min_space = -1;
        unordered_map<long long, long long> last_seen;
        for(long long j = 0; j<n; j++){
            long long val;
            cin >> val;
            nums.push_back(val);
            if(last_seen.find(val) == last_seen.end()){
                last_seen[val] = j;
            }else{
                long long space = j-last_seen[val];
                last_seen[val] = j;
                if(min_space == -1){
                    min_space = space;
                }else{
                    min_space = MIN(space, min_space);
                }
            }
        }
        /*for(auto iter=counts.begin(); iter!=counts.end(); iter++){
            cout << iter->first << "->" << iter->second << endl;
        }
        cout << endl;*/
        if(nums.size() == 1 || min_space == -1){
            cout << -1 << endl;
        }else{
            cout << min_space + 1 << endl;
        }
    }
    return 0;
}
