#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int N,K;

int travel(vector<int>& loc, vector<int>& count) {
  int t = 0;
  int excess = 0;
  for (int j=0; j < loc.size(); j++) {
    int bonus = min(excess,count[j]);
    count[j] -= bonus;
    excess -= bonus;
    if (count[j] > 0) {
      int trips = count[j] / K;
      if (count[j] % K > 0) {
	trips++;
	excess += K - count[j]%K;
      }
      t += trips * 2 * abs(loc[j]);
    }
  }
  return t;
}

int main() {
  cin >> N >> K;
  vector<int> left,right;
  vector<int> leftNum,rightNum;
  for (int j=0; j < N; j++) {
    int X,T;
    cin >> X >> T;
    left.push_back(X);
    leftNum.push_back(T);
  }
  while (left.back() > 0) {
    right.push_back(left.back());
    left.pop_back();
    rightNum.push_back(leftNum.back());
    leftNum.pop_back();
  }

  cout << travel(left,leftNum) + travel(right,rightNum) << endl;
}
