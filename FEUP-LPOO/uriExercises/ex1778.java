import java.util.Scanner;
 
public class ex1778{
    public static void main(String[] argc){
        Scanner scanner = new Scanner(System.in); 
        Double d =  scanner.nextDouble(); 

        for (int i = 0; i < 100; i++){
            System.out.printf("N[%d] = %.4f\n", i, d ); 
            d = d/2; 
        }
    }
}