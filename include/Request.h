#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
using namespace std;

/*enum class declarations*/
enum class Priority{
    LOW = 1,
    NORMAL = 2,
    HIGH = 3,
    EMERGENCY = 4
};

enum class RequestStatus{
    PENDING,
    IN_PROGRESS,
    COMPLETE,
};

/*class Request declaration*/
class Request{
    private:
        int requestID;
        string description;
        Priority priority;                      // an object of type Priority
        RequestStatus status;                         // an object of type Status
    public:
        Request(int, string, Priority, RequestStatus);
        Request();

        int getRequestID() const;
        string getDescription() const;
        Priority getPriority() const;
        RequestStatus getRequestStatus() const;

        void setRequestStatus(RequestStatus);

        bool operator>(const Request& other) const;
        bool operator<(const Request& other) const;
        bool operator==(const Request& other) const;
};

/*stream insertion operator so a Request can be printed with cout*/
ostream& operator<<(ostream& os, const Request& request);

#endif