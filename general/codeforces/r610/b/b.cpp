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
        long long n, p, k;
        cin >> n >> p >> k;
        vector<long long> goods;
        for(long long j = 0; j<n; j++){
            long long a;
            cin >> a;
            if(a <= p){
                goods.push_back(a);
            }
        }
        sort(goods.begin(), goods.end());
        //print(goods.begin(), goods.end());
        if(goods.size() == 0){
            cout << 0 << endl;
        }else{
            vector<long long> dp_count(goods.size()+k, 0);
            vector<long long> dp_money(goods.size()+k, 0);
            dp_money[k-1] = p;
            long long max_goods = 0;
            for(long long j = k; j<dp_count.size(); j++){
                // Don't buy this good
                dp_count[j] = dp_count[j-1];
                dp_money[j] = dp_money[j-1];
                // Buy this good without using the deal
                if(goods[j-k] <= dp_money[j-1]){
                    dp_count[j] = dp_count[j-1] + 1;
                    dp_money[j] = dp_money[j-1] - goods[j-k];
                }
                // Buy this good using the deal
                if(goods[j-k] <= dp_money[j-k] && j >= 2*k-1 && (k+dp_count[j-k] > dp_count[j] || (k+dp_count[j-k] == dp_count[j] && dp_money[j-k] - goods[j-k] > dp_money[j]))){
                    dp_count[j] = k+dp_count[j-k];
                    dp_money[j] = dp_money[j-k] - goods[j-k];
                }
                max_goods = MAX(dp_count[j], max_goods);
            }
            //cout << "Count and money" << endl;
            //print(dp_count.begin(), dp_count.end());
            //print(dp_money.begin(), dp_money.end());
            cout << max_goods << endl;
        }
    }
    return 0;
}
