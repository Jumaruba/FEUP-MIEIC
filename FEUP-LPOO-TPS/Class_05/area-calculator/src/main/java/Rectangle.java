public class Rectangle implements AreaShape {
    double x, y;
    public Rectangle(double x, double y){
        this.x = x;
        this.y = y;
    }
    @Override
    public double getArea(){
        return this.x*this.y;
    }
    @Override
    public String draw(){
        return "Rectangle";
    }
}
