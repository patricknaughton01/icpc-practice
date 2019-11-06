#include <iostream>
#include <vector>
using namespace std;


vector<int> seq;
vector<int> lasts;

bool done() {
  if (seq.size() == 1) return true;
  bool change = false;
  int orig = seq[0];
  for (int k=1; k < seq.size(); k++)
    if (orig != seq[k]) return false;
  return true;
}

int main() {
  int n,v;
  cin >> n;
  for (int j=0; j < n; j++) {
    cin >> v;
    seq.push_back(v);
  }
  lasts.push_back(seq.back());

  int d=0;
  while (!done()) {
    d++;
    for (int k=0; k < seq.size()-1; k++) {
      seq[k] = (seq[k+1]-seq[k]);
    }
    seq.pop_back();
    lasts.push_back(seq.back());
    for (auto v: seq)
      cerr << ' ' << v;
    cerr << endl;
  }
  
  int total = 0;
  for (auto v : lasts)
    total += v;

  cout << d << " " << total << endl;
}
