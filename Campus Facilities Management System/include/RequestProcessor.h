#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H

#include "Request.h"
#include "Queue.h"
#include "Stack.h"
#include "PriorityQueue.h"

class RequestProcessor{
    private:
        Queue<Request> normalRequests;
        Stack<Request> processedRequests;
        PriorityQueue<Request> priorityRequests;

    public:
        RequestProcessor();

        void submitNormalRequest(const Request&);
        void submitPriorityRequest(const Request&);

        void processNormalRequest();
        void processPriorityRequest();

        void displayNormalRequests();
        void displayPriorityRequests();
        void displayPendingRequests();

};
#endif