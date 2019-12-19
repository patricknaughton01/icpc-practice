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
void print_paired(T s, T e){
    for(auto iter = s; iter != e; iter++){
        cout << "(" << iter->first << "," << iter->second << ") ";
    }
    cout << endl;
}


int main(){
    int t;
    cin >> t;
    for(int i = 0; i<t; i++){
        long long n;
        cin >> n;
        vector<long long> solves;
        for(int j = 0; j<n; j++){
            long long solved;
            cin >> solved;
            solves.push_back(solved);
        }
        if(n >= 6){
            //cout << "solves:";
            //print(solves.begin(), solves.end());
            long long worst_medal_ind = n/2;
            long long worst_medal_solves = solves[worst_medal_ind];
            while(worst_medal_ind >= 0 && solves[worst_medal_ind] == worst_medal_solves){
                worst_medal_ind--;
            }
            if(worst_medal_ind == -1){
                cout << "0 0 0" << endl;
            }else{
                long long off_end = worst_medal_ind + 1;
                map<long long, long long, greater<long long>> counts;
                long long total = off_end;
                for(long long j = 0; j<off_end; j++){
                    if(counts.find(solves[j]) == counts.end()){
                        counts[solves[j]] = 1;
                    }else{
                        counts[solves[j]]++;
                    }
                }
                //cout << "counts:";
                //print_paired(counts.begin(), counts.end());
                if(counts.size() < 3){
                    cout << "0 0 0" << endl;
                }else{
                    long long count_highest_solves = counts.begin()->second;
                    total -= count_highest_solves;
                    counts.erase(counts.begin()->first);
                    long long min_diff = total;
                    long long min_diff_s = 0;
                    long long min_diff_b = total;
                    long long b = total;
                    long long s = 0;
                    for(auto iter = counts.begin(); iter!=counts.end(); iter++){
                        s += iter->second;
                        b -= iter->second;
                        long long diff = ABS(s-b);
                        if(diff < min_diff){
                            min_diff = diff;
                            min_diff_s = s;
                            min_diff_b = b;
                        }
                    }
                    if(MIN(min_diff_s, min_diff_b) > count_highest_solves){
                        cout << count_highest_solves << " " << min_diff_s << " " << min_diff_b << endl;
                    }else{
                        cout << "0 0 0" << endl;
                    }
                }
            }
        }else{
            cout << "0 0 0" << endl;
        }
    }
    return 0;
}
