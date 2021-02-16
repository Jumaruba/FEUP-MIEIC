public class Attendee extends User {
    boolean hasPaid = false;
    public Attendee(String name) {
        super(name);
    }

    public Attendee(String name, int age) {
        super(name, age);
    }

    public boolean hasPaid(){
        return hasPaid;
    }

    @Override
    public String toString() {
        return "Attendee " + this.name + (this.hasPaid ? " has" : " hasn't") + " paid its registration.";
    }
}
