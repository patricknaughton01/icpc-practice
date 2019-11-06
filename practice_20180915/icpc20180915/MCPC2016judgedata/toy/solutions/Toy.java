/*  ACM Mid-Central Programming competition 2016 Problem ?: Building Toy
    solution by Andy Harrington
    recursive try of all permutations of lengths and ways to add on
*/

import java.util.*;
import java.io.*;
import static java.lang.Math.*;

public class Toy {
  static int n, maxSides;  // n segments to choose, odd maxSides maybe 1 less
  static int[] len; //edge lengths
  static double[] x0, y0, x1, y1; // endpt coord
  static double maxDist,   //distance to maximize
                eps = -1E-3;  // roundoff check neg to start; 
                              // bad data choice if answer different with + 
  public static void main(String[] args) throws Exception {   
    if (args.length > 0) DEBUG = Integer.parseInt(args[0]); //debug
    BufferedReader reader = 
                       new BufferedReader(new InputStreamReader(System.in));
    String line = reader.readLine();
    dprln(line, 1); // debug - record input
    Scanner in = new Scanner(line);
    n = in.nextInt();
    len = new int[n];
    for (int i = 0; i < n; i++) 
      len[i] = in.nextInt();
    x0 = new double[n];
    y0 = new double[n];
    x1 = new double[n];
    y1 = new double[n];
    maxDist = 0;
    maxSides = n - (n+1)%2; // always odd
    System.out.println(mix(0));
    if(DEBUG == 1) System.err.println(bestData); //used by Python image script
  }

  static void swap(int[] perm, int i, int j)
  {
    int temp = perm[i];
    perm[i] = perm[j];
    perm[j] = temp;
  }

  // work on all permutations of len with indices >= iPerm
  // return current maxDist
  static double mix(int iPerm) 
  {
    if (iPerm == maxSides) {   
      debugData(iPerm);  // debug
      return maxDist;
    }
    for (int j = iPerm; j < n; j++) {
      swap(len, iPerm, j);
      if (iPerm%2 == 1)
        mix(iPerm+1);  //need two new lengths in general
      else if (iPerm == 0 ) { // easy special build for base
        x1[0] = len[0]; // only nonzero coord for base seg
        mix(1);
      }
      else {  // iPerm is index for second new edge
        build(iPerm-1, iPerm-2); 
        if (iPerm > 3)  // use symmetry at iPerm = 2
          build(iPerm-1, iPerm-3);
      }
      swap(len, iPerm, j);  //undo - ends with same permutation as at start
    }
    return maxDist;
  }

  // build on edge with index e, up and down 
  //    creating edges with index i, i+1, 
  //    using len permutation set through i+1,
  //    and continue recursively
  static void build(int i, int e)
  {
    double D = len[e]; //  if endpts (0,0), (D,0): get new vert (E, F) ...
    double r1 = len[i], r2 = len[i+1];
    double dx = x1[e] - x0[e], dy = y1[e] - y0[e]; 
    double E = (r1*r1 - r2*r2 + D*D)/(2*D);  // solving quadratic equ ...
    double inRadical = r1*r1 - E*E;
    if (inRadical <= 0) {  // no triangle possible
      debugData(i);
      return;
    }
    double F = sqrt(inRadical); 
    // Now rotate (E, F) and (E, -F) vector and translate to actual vertex:
    for (int k = 0; k < 2; k++) {  // for +F, -F
      y1[i] = y0[i+1] = y0[e] + (F*dx + E*dy)/D;
      if (y1[i] <= eps) 
        debugData(i);  // debug
      else {
        if (y1[i] > maxDist) 
          maxDist = y1[i];
        x1[i] = x0[i+1] = x0[e] + (E*dx - F*dy)/D;
        y0[i] = y0[e]; x0[i] = x0[e];      // just copy matching 
        x1[i+1] = x1[e]; y1[i+1] = y1[e];  //   endpoint vertices
        mix(i+2); // perm at i, i+1 already set
      }
      F = -F; // for other root
    }
  }

  // DEBUG display from here on ////////////////////////////////////////
  static int DEBUG = 0;  // level of debug info shown 0: none; 3: most
  static double debugMaxDist = 0;  // slower calc, skipped in no-debug version
  static String bestData = "";

  // show  base length and then three vert in two new side and 2 lengths...
  static String segSeq(int nV)
  {
    String s = "" + len[0];
    for (int i = 1; i < nV; i += 2)
      s += "\n     " + x0[i] + " " + y0[i] + " " + x1[i] + " " + y1[i] + 
           " " + x1[i+1] + " " + y1[i+1];
    return s;
  }

  // When tower version is complete with nV edges
  // separate maxDist calc, so only display increasing seq
  static void debugData(int nV)
  {
    if (DEBUG == 0) return;
    double thisTop = 0, thisMin = 200;
    for (int i = 1; i < nV; i += 2) {
      thisTop = max(thisTop, y1[i]);
    }
    if (thisTop > debugMaxDist) {
      debugMaxDist = thisTop;
      bestData = "Max: " + thisTop + " " + segSeq(nV);
      dprln(bestData, 2);
    }
  }

  static void dprln(String s, int d) { // debug print with newline
    if (DEBUG >= d) System.err.println(s);
  }
}
