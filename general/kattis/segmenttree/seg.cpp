#include <iostream>
#include <vector>

using namespace std;

void build(vector<int> &tree, vector<int> &a);
int build(vector<int> &tree, vector<int> &a, int v, int l, int r);
int query(vector<int> &tree, vector<int> &a, int l, int r);
int query(vector<int> &tree, int v, int tl, int tr, int l, int r);
void add(vector<int> &tree, vector<int> &a, int ind, int val);
void add(vector<int> &tree, int v, int tl, int tr, int ind, int val);
int soln(vector<int> &a, int start, int end);
template<typename T>
void print_vec(vector<T> vec);

void build(vector<int> &tree, vector<int> &a){
    for(int i = 0, n = 4*a.size(); i < n; i++){
        tree.push_back(0);
    }
    build(tree, a, 1, 0, a.size());
}

int build(vector<int> &tree, vector<int> &a, int v, int l, int r){
    //cout << "l = " << l << " r = " << r << " v = " << v << endl;
    //print_vec(tree);
    if(v <= tree.size()){
        if(r - l == 1){
            tree[v] = a[l];
            return tree[v];
        }else{
            int mid = (l + r)/2;
            int l_sum = build(tree, a, 2*v, l, mid);
            int r_sum = build(tree, a, 2*v + 1, mid, r);
            tree[v] = l_sum + r_sum;
            return tree[v];
        }
    }
    return 0;
}

template<typename T>
void print_vec(vector<T> vec){
    for(auto iter = vec.begin(); iter != vec.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

int query(vector<int> &tree, vector<int> &a, int l, int r){
    return query(tree, 1, 0, a.size(), l, r);
}

int query(vector<int> &tree, int v, int tl, int tr, int l, int r){
    //cout << tl << " " << tr << " " << l << " " << r << " " << endl;
    if(l == r){     // Empty subinterval
        return 0;
    }else if(l == tl && r == tr){   // This node is exactly the interval we want
        return tree[v];
    }
    int mid = (tl + tr)/2;
    if(l == tl && r >= mid){    // Add full left interval and part of right
        return tree[2*v] + query(tree, 2*v + 1, mid, tr, mid, r);
    }
    else if(r <= mid){          // Desired interval is in left subtree
        return query(tree, 2*v, tl, mid, l, r);
    }
    else if(r == tr && l <= mid){   // Add full right interval and part of left
        return tree[2*v + 1] + query(tree, 2*v, tl, mid, l, mid);
    }
    else if(l >= mid){              // Desired interval is in right subtree
        return query(tree, 2*v+1, mid, tr, l, r);
    }
    else if(l <= mid && r >= mid){  // Desired interval spans left and right subtrees
        return query(tree, 2*v, tl, mid, l, mid) + query(tree, 2*v+1, mid, tr, mid, r);
    }
    return 0;
}

void add(vector<int> &tree, vector<int> &a, int ind, int val){
    add(tree, 1, 0, a.size(), ind, val);
}

void add(vector<int> &tree, int v, int tl, int tr, int ind, int val){
    int mid = (tl + tr)/2;
    tree[v] += val;
    if(v < tree.size()){
        if(ind < mid){  // Intervals to add to are in left subtree
            add(tree, 2*v, tl, mid, ind, val);
        }else{          // Intervals to add to are in right subtree
            add(tree, 2*v + 1, mid, tr, ind, val);
        }
    }
}

int soln(vector<int> &a, int start, int end){
    int sum = 0;
    for(int i = start; i<end && i<a.size(); i++){
        sum += a[i];
    }
    return sum;
}

int main(){
    vector<int> test;
    test.push_back(1);
    test.push_back(-7);
    test.push_back(3);
    test.push_back(4);
    test.push_back(2);
    test.push_back(10);
    test.push_back(9);
    test.push_back(11);
    test.push_back(15);
    /*vector<int> test;
    test.push_back(1);
    test.push_back(3);
    test.push_back(5);
    test.push_back(7);
    test.push_back(9);
    test.push_back(11);*/
    vector<int> tree;
    build(tree, test);
    print_vec(test);
    print_vec(tree);
    int test_cases = 11;
    int indices[test_cases][2] = {
        {0, 9},
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5},
        {5, 6},
        {1, 9},
        {0, 8},
        {4, 6},
        {3, 6},
        {2, 5},
    };
    for(int i = 0; i<test_cases; i++){
        int idx1 = indices[i][0];
        int idx2 = indices[i][1];
        cout << idx1 << "-" << idx2 << " Expected: " 
            << soln(test, idx1, idx2) << " Res: " 
            << query(tree, test, idx1, idx2) << endl;
    }
    add(tree, test, 0, 10);
    test[0] += 10;
    print_vec(test);
    print_vec(tree);
    for(int i = 0; i<test_cases; i++){
        int idx1 = indices[i][0];
        int idx2 = indices[i][1];
        cout << idx1 << "-" << idx2 << " Expected: " 
            << soln(test, idx1, idx2) << " Res: " 
            << query(tree, test, idx1, idx2) << endl;
    }
    return 0;
}
