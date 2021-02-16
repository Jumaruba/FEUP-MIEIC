package com.aor.refactoring.example1;

import java.util.ArrayList;
import java.util.List;

public class Order {
    private List<OrderLine> lines;

    public Order() {
        lines = new ArrayList<>();
    }

    public void add(Product product, int quantity) {
        lines.add(new OrderLine(product, quantity));
    }

    public boolean isElegibleForFreeDelivery() {
        return getTotalPrice()>100;
    }
    public double getTotalPrice(){
        double total = 0;
        for (OrderLine line : lines)
            total += line.getPrice();
        return total;
    }
    public String toString(OrderLine line){
        return line.toString() + line.getPrice() + '\n';
    }

    public String printOrder() {
        StringBuffer printBuffer = new StringBuffer();

        for (OrderLine line : lines)
            printBuffer.append(this.toString(line));

        printBuffer.append("Total: " + getTotalPrice());

        return printBuffer.toString();
    }
}