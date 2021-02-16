import java.util.ArrayList;
import java.util.Objects;

public class Event{
    String title;
    String date = "";
    String description = "";
    ArrayList<Person> people = new ArrayList<>(100);
    Event(String title, String s, String description){
        this.title = title;
        this.description = description;
        this.date = s;
    }

    public Event(Event e){
        this.title = e.title;
        this.date = e.date;
        this.description = e.description;
    }

    public Event(String title, String s) {
        this.title = title;
        this.date = s;
    }

    public Event(String title) {
        this.title = title;
    }

    public String getTitle() {
        return title;
    }

    public String getDate() {
        return date;
    }

    public String getDescription() {
        return description;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    @Override
    public String toString() {
        return title + " is a " + description + " and will be held at " + date + ".";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Event event = (Event) o;
        return Objects.equals(title, event.title) &&
                Objects.equals(date, event.date) &&
                Objects.equals(description, event.description);
    }


    public void addPerson(Person person) {
        if (!people.contains(person))
            people.add(person);
        else{
            people.set(people.indexOf(person), person);
        }
    }

    public int getAudienceCount() {
        return people.size();
    }

}
