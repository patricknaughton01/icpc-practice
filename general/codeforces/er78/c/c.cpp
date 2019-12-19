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
        long long n;
        cin >> n;
        vector<long long> left;
        vector<long long> right;
        long long num_red=0, num_blue=0;
        for(long long j = 0; j<n; j++){
            int val;
            cin >> val;
            if(val == 1){
                num_red++;
            }else{
                num_blue++;
            }
            left.push_back(val);
        }
        for(long long j = 0; j<n; j++){
            int val;
            cin >> val;
            if(val == 1){
                num_red++;
            }else{
                num_blue++;
            }
            right.push_back(val);
        }
        long long diff = num_blue - num_red;
        unordered_map<long long, long long> first_occurence;
        vector<long long>left_suf(n+1, 0);
        vector<long long>right_pref(n+1, 0);
        for(long long j = n-1; j>=0; j--){
            if(left[j] == 1){
                left_suf[j] = left_suf[j+1] - 1;
            }else{
                left_suf[j] = left_suf[j+1] + 1;
            }
        }
        for(long long j = 1; j<n+1; j++){
            if(right[j-1] == 1){
                right_pref[j] = right_pref[j-1] - 1;
            }else{
                right_pref[j] = right_pref[j-1] + 1;
            }
            if(first_occurence.find(right_pref[j])==first_occurence.end()){
                first_occurence[right_pref[j]] = j;
            }
        }
        first_occurence[0] = 0;
        /*cout << "Left_suf: " << endl;
        print(left_suf.begin(), left_suf.end());
        cout << "Right_pref: " << endl;
        print(right_pref.begin(), right_pref.end());
        cout << "First occ: " << endl;
        print_d(first_occurence.begin(), first_occurence.end());
        cout << "Diff: " << diff << endl;*/
        long long min_eats = 2*n;
        for(long long j = n; j >= 0; j--){
            long long tmp = (diff - left_suf[j]);
            if(first_occurence.find(tmp) != first_occurence.end()){
                min_eats = MIN(min_eats, n-j+first_occurence[tmp]);
            }
        }
        cout << min_eats << endl;
    }
    return 0;
}
