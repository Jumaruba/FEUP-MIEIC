package com.aor.refactoring.example5;

public class West extends Direction{

    public West(int row, int column) {
        super(row, column);
    }

    @Override
    public Direction turnLeft() {
        return new South(row, column);
    }

    @Override
    public Direction turnRight() {
        return new North(row, column);
    }

    @Override
    public void moveFoward() {
        this.column--;
    }

    @Override
    public Character getDirection() {
        return 'W';
    }
}
