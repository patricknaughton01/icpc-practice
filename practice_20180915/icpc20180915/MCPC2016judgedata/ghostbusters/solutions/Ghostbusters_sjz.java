import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class Ghostbusters_sjz {

	Scanner input;


	public Ghostbusters_sjz(BufferedReader input) {
		this.input = new Scanner(input);
	}

	public static void main(String[] args) throws FileNotFoundException, IOException {
		if (args.length > 0) {
			for (int i = 0; i < args.length; ++i) {
				try (BufferedReader input 
						= new BufferedReader(new FileReader(args[i])))
				{
					new Ghostbusters_sjz(input).solve();
				}
			}
		} else {
			BufferedReader input 
			= new BufferedReader (new InputStreamReader(System.in));
			new Ghostbusters_sjz(input).solve();
		}

	}

	
	
	private class Lamp
	{
		int index;
		int x;
		int y;
		boolean isHorizontal;
		int root;
		boolean visited;

		List<Integer> inEdges;
		List<Integer> outEdges;


		Lamp () {
			index = 0;
			x = 0;
			y = 0;
			isHorizontal = true; 
			root = -1;
			visited = false;
			inEdges = new LinkedList<Integer>();
			outEdges = new LinkedList<Integer>();
		}

		Lamp (int i, int xx, int yy, boolean horizontal)
		{
			index = i;
			x = xx;
			y = yy;
			isHorizontal = horizontal;
			root = -1;
			visited = false;
			inEdges = new LinkedList<Integer>();
			outEdges = new LinkedList<Integer>();
		}

		boolean conflictsWith(Lamp lamp, int range) {
			if (isHorizontal == lamp.isHorizontal)
			{
				if (isHorizontal)
				{
					// Both lamps are horizontal.
					return (y == lamp.y) && (Math.abs(x - lamp.x) <= 2*range);
				}
				else
				{
					// both lamps are vertical
					return (x == lamp.x) && (Math.abs(y - lamp.y) <= 2*range);
				}
			}
			else
			{
				return false;
			}
			
		}

		void implies (Lamp lamp) {
			if (index != lamp.index)
			{
				//System.err.println("" +  index + ' ' + toString() + " implies " + lamp.index + ' ' + lamp);
				outEdges.add(lamp.index);
				lamp.inEdges.add(index);
			}			
		}

		
		public String toString() {
			return "(" + x + ',' + y + ',' 
					+ ((isHorizontal) ? 'H' : 'V') + ')';
		}

		// Kosaaju's algorithm for findinc strongly connected components
		void visit(LinkedList<Integer> L)
		{
			LinkedList<Integer> toBeVisited = new LinkedList<>();
			toBeVisited.add(index);
			while (!toBeVisited.isEmpty()) {
				Lamp lamp = allLamps[toBeVisited.getFirst()];
				toBeVisited.removeFirst();
				if (!lamp.visited) {
					lamp.visited = true;

					//System.err.println("Visited " + lamp.index + ' ' + lamp.toString());
					for (int out: lamp.outEdges) {
						toBeVisited.addFirst(out);
					}
					L.addFirst(lamp.index);
				}			
			}
		}
		
		void assign (int componentRoot) {
			LinkedList<Integer> toBeAssigned = new LinkedList<>();
			toBeAssigned.add(index);
			while (!toBeAssigned.isEmpty()) {
				Lamp lamp = allLamps[toBeAssigned.getFirst()];
				toBeAssigned.removeFirst();
				if (lamp.root < 0)
				{
					//System.err.println("Assigning " + lamp.index + ' ' + lamp.toString() + " to " + componentRoot);
					lamp.root = componentRoot;
					for (int in: lamp.inEdges)
					{
						toBeAssigned.addLast(in);
					}
				}
			}
		}


	};


	int N, L;
	Lamp[] allLamps;


	Lamp alternate (Lamp lamp) {
		if (lamp.index % 2 == 0)
			return allLamps[lamp.index + 1];
		else
			return allLamps[lamp.index - 1];
	}


	void readLamps() {
		for (int i = 0; i < L; ++i) {
			int x = input.nextInt();
			int y = input.nextInt();
			
			allLamps[2*i] = new Lamp(2*i, x, y, false);
			allLamps[2*i+1] = new Lamp(2*i+1, x, y, true);
		}
	}


	void findConflicts(int R)
	{
		for (int ilamp1 = 0; ilamp1 < 2*L; ++ilamp1) {
			Lamp lamp1 = allLamps[ilamp1];
			allLamps[ilamp1] = new Lamp(lamp1.index, lamp1.x, lamp1.y, lamp1.isHorizontal);
		}
		
		for (int ilamp1 = 0; ilamp1 < 2*L; ++ilamp1) {
			Lamp lamp1 = allLamps[ilamp1];

			for (int ilamp2 = ilamp1+1; ilamp2 < 2*L; ++ilamp2) {
				Lamp lamp2 = allLamps[ilamp2];

				if (lamp1.conflictsWith(lamp2, R)) {
					//System.err.println("Conflict between " + lamp1 + " and "  + lamp2);
					Lamp lamp1B = alternate(lamp1);
					Lamp lamp2B = alternate(lamp2);
					// If we choose lamp 1, we must also choose 2b
					//    because 1 and 2 conflict.
					lamp1.implies (lamp2B);
					lamp2.implies (lamp1B);
				}
			}
		}
	}


	void analyze() {
		LinkedList<Integer> visiters = new LinkedList<>();
		for (int ilamp1 = 0; ilamp1 < 2*L; ++ilamp1) {
			Lamp lamp1 = allLamps[ilamp1];
			lamp1.visit(visiters);
		}
		for (int ilamp: visiters) {
			Lamp lamp = allLamps[ilamp];
			//System.err.println("Assigning " + ilamp + ' ' + lamp);
			lamp.assign(ilamp);
		}
	}

	boolean  hasASolution() {
		boolean conflict = false;
		for (int i = 0; (!conflict) && i < L; ++i)
		{
			int lamp1V = 2*i;
			int lamp1H = 2*i+1;
			int root1 = allLamps[lamp1V].root;
			int root2 = allLamps[lamp1H].root;
			//System.err.println("" +  2*i + ':' + root1 + "  " + 2*i+1 + ':' + root2);
			if (root1 == root2)
			{
				// We need a lamp to be simultaneously horizontal and vertical
				conflict = true;
			}
		}
		return !conflict;
	}



	void solve()
	{
		//N = input.nextInt();  // For now, ignored. Later change to assume 0 <= x,y <= 10,000
		N = 10000;
		int R; // = input.nextInt();  // For now, ignored. Later change input 
		L = input.nextInt();
		allLamps = new Lamp[2*L];
		readLamps();
		
		int Rmax = 20000;
		int Rmin = 0;
		
		if (solvable(Rmax)) {
			System.out.println("UNLIMITED");
		} else {
			while (Rmax > Rmin) {
				R = (Rmax + Rmin + 1) / 2;
				if (solvable(R)) {
					Rmin  = R;
				} else {
					Rmax = R-1;
				}
			}
			System.out.println(Rmin);
		}
	}
	
	boolean solvable (int R) {
		findConflicts(R);
		analyze();
		return hasASolution();
	}


}
