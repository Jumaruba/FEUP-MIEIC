public class Ellipse implements HasArea {
    private double xradius, yradius;
    public Ellipse(double xradius, double yradius){
        this.xradius = xradius;
        this.yradius = yradius;
    }

    @Override
    public double getArea() {
        return Math.PI * xradius * yradius;
    }
}
