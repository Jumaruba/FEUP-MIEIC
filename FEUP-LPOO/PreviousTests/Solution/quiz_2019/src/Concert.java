import com.sun.org.apache.xpath.internal.operations.Equals;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Concert {
    private String city;
    private String country;
    private String date;
    private ArrayList<Act> acts = new ArrayList<>();
    Concert(String city, String country, String date){
        this.country = country;
        this.date = date;
        this.city = city;
    }

    void addAct(Act act){
        acts.add(act);
    }

    public String getCountry() {
        return country;
    }

    public String getCity() {
        return city;
    }

    public String getDate() {
        return date;
    }

    public List<Act> getActs(){
        return acts;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Concert concert = (Concert) o;
        return Objects.equals(city, concert.city) &&
                Objects.equals(country, concert.country) &&
                Objects.equals(date, concert.date) &&
                Objects.equals(acts, concert.acts);
    }

    @Override
    public int hashCode() {
        return Objects.hash(city, country, date, acts);
    }


    public boolean isValid(Ticket ticket){
        return ticket.getConcert().equals(this);
    }


    public boolean participates(Artist artist) {
        Band b = new Band("default", "default");
        for (Act act: acts){
            if (act.getClass() == b.getClass()){
                Band b1 = (Band)(act);
                if (b1.containsArtist(artist)) return true;
            }
            else if (act.getClass() == artist.getClass()){
                if (act.equals(artist)) return true;
            }
        }
        return false;
    }
}
