import java.util.ArrayList;
import java.util.List;

public class BoxOffice {
    private static ArrayList<Concert> tickets = new ArrayList<>(100);   //precisa ser mantindo
    private static ArrayList<Integer> number = new ArrayList<>(100);
    public static List<Ticket> buy(Concert concert, int i) throws InvalidTicket {
        ArrayList<Ticket> t = new ArrayList<>(100);
        int index;
        if (!tickets.contains(concert)) {
            tickets.add(concert);
            number.add(0);
        }
        index = tickets.indexOf(concert);
        for (int j = 1; j <= i; j++){
            number.set(index, number.get(index)+1);
            t.add(new Ticket(number.get(index), concert));
        }

        return t;
    }
}
