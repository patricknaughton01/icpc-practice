#include <iostream>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main(){
    unordered_set<int> nums_said;
    int num;
    int max = 0;
    int n;
    cin >> n;
    for(int i = 0; i<n; i++){
        cin >> num;
        nums_said.insert(num);
        if(num > max){
            max = num;
        }
    }
    bool good_job = true;
    for(int i = 1; i<=max; i++){
        if(nums_said.find(i)==nums_said.end()){
            cout << i << endl;
            good_job = false;
        }
    }
    if(good_job){
        cout << "good job" << endl;
    }
    return 0;
}
