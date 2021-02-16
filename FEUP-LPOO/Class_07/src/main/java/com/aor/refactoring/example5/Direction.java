package com.aor.refactoring.example5;

public abstract class Direction {

    protected int row;
    protected int column;

    public Direction(int row, int column){
        this.row = row;
        this.column = column;
    }

    public int getRow(){
        return this.row;
    }
    public int getColumn(){
        return this.column;
    }

    public abstract Character getDirection();
    public abstract Direction turnLeft();
    public abstract Direction turnRight();
    public abstract void moveFoward();
}
