package com.aor.refactoring.example5;

//smell:
//object orientation violators: switch statments
//solve: use the command design pattern

public class Turtle {
    private Direction direction;

    public Turtle(Direction direction) {
        this.direction = direction;
    }

    public int getRow() {
        return direction.getRow();
    }

    public int getColumn() {
        return direction.getColumn();
    }

    public char getDirection() {
        return direction.getDirection();
    }

    public void execute(char command) {
        if (command == 'L') this.direction = direction.turnLeft();
        else if (command == 'R')  this.direction = direction.turnRight();
        else if (command == 'F') direction.moveFoward();

    }
}
