#include <iostream>
#include <vector>
#include <algorithm>

#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))

using namespace std;

int main(){
    int t;
    cin >> t;
    for(int i = 0;i <t; i++){
        long long r, g, b;
        cin >> r >> g >> b;
        vector<long long> nums;
        nums.push_back(r);
        nums.push_back(g);
        nums.push_back(b);
        sort(nums.begin(), nums.end());
        long long days = nums[0];
        // try to balance how we pair these candies
        if(nums[2] - nums[0] > nums[1]){
            nums[2] -= nums[0];
        }else{
            nums[0] -= nums[2] - nums[1];
            nums[2] = nums[1];
            nums[2] -= nums[0]/2;
            nums[1] -= (nums[0] + 1)/2;
        }
        nums[0] = 0;
        sort(nums.begin(), nums.end());
        days += nums[1];
        cout << days << endl;
    }
    return 0;
}
