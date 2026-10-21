#ifndef ACTIVITYSCHEDULER_H
#define ACTIVITYSCHEDULER_H

#include "Activity.h"
#include "Node.h"

class ActivityScheduler{
    private:
        Node<Activity>* head;

    public:
        ActivityScheduler();
        ~ActivityScheduler();

        bool scheduleActivity(const Activity&);
        void displayActivities() const;
        bool hasConflict(const Activity&) const;                    //function to check conflicts
};

#endif