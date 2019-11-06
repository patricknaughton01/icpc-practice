#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))
#define ABS(x) ((x)>0?(x):(-(x)))

using namespace std;

long a, b, w, a2, b2, w2;

template <typename T>
void print_vec(vector<T> vec){
    for(auto iter = vec.begin(); iter != vec.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

template <typename T, typename S>
void print_umap(unordered_map<T, S> umap){
    for(auto iter = umap.begin(); iter != umap.end(); iter++){
        cout << iter->first << " -> " << iter->second << endl;
    }
    cout << endl;
}

double deriv(double x){
    double n1 = 2*x*x - 3*x*w + b2 + w2;
    double n2 = 2*x*x + a2 - w*x;
    double d1 = sqrt((w-x)*(w-x) + b2);
    double d2 = sqrt(x*x + a2);
    return (n1/d1) + (n2/d2);
}

double f(double x){
    double t1 = x * sqrt((w-x)*(w-x)+b2);
    double t2 = (x-w) * sqrt(x*x + a2);
    return t1 + t2;
}

double ans(double x){
    return sqrt(x*x + a2) + sqrt((w-x)*(w-x) + b2);
}

int main(){
    int n;
    cin >> n;
    for(int i = 0; i<n; i++){
        long tg, th, r, g, h;
        cin >> w >> tg >> th >> r;
        g = MIN(tg, th);
        h = MAX(tg, th);
        //cout << w << " " << g << " " << h << " " << r << endl;
        a = g - r;
        b = h - r;
        a2 = a*a;
        b2 = b*b;
        w2 = w*w;
        
        double min_dist = sqrt(w*w + (h-g)*(h-g));
        
        double x = w * (double)g/(double)(h+g); // initial guess for newton's method
        //cout << x << endl;
        double last_x = x;
        double diff = 10000;
        while(diff > 1e-10){
            x = last_x - 0.1 * f(last_x)/deriv(last_x);
            diff = ABS(ans(x) - ans(last_x));
            last_x = x;
            //cout << x << endl;
        }
        cout << min_dist << " " << ans(x) << endl;
    }
    return 0;
}
