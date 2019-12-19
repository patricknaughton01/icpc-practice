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
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    if(c == 0 && d == 0 && a == b+1){
        cout << "YES" << endl;
        for(long long i = 0; i<b; i++){
            cout << "0 1 ";
        }
        cout << "0" << endl;
    }else if(a == 0 && b == 0 && d == c+1){
        cout << "YES" << endl;
        for(long long i = 0; i<c; i++){
            cout << "3 2 ";
        }
        cout << "3" << endl;
    }else{
        if(a > b || d > c){
            cout << "NO" << endl;
        }else{
            bool success = false;
            /*if(a == 0 && d == 0 && ABS(b-c) <= 1){
                success = true;
                cout << "YES" << endl;
                if(b < c){
                    for(long long i = 0; i<b; i++){
                        cout << "2 1 ";
                    }
                    cout << "2" << endl;
                }else if(c < b){
                    for(long long i = 0; i<c; i++){
                        cout << "1 2 ";
                    }
                    cout << "1";
                    cout << endl;
                }else{
                    for(long long i = 0; i<b; i++){
                        cout << "2 1 ";
                    }
                    cout << endl;
                }
            }*/
            if(!success){
                // Case 1: cancel a 1's and d 2's
                long long b_prime = b - a;
                long long c_prime = c - d;
                if(b_prime == c_prime){
                    cout << "YES" << endl;
                    success = true;
                    for(long long i = 0; i<a; i++){
                        cout << "0 1 ";
                    }
                    for(long long i = 0; i<b_prime; i++){
                        cout << "2 1 ";
                    }
                    for(long long i = 0; i<d; i++){
                        cout << "2 3 ";
                    }
                    cout << endl;
                }
            }
            if(!success){
                // Case 2: cancel a+1 1's and d 2's
                long long b_prime = b - (a+1);
                long long c_prime = c - d;
                if(b_prime == c_prime){
                    cout << "YES" << endl;
                    success = true;
                    for(long long i = 0; i<a; i++){
                        cout << "1 0 ";
                    }
                    cout << "1 ";
                    for(long long i = 0; i<b_prime; i++){
                        cout << "2 1 ";
                    }
                    for(long long i = 0; i<d; i++){
                        cout << "2 3 ";
                    }
                    cout << endl;
                }
            }
            if(!success){
                // Case 3: cancel a 1's and d+1 2's
                long long b_prime = b - a;
                long long c_prime = c - (d+1);
                if(b_prime == c_prime){
                    cout << "YES" << endl;
                    success = true;
                    for(long long i = 0; i<a; i++){
                        cout << "0 1 ";
                    }
                    for(long long i = 0; i<b_prime; i++){
                        cout << "2 1 ";
                    }
                    for(long long i = 0; i<d; i++){
                        cout << "2 3 ";
                    }
                    cout << "2";
                    cout << endl;
                }
            }
            if(!success){
                // Case 4: cancel a+1 1's and d+1 2's
                long long b_prime = b - (a+1);
                long long c_prime = c - (d+1);
                if(b_prime == c_prime){
                    cout << "YES" << endl;
                    success = true;
                    for(long long i = 0; i<a; i++){
                        cout << "1 0 ";
                    }
                    cout << "1 ";
                    for(long long i = 0; i<b_prime; i++){
                        cout << "2 1 ";
                    }
                    for(long long i = 0; i<d; i++){
                        cout << "2 3 ";
                    }
                    cout << "2";
                    cout << endl;
                }
            }
            if(!success){
                cout << "NO" << endl;
            }   
        }
    }
    return 0;
}
