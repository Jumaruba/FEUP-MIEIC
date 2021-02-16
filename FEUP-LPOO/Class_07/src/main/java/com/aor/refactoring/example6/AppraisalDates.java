package com.aor.refactoring.example6;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

public class AppraisalDates {
    private List<Date> appraisals;

    public AppraisalDates(){
        this.appraisals  = new ArrayList<>();
    }

    private Date getLatestAppraisalDate(){
        Date latestAppraisalDate = !this.appraisals.isEmpty() ? this.appraisals.get(0) : new Date();
        for(Date appraisalDate : this.appraisals)
            latestAppraisalDate = latestAppraisalDate.before(appraisalDate) ? appraisalDate: latestAppraisalDate;

        return latestAppraisalDate;
    }

    public Date getNextAppraisalDate(){
        Date latestAppraisalDate = getLatestAppraisalDate();
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(latestAppraisalDate);
        calendar.add(Calendar.MONTH, 3);
        int dayOfWeek = calendar.get(Calendar.DAY_OF_WEEK);

        if (dayOfWeek == Calendar.SATURDAY)
            calendar.add(Calendar.DAY_OF_MONTH, 1);
        else if (dayOfWeek == Calendar.SUNDAY)
            calendar.add(Calendar.DAY_OF_MONTH, 2);

        return calendar.getTime();
    }

    public List<Date> getAppraisals() {
        return appraisals;
    }

    public void addAppraisal(Date appraisalDate) {
        this.appraisals.add(appraisalDate);
    }
}
