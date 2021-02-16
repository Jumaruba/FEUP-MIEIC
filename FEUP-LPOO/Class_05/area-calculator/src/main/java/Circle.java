public class Circle implements AreaShape{
    private float radius;
    public Circle(float radius){
        this.radius = radius;
    }

    @Override
    public double getArea(){
        return Math.PI * Math.pow(radius,2);
    }

    @Override
    public String draw() {
        return "Circle";
    }
}
