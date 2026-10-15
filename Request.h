#ifndef REQUEST_H
#define REQUEST_H

#include<iostream>
using namespace std;

class Request{
    private:
        string requestID, userName, resourceID;
        int priority;
        int requestTime;

    public:
        Request();
        Request(string, string, string, int, int);
        string getRequestID();
        string getUserName();
        string getResourceID();
        int getRequestTime();
        int getPriority();
        void display();
};

#endif