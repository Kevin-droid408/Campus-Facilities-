#include "Request.h"

/*parameterized constructor to initialize the Request*/
Request::Request(int id, string des, Priority p, Status s){
    requestID = id;
    description = des;
    priority = p;
    status = s;
}

/*Default constructor to initialize the Request*/
Request::Request(){
    requestID = 0;
    description = " ";
    priority = Priority::LOW;
    status = Status::PENDING;
}

/*getRequestID getter*/
int Request::getRequestID() const{
    return requestID;
}

/*getDescription getter*/
string Request::getDescription() const{
    return description;
}

/*getPriority getter*/
Priority Request::getPriority() const{
    return priority;
}

/*getStatus getter*/
Status Request::getStatus() const{
    return status;
} 

/*setStatus setter*/
void Request::setStatus(Status s){
    status = s;
}

/*comparison operators for the max heap*/
bool Request::operator>(const Request& other) const{
    if(priority != other.priority){
        return priority > other.priority;
    }
    return requestID < other.requestID;
}

bool Request::operator<(const Request& other) const{
    if(priority != other.priority){
        return priority < other.priority;
    }
    return requestID > other.requestID;   
}

bool Request::operator==(const Request& other) const{
    return requestID == other.requestID;
}