package com.aor.refactoring.example3;

public class fixedDiscount implements Discount{
    private double fixed;
    public fixedDiscount(int fixed){
        setFixed(fixed);
    }

    public void setFixed(int fixed){
        this.fixed = fixed;
    }

    @Override
    public double applyDiscount(double price) {
        return fixed > price ? 0 : price - fixed;
    }
}
