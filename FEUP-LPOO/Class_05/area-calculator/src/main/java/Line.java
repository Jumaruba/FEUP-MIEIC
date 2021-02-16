public class Line implements Shape{
    private double length;

    public Line(double lenght){
        this.length = lenght;
    }

    public void getArea() throws NoAreaException {
        throw new NoAreaException("No area");
    }

    @Override
    public String draw() {
        return "Line";
    }
}
