public class Square implements AreaShape {
    private float side;

    public Square(float side) {
        this.side = side;
    }

    @Override
    public double getArea() {
        return this.side * this.side;
    }

    @Override
    public String draw() {
        return "Square";
    }
}
