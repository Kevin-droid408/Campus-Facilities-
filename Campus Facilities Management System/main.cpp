#include <iostream>
#include <string>
#include "include/RequestProcessor.h"
#include "include/ActivityScheduler.h"
using namespace std;


int readInt(const string& prompt){
    int value;
    cout << prompt;
    while(!(cin >> value)){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid number, try again: ";
    }
    cin.ignore(1000, '\n');
    return value;
}


string readLine(const string& prompt){
    string text;
    cout << prompt;
    getline(cin, text);
    return text;
}


int readTime(const string& label){
    int h = readInt(label + " hour (0-23): ");
    int m = readInt(label + " minute (0-59): ");
    return h * 60 + m;
}

Request readRequest(){
    int id = readInt("Request ID: ");
    string des = readLine("Description: ");
    int p = readInt("Priority (1=LOW, 2=NORMAL, 3=HIGH, 4=EMERGENCY): ");

    if(p < 1) p = 1;
    if(p > 4) p = 4;

    return Request(id, des, static_cast<Priority>(p), Status::PENDING);
}

void requestMenu(RequestProcessor& rp){
    int choice = -1;

    while(choice != 0){
        cout << "\n--- Request Processor ---" << endl;
        cout << "1. Submit normal request" << endl;
        cout << "2. Submit priority request" << endl;
        cout << "3. Process normal request" << endl;
        cout << "4. Process priority request" << endl;
        cout << "5. Display pending requests" << endl;
        cout << "0. Back" << endl;
        choice = readInt("Choice: ");

        switch(choice){
            case 1: rp.submitNormalRequest(readRequest()); break;
            case 2: rp.submitPriorityRequest(readRequest()); break;
            case 3: rp.processNormalRequest(); break;
            case 4: rp.processPriorityRequest(); break;
            case 5: rp.displayPendingRequests(); break;
            case 0: break;
            default: cout << "Invalid choice!" << endl;
        }
    }
}

void activityMenu(ActivityScheduler& scheduler){
    int choice = -1;

    while(choice != 0){
        cout << "\n--- Activity Scheduler ---" << endl;
        cout << "1. Schedule activity" << endl;
        cout << "2. Display activities" << endl;
        cout << "3. Load sample activities" << endl;
        cout << "0. Back" << endl;
        choice = readInt("Choice: ");

        if(choice == 1){
            int id = readInt("Activity ID: ");
            string date = readLine("Date (YY-MM-DD): ");
            string des = readLine("Description: ");
            int start = readTime("Start");
            int duration = readInt("Duration (minutes): ");

            scheduler.scheduleActivity(Activity(id, date, des, start, duration));
        }
        else if(choice == 2){
            scheduler.displayActivities();
        }
        else if(choice == 3){
            
            scheduler.scheduleActivity(Activity(1, "26-10-25", "Lecture", 600, 60));
            scheduler.scheduleActivity(Activity(2, "26-10-24", "Meeting", 480, 90));
            scheduler.scheduleActivity(Activity(3, "26-10-25", "Lab", 540, 30));
            
            scheduler.scheduleActivity(Activity(4, "26-10-25", "Clash", 630, 60));
            
            scheduler.scheduleActivity(Activity(5, "26-10-26", "Bad", 600, 0));
            
            scheduler.scheduleActivity(Activity(6, "26-10-26", "Late", 1400, 100));
            
            scheduler.scheduleActivity(Activity(7, "26-10-25", "Study", 570, 30));
        }
        else if(choice != 0){
            cout << "Invalid choice!" << endl;
        }
    }
}

int main(){
    RequestProcessor rp;
    ActivityScheduler scheduler;
    int choice = -1;

    while(choice != 0){
        cout << "\n===== Main Menu =====" << endl;
        cout << "1. Request Processor" << endl;
        cout << "2. Activity Scheduler" << endl;
        cout << "0. Exit" << endl;
        choice = readInt("Choice: ");

        switch(choice){
            case 1: requestMenu(rp); break;
            case 2: activityMenu(scheduler); break;
            case 0: cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
/*#include "include/RequestProcessor.h"
#include "include/ActivityScheduler.h"
#include "include/Activity.h"
#include "include/PriorityQueue.h"
#include "include/Queue.h"
#include "include/Request.h"
#include "include/Stack.h"

#include <iostream>
using namespace std;

int main(){
    cout << "Welcome to the Campus Facilities Management System!" << endl;
    cout << "This is a placeholder for the main application logic." << endl;
    return 0;
}*/