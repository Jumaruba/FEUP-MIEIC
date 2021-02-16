import java.util.Scanner; 
import java.util.ArrayList; 

//obs: this program is not effective, but the goal is to learn java, not to implement the best solution. 
//So, what we truly want to do is change position in the array, not just print changed positions    
public class ex1175{
    public static void main(String[] argc){
        ArrayList<Integer> array = new ArrayList<Integer>(20); 
        Scanner scanner = new Scanner(System.in); 
        Integer aux; 
        for (int i = 0; i<20; i++){
            array.add(scanner.nextInt()); 
        }
        for (int i = 0; i < 10; i++){
            aux = array.get(i); 
            array.set(i, array.get(19-i));
            array.set(19-i, aux);  

        }
        for (int i = 0; i < 20; i++){
            System.out.printf("N[%d] = %d\n", i, array.get(i)); 
        }
    }
}