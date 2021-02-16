package com.aor.refactoring.example2;

//refactorings:
//extract class

//smells:
//bloaters: large class, large methods, many parameters
//dispensable: duplicate code, comments
//change prevent: divergent change

//SOLID
//interface segregation principle

public abstract class Shape {

    private double x;
    private double y;

    public Shape(double x, double y) {
        setX(x);
        setY(y);
    }


    public void setX(double x){
        this.x = x;
    }

    public void setY(double y){
        this.y = y;
    }

    public double getX(double x){
        return x;
    }

    public double getY(double y){
        return y;
    }

    public double getArea() throws Exception {
        throw new Exception("Shape with no type");

    }

    public double getPerimeter() throws Exception {
        throw new Exception("Shape with no type");
    }

    public abstract void draw(GraphicFramework graphics);
}
