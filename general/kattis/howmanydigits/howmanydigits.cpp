#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main(){
    vector<int> digits;
    vector<double> raw_logs;
    digits.push_back(1);
    digits.push_back(1);
    raw_logs.push_back(0);
    raw_logs.push_back(0);
    int num;
    while(cin>>num){
        if(num < digits.size()){
            cout << digits[num] << endl;
        }else{
            for(int i = raw_logs.size()-1; i<=num; i++){
                raw_logs.push_back(log10(i+1)+raw_logs[i]);
                digits.push_back((int)(raw_logs[raw_logs.size()-1]+1.0));
            }
            cout << digits[num] << endl;
        }
    }
}
