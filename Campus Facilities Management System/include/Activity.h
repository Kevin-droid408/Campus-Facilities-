#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
using namespace std;

class Activity{
    private:
        int activityID;
        string date;                    //YY-MM-DD format
        string description;
        int startMinutes;               // minutes after midnight
        int duration;                   // duration in minutes

    public:
        Activity(int, string, string, int, int);

        int getActivityID() const;
        string getDate() const;
        string getDescription() const;
        int getStartMinutes() const;
        int getDuration() const;

        int getEndMinutes() const;
};
#endif