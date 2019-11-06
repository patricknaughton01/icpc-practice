#include <iostream>
#include <vector>

using namespace std;

void print_ans(vector<int> &lens, vector<int> &ends, int n){
    vector<int> output(n, 0);
    int val = lens.size();
    for(int i = ends.size() - 1; i>=0; i--){
        for(int j = 0; j<lens[i]; j++){
            output[ends[i] - j - 1] = val;
        }
        val--;
    }
    for(int i = 0; i<output.size(); i++){
        cout << output[i] << " ";
    }
    cout << endl;
}

bool move_platforms(int n, int d, vector<int> &lens, vector<int> &ends){
    // we start with all platforms at the very beginning and move them
    // out to reach the end
    for(int i = ends.size()-1; i>=0; i--){
        if(ends[i] + d > n){
            // we can just reach the end
            return true;
        }else{
            //cout << "N: " << n << endl;
            // set the farthest platform as far from the current
            // end as possible
            ends[i] = n-d+1;
            // now we have to reach the beginning of this platform
            n = ends[i] - lens[i];
            //cout << "NewN: " << n << endl;
        }
    }
    return (d > n);
}

int main(){
    int n, m, d;
    cin >> n >> m >> d;
    vector<int> platforms;
    vector<int> ends;
    int sum = 0;
    for(int i = 0; i<m; i++){
        int len;
        cin >> len;
        sum += len;
        platforms.push_back(len);
        ends.push_back(sum);
    }
    /*for(int i = 0; i<ends.size(); i++){
        cout << ends[i] << endl;    
    }*/
    bool ans = move_platforms(n, d, platforms, ends);
    /*for(int i = 0; i<ends.size(); i++){
        cout << ends[i] << endl;    
    }*/
    if(ans){
        cout << "YES" << endl;
        print_ans(platforms, ends, n);
    }else{
        cout << "NO" << endl;
    }
    return 0;
}
