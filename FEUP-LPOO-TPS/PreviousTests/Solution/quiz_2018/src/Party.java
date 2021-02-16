import java.util.ArrayList;

public class Party extends Event{
    private ArrayList<Person> people = new ArrayList<>(100);
    private ArrayList<Event> events = new ArrayList<>(100);
    public Party(String name, String date, String description){
        super(name, date, description);
    }

    public void addPerson(Person person) {
        people.add(person);
    }

    public int getAudienceCount() {
        return people.size();
    }

    public void addEvent(Event e){
        events.add(e);
        for (Person p: e.people){
            this.addPerson(p);
        }
    }
}
