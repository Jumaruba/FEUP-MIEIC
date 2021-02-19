import java.util.*;

public class SymbolTable {
    public static HashMap<String, Integer> symbols = new HashMap<String, Integer>();
    public static void store(String key, Integer value){
        symbols.put(key, value);
    }
    public static int get_value(String key){
        return symbols.get(key);
    }
}