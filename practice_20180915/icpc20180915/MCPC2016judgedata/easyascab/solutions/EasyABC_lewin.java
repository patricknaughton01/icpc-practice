import java.io.*;
import java.util.*;

// http://codeforces.com/contest/512/problem/A
public class EasyABC_lewin {
  private static InputReader in;
  private static PrintWriter out;

  public static void main(String[] args) throws IOException {
    in = new InputReader(System.in);
    out = new PrintWriter(System.out, true);
    int mx = in.next().charAt(0)-'a'+1;
    int N = in.nextInt();
    char[][] s = new char[N][];
    int[][] graph = new int[mx][mx];
    int[] indeg = new int[mx];
    boolean[][] conn = new boolean[mx][mx];
    for (int i = 0; i < N; i++)
      s[i] = in.next().toCharArray();
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        int k = 0;
        for (; k < Math.min(s[i].length, s[j].length); k++) {
          if (s[i][k] != s[j][k]) {
            conn[s[i][k]-'a'][s[j][k]-'a'] = true;
            graph[s[i][k]-'a'][s[j][k]-'a']++;
            indeg[s[j][k]-'a']++;
            break;
          }
        }
        if (k == Math.min(s[i].length, s[j].length) && s[i].length > s[j].length) {
          out.println("IMPOSSIBLE");
          out.close();
          System.exit(0);
        }
      }
    }
    
    int[] queue = new int[mx];
    int front = 0, back = 0;
    for (int i = 0; i < mx; i++)
      if (indeg[i] == 0)
        queue[back++] = i;
    while (front < back) {
      int n = queue[front++];
      for (int i = 0; i < mx; i++) {
        if (graph[n][i] > 0) {
          indeg[i] -= graph[n][i];
          graph[n][i] = 0;
          if (indeg[i] == 0) {
            queue[back++] = i;
          }
        }
      }
    }
    if (front != mx) {out.println("IMPOSSIBLE");}
    else {
      boolean unique = true;
      for (int i = 1; i < mx; i++) {
        if (!conn[queue[i-1]][queue[i]]) {
          unique = false;
          break;
        }
      }
      if (unique) {
        for (int i = 0; i < mx; i++)
          out.print((char)(queue[i]+'a'));
        out.println();
      } else {
        out.println("AMBIGUOUS");
      }
    }
    out.close();
    System.exit(0);
  }

  static class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
      reader = new BufferedReader(new InputStreamReader(stream), 32768);
      tokenizer = null;
    }

    public String next() {
      while (tokenizer == null || !tokenizer.hasMoreTokens()) {
        try {
          tokenizer = new StringTokenizer(reader.readLine());
        } catch (IOException e) {
          throw new RuntimeException(e);
        }
      }
      return tokenizer.nextToken();
    }

    public int nextInt() {
      return Integer.parseInt(next());
    }
  }


}
