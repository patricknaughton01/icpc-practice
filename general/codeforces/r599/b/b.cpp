#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

template<typename T>
void print_vec(const vector<T> &vec){
    for(auto iter = vec.begin(); iter!=vec.end(); iter++){
        cout << *iter << " ";
    }   
    cout << endl;
}

int main(){
    int k;
    cin >> k;
    for(int i = 0; i<k; i++){
        int n;
        cin >> n;
        string s, t;
        cin >> s >> t;
        //cout << s << endl << t << endl;
        vector<int> diff_inds;
        bool success = true;
        for(int j = 0; j<n; j++){
            if(s[j] != t[j]){
                diff_inds.push_back(j);
                if(diff_inds.size() > 2){
                    j = n;
                    success = false;
                    break;
                }
            }
        }
        if(!success || diff_inds.size() == 1){
            // only found one or more than two diffs
            cout << "No" << endl;
        }else{
            // found exactly two diffs
            if((s[diff_inds[0]] == s[diff_inds[1]]) 
                && (t[diff_inds[0]] == t[diff_inds[1]])){
                cout << "Yes" << endl;
            }else{
                cout << "No" << endl;
            }
        }
    }
    return 0;
}

