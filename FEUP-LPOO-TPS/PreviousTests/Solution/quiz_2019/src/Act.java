import java.util.ArrayList;
import java.util.List;

abstract class Act  {
    protected String name;
    protected String country;
    Act(String name, String country){
        this.name = name;
        this.country = country;
    }

    public String getName(){
        return this.name;
    }
    public String getCountry(){
        return this.country;
    }

}
