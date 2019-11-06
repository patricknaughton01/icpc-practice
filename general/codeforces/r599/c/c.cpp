#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <unordered_set>
#include <set>

#define MIN(x, y) ((x)<(y)?(x):(y))

using namespace std;

template<typename T>
void print_vec(const vector<T> &vec){
    for(auto iter = vec.begin(); iter!=vec.end(); iter++){
        cout << *iter << " ";
    }   
    cout << endl;
}

template<typename T>
void print_uset(const unordered_set<T> &uset){
    for(auto iter = uset.begin(); iter!=uset.end(); iter++){
        cout << *iter << " ";
    }   
    cout << endl;
}

int main(){
    long long n;
    cin >> n;
    vector<long long> primes;
    unordered_set<long long> divisors;
    primes.push_back(2);
    for(long long i = 3; i<(long long)sqrt(n) + 1; i++){
        bool prime = true;
        for(long long j = 0; j<primes.size(); j++){
            if(i%primes[j] == 0){
                prime = false;
                j = primes.size();
                break;
            }if(primes[j] > (long long)sqrt(i)){
                j = primes.size();
                break;
            }
        }
        if(prime){
            primes.push_back(i);
        }
    }
    for(long long i = 0; i<primes.size(); i++){
        if(n%primes[i] == 0){
            divisors.insert(primes[i]);
        }
    }
    for(auto iter = divisors.begin(); iter!=divisors.end(); iter++){
        while(n % (*iter) == 0){
            n /= *iter;
        }
    }
    if(n > 1){
        divisors.insert(n);
    }
    //print_uset(divisors);
    //print_vec(primes);
    if(divisors.size() == 1){
        cout << *(divisors.begin()) << endl;
    }else if(divisors.size() == 0){
        // n is prime
        cout << n << endl;
    }else{
        cout << 1 << endl;
    }
    return 0;
}
