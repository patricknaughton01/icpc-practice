#include <iostream>
#include <vector>
#include <algorithm>

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
        vector<int> lens;
        for(int j = 0; j<n; j++){
            int len;
            cin >> len;
            lens.push_back(len);
        }
        sort(lens.begin(), lens.end(), [](int a, int b){return a > b;});
        //print_vec(lens);
        for(int j = 0; j<n; j++){
            if(j+1 > lens[j]){
                cout << j << endl;
                break;
            }else if(j+1 == lens[j]){
                cout << j+1 << endl;
                break;
            }
        }
    }   
    return 0;
}

