import java.util.ArrayList;

public class Band extends Act{
    ArrayList<Artist> artists = new ArrayList<>();
    Band(String name, String country){
        super(name, country);
    }

    public void addArtist(Artist artist){
        artists.add(artist);
    }

    public ArrayList<Artist> getArtists(){
        return this.artists;
    }

    public boolean containsArtist(Artist artist){
        return artists.contains(artist);
    }


}
