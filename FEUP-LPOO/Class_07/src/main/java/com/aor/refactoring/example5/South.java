package com.aor.refactoring.example5;

public class South extends Direction{

    public South(int row, int column) {
        super(row, column);
    }

    @Override
    public Direction turnLeft() {
        return new East(row, column);
    }

    @Override
    public Direction turnRight() {
        return new West(row, column);
    }

    @Override
    public void moveFoward() {
        this.row++;
    }

    @Override
    public Character getDirection() {
        return 'S';
    }
}
