#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    vector<int> starts;
    vector<int> ends;
    for(int i = 0; i<n; i++){
        int t;
        cin >> t;
        starts.push_back(t);
        ends.push_back(t+1000);
    }
    int i = 0;
    int j = 0;
    int processing = 0;
    int max_processing = 0;
    while(i < n && j < n){
        if(starts[i] < ends[j]){
            processing++;
            i++;
            if(processing > max_processing){
                max_processing = processing;
            }
        }else{
            processing--;
            j++;
        }
    }
    cout << (max_processing + (k-1))/k << endl;
    return 0;
}
