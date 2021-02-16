package com.aor.refactoring.example4;

//smells:
//refused bequest

public class Client extends Person {

    public Client(String name, String phone) {
        super(name, phone);
    }
}
