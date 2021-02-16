import java.util.Scanner;
import java.util.ArrayList; 


public class ex1174{
    static final int m = 100; 
    public static void main(String[] argv){
        Scanner scanner = new Scanner(System.in); 
        ArrayList<Double> array = new ArrayList<Double>(m); 
        for (int i = 0; i < m; i++){
            array.add(scanner.nextDouble()); 
        }
        for (int i = 0; i < m; i++){
            if (array.get(i) <= 10){
                System.out.printf("A[%d] = %.1f\n", i, array.get(i)); 
            }
        }
        scanner.close(); 
    }
}