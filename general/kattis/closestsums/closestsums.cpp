#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <iterator>
#include <utility>

#define ABS(x) ((x)>0?(x):(-(x)))

using namespace std;

template <typename T>
void print_vec(vector<T> vec){
    for(auto iter = vec.begin(); iter != vec.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

template <typename T>
void print_set(set<T> set){
    for(auto iter = set.begin(); iter != set.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

int main(){
    int n, m;
    int case_num = 1;
    while(cin >> n){
        vector<long long> entries;
        for(int i = 0; i<n; i++){
            long long e;
            cin >> e;
            entries.push_back(e);
        }
        cin >> m;
        cout << "Case " << case_num << ":" << endl;
        case_num++;
        for(int i = 0; i<m; i++){
            long long q; 
            cin >> q;
            map<long long, int> diffs;
            for(int j = 0; j<entries.size(); j++){
                diffs.insert(pair<long long, int>(q - entries[j], j));
            }
            long long min_diff;
            long long min_diff_sum;
            for(int j = 0; j<entries.size(); j++){
                auto lower = diffs.lower_bound(entries[j]);
                auto next = prev(lower);
                long long d1;
                long long d2;
                bool d1v = false;
                bool d2v = false;
                if(lower != diffs.end() && lower->second != j){
                    d1 = lower->first - entries[j];
                    d1v = true;
                }
                if(lower != diffs.begin() && next->second != j){
                    // lower isn't the beginning so we can check next
                    d2 = next->first - entries[j];
                    d2v = true;
                }
                long long min_diff_this_entry;
                long long min_diff_sum_this_entry;
                if(d1v && d2v){
                    if(ABS(d1) < ABS(d2)){
                        min_diff_this_entry = ABS(d1);
                        min_diff_sum_this_entry = q - d1;
                    }else{
                        min_diff_this_entry = ABS(d2);
                        min_diff_sum_this_entry = q - d2;
                    }
                }else if(d1v){
                    min_diff_this_entry = ABS(d1);
                    min_diff_sum_this_entry = q - d1;
                }else if(d2v){
                    min_diff_this_entry = ABS(d2);
                    min_diff_sum_this_entry = q - d2;
                }
                //cout << "d1: " << d1 << endl;
                //cout << "d2: " << d2 << endl;
                if(j == 0 || min_diff_this_entry < min_diff){
                    min_diff = min_diff_this_entry;
                    min_diff_sum = min_diff_sum_this_entry;
                }
            }
            cout << "Closest sum to " << q << " is " << min_diff_sum << "." << endl;
        }
        //print_vec(entries);
    }
    
    return 0;
}

