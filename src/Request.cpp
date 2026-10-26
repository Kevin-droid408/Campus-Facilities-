#include "Request.h"

/*parameterized constructor to initialize the Request*/
Request::Request(int id, string des, Priority p, RequestStatus s){
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
    status = RequestStatus::PENDING;
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

/*getRequestStatus getter*/
RequestStatus Request::getRequestStatus() const{
    return status;
} 

/*setRequestStatus setter*/
void Request::setRequestStatus(RequestStatus s){
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

/*stream insertion operator so a Request can be printed with cout*/
ostream& operator<<(ostream& os, const Request& request){
    string p;
    switch(request.getPriority()){
        case Priority::LOW:       p = "LOW";       break;
        case Priority::NORMAL:    p = "NORMAL";    break;
        case Priority::HIGH:      p = "HIGH";      break;
        case Priority::EMERGENCY: p = "EMERGENCY"; break;
    }

    string s;
    switch(request.getRequestStatus()){
        case RequestStatus::PENDING:     s = "PENDING";     break;
        case RequestStatus::IN_PROGRESS: s = "IN_PROGRESS"; break;
        case RequestStatus::COMPLETE:    s = "COMPLETE";    break;
    }

    os << "[ID: " << request.getRequestID()
       << ", " << request.getDescription()
       << ", " << p << ", " << s << "]";
    return os;
}