public class Triangle implements AreaShape{
    double base, height;
    public Triangle(double base, double height){
        this.base = base;
        this.height = height;
    }
    @Override
    public double getArea(){
        return this.base*this.height/2;
    }

    @Override
    public String draw() {
        return "Triangle";
    }
}
