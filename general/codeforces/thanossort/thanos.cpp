#include <iostream>
#include <vector>

#define MAX(x, y) ((x)>(y)?(x):(y))

using namespace std;

bool isSorted(vector<int> vec);
int thanossort(vector<int> &vec);

int main(){
    int n;
    cin >> n;
    vector<int> nums;
    for(int i = 0; i<n; i++){
        int k;
        cin >> k;
        nums.push_back(k);
    }
    cout << thanossort(nums) << endl;
    return 0;
}

int thanossort(vector<int> &vec){
    if(vec.size() == 0){
        return 0;
    }
    if(isSorted(vec)){
        return vec.size();
    }else{
        vector<int> v1;
        vector<int> v2;
        int mid = vec.size()/2;
        for(int i = 0; i<vec.size(); i++){
            if(i < mid){
                v1.push_back(vec[i]);
            }else{
                v2.push_back(vec[i]);
            }
        }
        return MAX(thanossort(v1), thanossort(v2));
    }
}

bool isSorted(vector<int> vec){
    for(int i = 0; i<vec.size() - 1; i++){
        if(vec[i] > vec[i+1]){
            return false;
        }
    }
    return true;
}

