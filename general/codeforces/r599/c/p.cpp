#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


int main(){
    vector<long long> primes;
    primes.push_back(2);
    // generate primes up to 1000000
    for(long long i = 3; i<=1000000; i++){
        bool prime = true;
        for(long long j = 0; j<primes.size(); j++){
            if(i%primes[j] == 0){
                prime = false;
                j = primes.size(); break;
            }
            if(primes[j] > (long long)sqrt(i)){
                primes.push_back(i);
                j = primes.size();
                break;
            }
        }
    }
    for(long long i = 0; i<primes.size(); i++){
        cout << primes[i] << ", ";
    }
    cout << endl;
    return 0;
}

