import com.sun.org.apache.bcel.internal.generic.ARETURN;

import java.util.List;

public class City implements SumProvider{
    List<House> houses;

    public City(List<House> houses){
        this.houses = houses;
    }

    @Override
    public double sum() {
        double sum= 0;
        for (House h: this.houses) sum+=h.getArea();
        return sum;
    }
}
