import java.util.*;
public class TheCalculusOfAda
{
   public static void main(String[] args)
   {
      Scanner scan = new Scanner(System.in);
      String str = scan.nextLine();
      String[] strarry = str.split(" ");
      int n = strarry.length - 1;
      int[][] nums = new int[n][n];
      for(int i=0;i<n;i++) 
         nums[0][i] = Integer.parseInt(strarry[i+1]);
      
      int i;
      for(i=1; i<n; i++)
      {
         boolean same = true;
         for(int k=0;k<n-i;k++) {
            nums[i][k] = nums[i-1][k+1]-nums[i-1][k];
            if (k > 0 && nums[i][k] != nums[i][k-1])
                same = false;
         }
         if (same)
            break;   
      }
      int deg = i, val = 0;
      if (nums[deg][0] == 0) deg = 0; // missed checking initial row
      for(int row=0;row<=deg;row++)
         val += nums[row][n-1-row];
      System.out.println(deg + " " + val);
   }
}
