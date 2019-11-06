#include "validate.h"

#include <vector>
#include <iostream>

using namespace std;

struct Point
{
    int x, y;
    Point(){}
    Point(int x, int y) : x(x), y(y) {
    }
};

long long det(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}

Point operator - (const Point &a, const Point &b)
{
    return Point(a.x - b.x, a.y - b.y);
}

bool intersect(const Point &b1, const Point &e1,
               const Point &b2, const Point &e2)
{
    return det(e1-b1, b2 - b1) * det(e1-b1, e2 - b1) < 0 &&
           det(e2-b2, b1 - b2) * det(e2-b2, e1 - b2) < 0;
}


vector<Point> points;
string directions;
vector<int> permutation;

void read_input(istream &in) {
    int n;
    in >> n;
    
    points.clear();
    for (int i = 0; i < n; ++ i) {
        int x, y;
        in >> x >> y;
        points.push_back(Point(x, y));
    }
    in >> directions;
}


void read_solution(istream &sol, feedback_function feedback) {
    permutation.clear();
    for (int i = 0; i < points.size(); ++ i) {
        int x;
        if (!(sol >> x) || x < 1 || x > points.size())
            feedback("Not a permutation: at least a number is not in 1..n");
        -- x;
        for (int j = 0; j < i; ++ j)
            if (permutation[j] == x)
                feedback("Not a permutation: duplicated numbers");
        permutation.push_back(x);
    }
}

void check_case() {
    read_input(judge_in);

    read_solution(author_out, wrong_answer);

    for (int i = 2; i + 1 < points.size(); ++ i) {
        Point a = points[permutation[i]];
        Point b = points[permutation[i + 1]];
        for (int j = 0; j < i - 1; ++ j) {
            Point c = points[permutation[j]];
            Point d = points[permutation[j+1]];
            if(intersect(a, b, c, d))
                wrong_answer("Intersection");
        }
    }

    for (int i = 0; i + 2 < points.size(); ++ i) {
        Point a = points[permutation[i]];
        Point b = points[permutation[i + 1]];
        Point c = points[permutation[i + 2]];
        
        int sign = det(b - a, c - a);
        if (directions[i] == 'L') {
            if (sign <= 0)
                wrong_answer("Wrong Answer when 'L'");
        } else {
            if (sign >= 0)
                wrong_answer("Wrong Answer when 'R'");
        }
    }
}


int main(int argc, char **argv) {
    init_io(argc, argv);

    check_case();

    /* Check for trailing output. */
    string trash;
    if (author_out >> trash) {
        wrong_answer("Trailing output");
    }

    cerr << "Correct!" << endl;

    accept();
}
