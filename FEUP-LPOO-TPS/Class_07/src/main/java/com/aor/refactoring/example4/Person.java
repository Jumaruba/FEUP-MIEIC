package com.aor.refactoring.example4;

public abstract class Person {
    protected String name;
    protected String phone;
    public Person(String name, String phone){
        setName(name);
        setPhone(phone);
    }

    public boolean login(String name, String username){ return false;}

    public void setName(String name){
        this.name = name;
    }

    public void setPhone(String phone){
        this.phone = phone;
    }

    public String getName(){
        return name;
    }

    public String getPhone(){
        return phone;
    }

}
