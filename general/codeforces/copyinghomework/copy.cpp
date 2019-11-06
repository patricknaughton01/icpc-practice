#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main(){
    int N;
    cin >> N;
    unordered_map<int, int> num_indices;
    for(int i = 0; i<N; i++){
        int val;
        cin >> val;
        num_indices[val] = i;
    }
    vector<int> out_perm(N, 0);
    /*for(auto iter=out_perm.begin(); iter!=out_perm.end(); iter++){
        cout << *iter << endl;
    }*/
    for(int i = 0; i<N; i++){
        out_perm[num_indices[N-i]] = i+1;
    }
    for(auto iter=out_perm.begin(); iter!=out_perm.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
    return 0;
}
