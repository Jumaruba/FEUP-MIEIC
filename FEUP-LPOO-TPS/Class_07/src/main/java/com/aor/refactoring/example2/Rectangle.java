package com.aor.refactoring.example2;

public class Rectangle extends Shape {
    double width;
    double height;
    private double x;
    private double y;

    public Rectangle(double x, double y, double width, double height) {
        super(x,y);
        this.width = width;
        this.height = height;
    }

    @Override
    public double getArea(){
        return width*height;
    }

    @Override
    public double getPerimeter(){
        return 2 * (width + height);
    }

    @Override
    public void draw(GraphicFramework graphics) {
        graphics.drawLine(x, y, x + width, y);
        graphics.drawLine(x + width, y, x + width, y + height);
        graphics.drawLine(x + width, y + height, x, y + height);
        graphics.drawLine(x, y + height, x, y);
    }
}
