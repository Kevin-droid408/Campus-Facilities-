#include "RequestProcessor.h"
#include <iostream>
using namespace std;

/*default constructor to initialize request processing*/
RequestProcessor::RequestProcessor()
    : priorityRequests(10){

}

/*submit a normal request*/
void RequestProcessor::submitNormalRequest(const Request& request){
    normalRequests.enqueue(request);
    cout << "Normal request submitted successfully. \n";
}

/*submit a priority request*/
void RequestProcessor::submitPriorityRequest(const Request& request){
    priorityRequests.insert(request);
}

/*process the first normal request*/
void RequestProcessor::processNormalRequest(){
    if (normalRequests.isEmpty()){
        cout << "No normal requests to process!" << endl;
        return;
    }

    Request request = normalRequests.peek();
    normalRequests.dequeue();
    processedRequests.push(request);

    cout << "Processed normal request: "
         << request.getRequestID() << " - "
         << request.getDescription() << endl;
}

/*process the highest-priority request*/
void RequestProcessor::processPriorityRequest(){
    if (priorityRequests.isEmpty()){
        cout << "No priority requests to process!" << endl;
        return;
    }

    Request request = priorityRequests.pop();
    processedRequests.push(request);

    cout << "Processed priority request: "
         << request.getRequestID() << " - "
         << request.getDescription() << endl;
}

/*display normal requests*/
void RequestProcessor::displayNormalRequests() {
    normalRequests.display();
}

/*display priority requests*/
void RequestProcessor::displayPriorityRequests() {
    priorityRequests.display();
}

/*display all pending requests*/
void RequestProcessor::displayPendingRequests(){
    cout << "Normal Pending Requests!" << endl;
    displayNormalRequests();

    cout << "Priority Pending Requests!" << endl;
    displayPriorityRequests();
}