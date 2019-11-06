#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    long long N, D, T;
    cin >> N >> D >> T;
    double rmin, rmax;
    // Total reach of two people i.e. max distance
    // between two people who can reach each other
    long long d = 2*D;
    // Number of times each person clinks with
    // someone
    long long t = (2 * T) / N;
    if(t == N-1){   // We can clinked with everyone else
        rmin = 0;
        if(N%2 == 0){
            // Even number of poeple so someone is dia. opposed
            // to us.
            rmax = D;
        }else{
            // N is odd so get last person above our level
            long long k = (N-1)/2;
            rmax = d/( sqrt(2-2*cos(((2 * M_PI * k) / (double)N))) );
        }
    }else{
        // If we didn't clink with everyone else, we 
        // definitely clinked with an even number of people
        // because of symmetry of the circle, so let k be 
        // half the number of people we clinked with.
        long long k = t/2;
        // Max radius is when we can just reach the kth person
        rmax = d/( sqrt(2-2*cos(((2 * M_PI * k) / (double)N))) );
        // Min radius is when we can just barely reach the k+1 person
        rmin = d/( sqrt(2-2*cos(((2 * M_PI * (k+1)) / (double)N))) );
    }
    cout << rmin << " " << rmax << endl;
    return 0;
}
