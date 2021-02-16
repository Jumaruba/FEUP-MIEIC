import java.util.Objects;

public class Artist  extends Act{
    Artist(String name, String country) {
        super(name, country);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Artist artist = (Artist) o;
        return Objects.equals(name, artist.name) &&
                Objects.equals(country, artist.country);
    }
}
