package com.aor.numbers;

public class DivisibleByFilter implements IListFilter{
    Integer n;
    public DivisibleByFilter(Integer n){
        this.n = n;
    }
    public boolean accept(Integer number){
        if (number == 0) return false;
        return number%n == 0;
    }
}
