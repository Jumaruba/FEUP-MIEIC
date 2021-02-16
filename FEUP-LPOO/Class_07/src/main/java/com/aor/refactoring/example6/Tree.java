package com.aor.refactoring.example6;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

//switch statements
//bloaters: many parameters, huge methods, class too large
//solution 1: extract class for location
//solution 2: extract methods

//unnecessary comments

//Couplers:
//Inappropriate intimacy: public parameters
//solution: set to private and create get methods

//Objects oriented violations:
//switch statements

public class Tree {
    public Date plantedAt;
    private Location location;
    private AppraisalDates appraisalDates;

    public Tree(Date plantedAt, Location location){
        this.plantedAt = plantedAt;
        this.setLocation(location);
        this.appraisalDates = new AppraisalDates();
    }

    public void setLocation(Location location){
        this.location = location;
    }

    public Location getLocation(){
        return this.location;
    }
    public String toString() {
        return "Tree planted at " + this.plantedAt.toString() + this.location.toString();
    }

    public void addAppraisal(Date appraisalDate) {
        this.appraisalDates.addAppraisal(appraisalDate);
    }

    public List<Date> getAppraisals(){
        return this.appraisalDates.getAppraisals();
    }


    public boolean isNextAppraisalOverdue(){
        Date nextAppraisalDate = appraisalDates.getNextAppraisalDate();
        return nextAppraisalDate.before(new Date());
    }
}
