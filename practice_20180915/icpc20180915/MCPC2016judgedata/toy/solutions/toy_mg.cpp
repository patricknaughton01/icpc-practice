// MCPC 2016, Construction Toy
// Solution by Michael Goldwasser

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define MAX_N 10
#define MAX_L 99
#define EPS 0.0001
#define DEBUG false

struct Point {
    double x,y;
};

struct Segment {
    int len;
    Point a, b;
};

struct Outcome {
    double span;
    double minx;  // only used to test tolerance for judges
};

vector<Segment> tower,bestTower;
int n;
int length[MAX_N];
bool avail[MAX_N];

Outcome best = { 0, 0 };

double computeTolerance() {
    double small = MAX_L * MAX_N;
    for (int j=2; j < tower.size(); j++) {
        small = min(small, tower[j].b.x);
    }
    return small;
}

void extend();


void trySolution() {
    if (DEBUG)
        cerr << string(tower.size(),' ') << "trySolution() called with point " <<
            tower.back().b.x << "," << tower.back().b.y << endl;
    int t = tower.size();
    Point &p(tower[t-1].b);
    if (p.x > best.span) {
        best = Outcome{p.x, computeTolerance()};
        bestTower = vector<Segment>(tower);
    }
    if (p.x > -EPS)
        extend();  // try adding more
}

void tryGeometry(bool orient) {
    if (DEBUG) cerr << string(tower.size(),' ') << "tryGeometry(" << orient << ") called" << endl;
    int t = tower.size();
    Segment &base(tower[t-3]);
    int first = (orient ? t-2 : t-1);
    int second = (orient ? t-1 : t-2);

    if (DEBUG) cerr << string(tower.size(),' ') << "base is " << base.a.x << "," << base.a.y << " " <<
                   base.b.x << "," << base.b.y << " with len " << base.len << endl;

    tower[first].a = base.a;
    tower[second].a = base.b;

    // Circle-Circle intersections http://mathworld.wolfram.com/Circle-CircleIntersection.html
    double d(base.len), R(tower[first].len), r(tower[second].len);
    double major = (d*d - r*r + R*R)/(2*d);
    double minor = 0.5*sqrt((-d+r-R)*(-d-r+R)*(-d+r+R)*(d+r+R))/d;

    if (DEBUG) cerr << string(tower.size(),' ') << "major is " << major << endl;
    if (DEBUG) cerr << string(tower.size(),' ') << "minor is " << minor << endl;

    double dx(base.b.x-base.a.x), dy(base.b.y-base.a.y);

    if (DEBUG) cerr << string(tower.size(),' ') << "delta is " << dx << "," << dy << endl;

    Point p{base.a.x + dx*major/base.len, base.a.y + dy*major/base.len};
    Point q{dy*minor/base.len, -dx*minor/base.len};

    if (DEBUG) cerr << string(tower.size(),' ') << "p is " << p.x << "," << p.y << endl;
    if (DEBUG) cerr << string(tower.size(),' ') << "q is " << q.x << "," << q.y << endl;

    Point u{p.x+q.x, p.y+q.y};
    tower[first].b = tower[second].b = u;
    trySolution();

    Point v{p.x-q.x, p.y-q.y};
    tower[first].b = tower[second].b = v;
    trySolution();
}


void extend() {
    if (DEBUG) {
        if (tower.size() % 2 == 0)
            cerr << string(tower.size(),' ') << "extending tower with length " << tower.back().len << endl;
        else
            cerr << string(tower.size(),' ') << "extend base (" << tower.back().a.x << "," << tower.back().a.y << ") (" << tower.back().b.x << "," << tower.back().b.y << ") with length " << tower.back().len << endl;
    }
    for (int j=0; j < n; j++)
        if (avail[j]) {
            avail[j] = false;
            if (DEBUG) cerr << string(tower.size(),' ') << "pushing new length " << length[j] << endl;
            tower.push_back(Segment{length[j], Point{0,0}, Point{0,0}});

            int t = tower.size();
            if (t % 2 == 0)
                extend();
            else {
                // just placed odd-numbered segment. Let's find triangles
                Segment &a(tower[t-1]), &b(tower[t-2]), &c(tower[t-3]);
                int m=max(a.len,max(b.len,c.len));
                if (a.len+b.len+c.len > 2*m) {
                    tryGeometry(true);
                    if (t > 3) tryGeometry(false);
                }
            }

            tower.pop_back();
            avail[j] = true;
        }
}


int main() {
    cin >> n;
    for (int j=0; j < n; j++) {
        cin >> length[j];
        avail[j] = true;
    }
    for (int j=0; j < n; j++) {
        avail[j] = false;
        tower.push_back(Segment{length[j], {0,0}, {0,double(length[j])}});
        extend();
        tower.pop_back();
        avail[j] = true;
    }

    cerr << "Tolerance was " << best.minx << endl;
    if (best.minx <= EPS) best.span = -best.span;  // make intentional error if tolerance not met

    cerr << "Base length " << bestTower[0].len << endl;
    for (int j=2; j<bestTower.size(); j+=2) {
        cerr << "Lengths " << bestTower[j-1].len << " and " << bestTower[j].len << " lead to point ("
             << bestTower[j].b.x << "," << bestTower[j].b.y << ")" << endl;
    }

    cout << best.span << endl;

}
