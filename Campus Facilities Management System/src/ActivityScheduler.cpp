#include "ActivityScheduler.h"
#include <iostream>
using namespace std;

/*default constructor to initialize the ActivityScheduler*/
ActivityScheduler::ActivityScheduler(){
    head = nullptr;
}

/*Destructor to deallocate memory*/
ActivityScheduler::~ActivityScheduler(){
    Node<Activity>* current = head;

    while(current != nullptr){
        Node<Activity>* temp = current;
        current = current->next;
        delete temp;
    }
}

/*checking for overlapping activities on the same date*/
bool ActivityScheduler::hasConflict(const Activity& activity) const{

    Node<Activity>* current  = head;

    while(current != nullptr){
        if(current->data.getDate() == activity.getDate()){
            int existingStart = current->data.getStartMinutes();
            int existingEnd = current->data.getEndMinutes();
            int newStart = activity.getStartMinutes();
            int newEnd = activity.getEndMinutes();
            if(newStart < existingEnd && newEnd > existingStart){
                return true;
            }
        }

        current = current->next;
    }

    return false;
}

/*Schedule an activity*/
bool ActivityScheduler::scheduleActivity(const Activity& activity){

    /*reject invalid times: negative start, non-positive duration, or ending after midnight*/
    if(activity.getStartMinutes() < 0 || activity.getDuration() <= 0 ||
       activity.getEndMinutes() > 1440){
        cout << "Scheduling failed: invalid start time or duration" << endl;
        return false;
    }

    if(hasConflict(activity)){
        cout << "Scheduling failed: activity overlaps "
             << "with an existing activity" << endl;
        return false;
    }
    
    Node<Activity>* newNode = new Node<Activity>(activity);

    /*Insert at the beginning*/
    if(head == nullptr || activity.getDate() < head->data.getDate() ||
        (activity.getDate() == head->data.getDate() && 
        activity.getStartMinutes() < head->data.getStartMinutes())){
            
        newNode->next = head;
        head = newNode;
    }

    else{

        Node<Activity>* current =  head;

        while(current->next != nullptr &&
            (current->next->data.getDate() < activity.getDate() ||
            (current->next->data.getDate() == activity.getDate() &&
             current->next->data.getStartMinutes() <= activity.getStartMinutes()))){
            
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    cout << "Activity scheduled successfully!" << endl;
    return true;
}

/*Display all scheduled activities*/
void ActivityScheduler::displayActivities() const{

    if(head == nullptr){
        cout << "No activities scheduled!" << endl;
        return;
    }

    Node<Activity>* current = head;
    cout << "---Scheduled Activities---" << endl;

    while(current != nullptr){

        int start = current->data.getStartMinutes();
        int end = current->data.getEndMinutes();

        cout << "Activity ID: "
             << current->data.getActivityID() << endl;
        cout << "Description: "
             << current->data.getDescription() << endl;
        cout << "Date: "
             << current->data.getDate() << endl;
        cout << "Start: ";

        if(start / 60 < 10)
            cout << "0";
        
        cout << start / 60 << ":";

        if(start % 60 < 10)
            cout << "0";
        
        cout << start % 60 << endl;

        cout << "End: ";

         if(end / 60 < 10)
            cout << "0";
        
        cout << end / 60 << ":";

        if(end % 60 < 10)
            cout << "0";

        cout << end % 60 << endl;

        cout << endl;

        current = current->next;
    }
}