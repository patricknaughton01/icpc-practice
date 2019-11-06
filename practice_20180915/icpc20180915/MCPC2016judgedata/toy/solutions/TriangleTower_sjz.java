import java.awt.geom.Point2D;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Scanner;


public class TriangleTower_sjz {

	private BufferedReader input;
	
	private int n;
	private int[] edgeLengths;
	private Point2D.Double[] vertices;
	private LinkedList<Integer> remainingEdges;
	private int edgeSum;
	private double maxHeight;
	
	
	class Line {
		// ax + by + c = 0
		public double a;
		public double b;
		public double c;

		
		public Line() 
		{
			a = b = c = 0.0;
		}

		public Line (Point2D.Double p1, Point2D.Double p2)
		{
			double dx = p2.x - p1.x;
			double dy = p2.y - p1.y;
			a = dy;
			b = -dx;
			c = p1.y * dx - p1.x * dy;
			double r = Math.sqrt(a*a + b*b);
			a /= r;
			b /= r;
			c /= r;
		}

		public String toString()
		{
			return "" + a + "x + " + b + "y + " + c + "= 0";
		}


		double distance (Point2D.Double p)
		{
			return a * p.x + b * p.y + c;
		}
		
		boolean onSameSide(Point2D.Double p1, Point2D.Double p2) {
			return distance(p1) * distance(p2) > 0.0;
		}


	}


	
	
	
	
	

	public TriangleTower_sjz(BufferedReader input) {
		this.input = input;
	}

	public static void main(String[] args) throws FileNotFoundException, IOException {
		if (args.length > 0) {
			for (int i = 0; i < args.length; ++i) {
				try (BufferedReader input 
						= new BufferedReader(new FileReader(args[i])))
				{
					new TriangleTower_sjz(input).solve();
				}
			}
		} else {
			BufferedReader input 
			    = new BufferedReader (new InputStreamReader(System.in));
			new TriangleTower_sjz(input).solve();
		}

	}

	private void solve() {
		Scanner in = new Scanner(input);
		n = in.nextInt();
		edgeLengths = new int[n];
		remainingEdges = new LinkedList<>();
		edgeSum = 0;
		for (int i = 0; i < n; ++i) {
			edgeLengths[i] = in.nextInt();
			remainingEdges.add(i);
			edgeSum += edgeLengths[i]; 
		}
		vertices = new Point2D.Double[n];
		
		maxHeight = 0.0;
		int baseEdge = 0;
		for (int i = 0; i < n; ++i) {
			int base = remainingEdges.removeFirst();
			double mh0 = maxHeight;
			maxHeight = Math.max(maxHeight, usingBase(base));
			if (maxHeight > mh0) {
				baseEdge = edgeLengths[i];
			}
			remainingEdges.addLast(base);
		}
		System.out.format("%.2f%n", maxHeight);
		System.err.println("base length was " + baseEdge);
		in.close();
	}

	// Get the highest tower we can using edge i as the base
	private double usingBase(int i) {
		vertices[0] = new Point2D.Double(0.0,  0.0);
		vertices[1] = new Point2D.Double(edgeLengths[i],  0.0);
		return buildUponEdge(0, 1, edgeLengths[i], 0.0,
				new Point2D.Double(((double)edgeLengths[i]) / 2.0, -1.0));
	}

	// Build the highest tower we can by adding on to the edge
	// between vertices[i] and vertices[j]. j is the highest numbered vertex
	// in the tower so far.
	private double buildUponEdge(int i, int j, int usedEdgesSum, 
			double heightSoFar, Point2D.Double awayFrom) {
		if (remainingEdges.size() == 0) {
			return 0.0;
		}
		if (heightSoFar + (double)(edgeSum - usedEdgesSum) < maxHeight) {
			// Not enough edges left to match the height we have already found
			return 0.0;
		}
		double maxHeight0 = Math.max(0.0,Math.max(vertices[i].y, vertices[j].y));
		int nRemain = remainingEdges.size();
		for (int e1 = 0; e1 < nRemain; ++e1) {
			int edge1 = remainingEdges.removeFirst();
			int edge1Len = edgeLengths[edge1];
			for (int e2 = 0; e2 < nRemain-1; ++e2) {
				int edge2 = remainingEdges.removeFirst();
				int edge2Len = edgeLengths[edge2];
				Point2D.Double[] v = findNewVertex(vertices[i], vertices[j], 
						edgeLengths[edge1], edgeLengths[edge2], awayFrom);
				if (v != null) {
					for (int vi = 0; vi < v.length; ++vi) {
						vertices[j+1] = v[vi];
						maxHeight0 = Math.max(maxHeight0, v[vi].y);
						double h1 = buildUponEdge(i, j+1, usedEdgesSum+edge1Len+edge2Len, 
								maxHeight0, vertices[j]);
						maxHeight0 = Math.max(maxHeight0, h1);
						double h2 = buildUponEdge(j, j+1, usedEdgesSum+edge1Len+edge2Len, 
								maxHeight0, vertices[i]);
						maxHeight0 = Math.max(maxHeight0, h2);
					}
				}
				remainingEdges.addLast(edge2);
			}
			remainingEdges.addLast(edge1);
		}
		return maxHeight0;
	}
	

	// Find the higher of the two points that are at distance 
	// d1 from p1 and d2 from p2.
	// Return null if no such point exists.
	private Point2D.Double[] findNewVertex(Point2D.Double p1, Point2D.Double p2, 
			double d1, double d2, Point2D.Double awayFrom) {
		double d = p1.distance(p2); 
		if (d == 0.0 || d >= (d1+d2) || d1 >= (d + d2) || d2 >= (d + d1))
			return null;
		double a = (d1*d1 - d2*d2 + d*d) / (2.0 * d);
		double hsq = d1*d1 - a*a;
		if (hsq < 0) {
			// Shouldn't happen
			System.err.println("hsq=" + hsq 
					+ "  p1=" + p1 
					+ "  p2=" + p2 
					+ "  d1=" + d1 
					+ "  d2=" + d2 
					);
			return null;
		}
		double h = Math.sqrt(hsq);
		
		// (x0,y0) is point midway between the two solutions.
		double x0 = p1.x + a * (p2.x - p1.x) / d;
		double y0 = p1.y + a * (p2.y - p1.y) / d;
		
		double x1 = x0 + h * (p2.y - p1.y) /d;
		double y1 = y0 - h * (p2.x - p1.x) /d;
		
		double x2 = x0 - h * (p2.y - p1.y) /d;
		double y2 = y0 + h * (p2.x - p1.x) /d;
		
		Point2D.Double[] solution = new Point2D.Double[2];
		solution[0] = new Point2D.Double(x1, y1);
		solution[1] = new Point2D.Double(x2, y2);
		
		return solution;
	}
}