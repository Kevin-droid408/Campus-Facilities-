#include "Activity.h"

/*Parameterized constructor to initialize the Activity*/
Activity::Activity(int id, string d, string des, int min, int dur ){
    activityID = id;
    date = d;
    description = des;
    startMinutes = min;
    duration = dur;
}

/*getActivityID getter*/
int Activity::getActivityID() const{
    return activityID;
}

/*getDate getter*/
string Activity::getDate() const{
    return date;
}

/*getDescription getter*/
string Activity::getDescription() const{
    return description;
}

/*getStartMinutes*/
int Activity::getStartMinutes() const{
    return startMinutes;
}

/*getDuration getter*/
int Activity::getDuration() const{
    return duration;
}

/*getEndMinutes getter*/
int Activity::getEndMinutes() const{
    return startMinutes + duration;
}