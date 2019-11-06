#include <iostream>
#include <algorithm>
using namespace std;

int main() {

  pair<int,int> rect[3];

  for (int j=0; j<3; j++) {
    int W,H;
    cin >> W >> H;
    rect[j] = make_pair(max(W,H), min(W,H));
  }
  sort(rect,rect+3);

  int S = rect[2].first;
  int T = S - rect[2].second;

  // need rect 0 and 1 to assembled to size S x T for S > T
  bool valid=false;

  if (rect[0].first == S && rect[1].first == S && rect[0].second+rect[1].second == T)
    valid = true;

  if ((rect[0].first == T || rect[0].second == T) &&
      (rect[1].first == T || rect[1].second == T) &&
      (rect[0].first + rect[0].second + rect[1].first + rect[1].second == T+T+S))
    valid = true;

  cout << (valid ? "YES" : "NO") << endl;

}
