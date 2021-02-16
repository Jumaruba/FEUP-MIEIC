package com.aor.refactoring.example6;

public class Location {
    private String latitude;
    private String longitude;
    private String name;

    public Location(String latitude, String longitude, String name){
        setLatitude(latitude);
        setLongitude(longitude);
        setName(name);
    }
    public void setLatitude(String latitude){
        this.latitude = latitude;
    }

    public void setLongitude(String longitude) {
        this.longitude = longitude;
    }

    public void setName(String name){
        this.name = name;
    }

    public String getName(){
        return this.name;
    }

    public String getLatitude() {
        return latitude;
    }

    public String getLongitude() {
        return longitude;
    }

    @Override
    public String toString() {
        return  " in location " + this.latitude + "," + this.longitude + " (" + this.name + ")";
    }
}
