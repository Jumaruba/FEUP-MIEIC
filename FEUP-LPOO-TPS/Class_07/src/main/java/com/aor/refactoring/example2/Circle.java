package com.aor.refactoring.example2;

public class Circle extends Shape{
    private double radius;
    private double x;
    private double y;

    public Circle(double x, double y, double radius){
        super(x,y);
    }

    public void setRadius(double radius){
        this.radius = radius;
    }

    @Override
    public double getArea(){
        return Math.PI * Math.pow(radius, 2);
    }

    @Override
    public double getPerimeter(){
        return 2 * Math.PI * radius;
    }

    @Override
    public void draw(GraphicFramework graphics) {
        graphics.drawCircle(x, y, radius);
    }
}
