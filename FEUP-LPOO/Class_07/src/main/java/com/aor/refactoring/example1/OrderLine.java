package com.aor.refactoring.example1;

public class OrderLine {
    public Product product;
    public int quantity;

    public OrderLine(Product product, int quantity) {
        setQuantity(quantity);
        setProduct(product);
    }

    public double getQuantity(){
        return quantity;
    }
    public Product getProduct(){
        return product;
    }

    public void setQuantity(int quantity){
        this.quantity = quantity;
    }

    public void setProduct(Product product) {
        this.product = product;
    }

    public double getPrice(){
        return product.getPrice() * quantity;
    }

    public String toString(){
        return product.getName() + "(x" + quantity + "): ";
    }


}
