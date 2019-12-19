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


int main(){
    int r, c;
    cin >> r >> c;
    vector<vector<long long>> mat;
    if(r != 1 && c != 1){
        for(int i = 0; i<r; i++){
            vector<long long> row;
            for(int j = 0; j<c; j++){
                row.push_back((i+1)*(r+j+1));
            }
            mat.push_back(row);
        }
    }else{
        if(r != 1){
            for(int i = 0; i<r; i++){
                vector<long long> row;
                row.push_back(i+2);
                mat.push_back(row);
            }
        }else if(c != 1){
            vector<long long> row;
            for(int i = 0; i<c; i++){
                row.push_back(i+2);
            }
            mat.push_back(row);
        }else{
            vector<long long>row;
            row.push_back(0);
            mat.push_back(row);
        }
    }
    if(mat.size() == 1 && mat[0].size() == 1){
        cout << 0 << endl;
    }else{
        for(int i = 0; i<r; i++){
            for(int j = 0; j<c; j++){
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
