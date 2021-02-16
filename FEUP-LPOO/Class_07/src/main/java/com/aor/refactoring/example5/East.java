package com.aor.refactoring.example5;

public class East extends Direction{

    public East(int row, int column) {
        super(row, column);
    }

    @Override
    public Direction turnLeft() {
        return new North(row, column);
    }

    @Override
    public Direction turnRight() {
        return new South(row, column);
    }

    @Override
    public void moveFoward() {
        this.column++;
    }

    @Override
    public Character getDirection() {
        return 'E';
    }
}
