package com.aor.refactoring.example3;

public class percentageDiscount implements Discount{
    private double percentage;

    public percentageDiscount(double percentage){
        setPercentage(percentage);
    }

    public void setPercentage(double percentage){
        this.percentage = percentage;
    }

    @Override
    public double applyDiscount(double price) {
        return price*(1-percentage);
    }
}
