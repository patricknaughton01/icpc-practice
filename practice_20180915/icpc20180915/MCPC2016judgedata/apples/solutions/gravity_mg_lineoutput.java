// Note that this verison does single System.out.println of composed string for each line

import java.util.Scanner;
import java.util.Arrays;

public class gravity_mg_lineoutput {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int R,C;
	R = in.nextInt();
	C = in.nextInt();

	char[][] grid = new char[R][C];

	for (int r=0; r < R; r++) {
	    String row = in.next();
	    for (int c=0; c < C; c++)
		grid[r][c] = row.charAt(c);
	}

	System.err.println("Done parsing input...");

	for (int c=0; c < C; c++) {
	    int hole = -1;  // invariant is that if hole != -1, then everything from hole to r is EMPTY
	    for (int r=R-1; r >= 0; r--) {
		if (hole == -1 && grid[r][c] == '.')
		    hole = r;
		else if (grid[r][c] == '#')
		    hole = -1;
		else if (hole != -1 && grid[r][c] == 'a') {
		    grid[hole][c] = 'a';
		    grid[r][c] = '.';
		    hole--;
		}
	    }

	}

	System.err.println("Done with simulation...");

	for (int r=0; r < R; r++)
	    System.out.println(grid[r]);

    }

}
