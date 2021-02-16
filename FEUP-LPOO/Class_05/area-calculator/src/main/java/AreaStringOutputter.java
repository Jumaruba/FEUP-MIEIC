public class AreaStringOutputter{
    SumProvider a;
    public AreaStringOutputter(SumProvider a){
        this.a = a;
    }

    public String output() {
        return "Sum of areas: " + a.sum();
    }
}
