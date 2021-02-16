import java.util.ArrayList;
import java.util.List;

public abstract class Bar {
    Boolean HappyHour = false;
    ArrayList<BarObserver> observers;
    public Bar(){
        this.observers = new ArrayList<>();
    }

    public Boolean isHappyHour(){
        return HappyHour;
    }

    public void startHappyHour(){
        HappyHour = true;
        notifyObservers();
    }

    public void endHappyHour(){
        HappyHour = false;
        notifyObservers();
    }

    //subscribe
    public void addObserver(BarObserver observer){
        observers.add(observer);
    }
    //unsubscribe
    public void removeObserver(BarObserver observer){
        observers.remove(observer);
    }
    //update
    void notifyObservers(){
        for (BarObserver observer: observers){
            if (isHappyHour()) observer.happyHourStarted(this);
            else observer.happyHourEnded(this);
        }
    }

}
