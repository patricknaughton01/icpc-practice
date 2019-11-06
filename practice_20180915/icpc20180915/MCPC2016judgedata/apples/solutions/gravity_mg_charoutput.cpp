#include <iostream>
using namespace std;

#define MAX_R 50000

string grid[MAX_R];

int main() {
  int R,C;
  cin >> R >> C;
  for (int j=0; j < R; j++)
    cin >> grid[j];

  for (int c=0; c<C; c++) {
    int open = -1;
    for (int r=R-1; r>=0; r--) {
      if (grid[r][c] == '#')
	open = -1;
      else if (open == -1 && grid[r][c] == '.')
	open = r;
      else if (open != -1 && grid[r][c] == 'a') {
	grid[open][c] = 'a';
	grid[r][c] = '.';
	open--;
      }
    }
  }

  for (int j=0; j < R; j++) {
    for (int c=0; c < C; c++)
      cout << grid[j][c];
    cout << endl;
  }
}
