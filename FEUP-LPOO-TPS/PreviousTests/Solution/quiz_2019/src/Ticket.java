public class Ticket{
    private Concert concert;
    private int number;
    Ticket(int number, Concert concert) throws InvalidTicket {
        if (number < 0) throw new InvalidTicket("invalid ticket");
        this.number = number;
        this.concert = concert;
    }

    public int getNumber() {
        return number;
    }

    public Concert getConcert() {
        return concert;
    }
}
