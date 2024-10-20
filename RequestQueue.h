#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "Request.h"
#include <queue>

class RequestQueue {
private:
    std::queue<Request> queue;

public:
    void addRequest(const Request& request);
    Request getNextRequest();
    bool isEmpty() const;
    int size() const;  // Declare size method
};

#endif // REQUESTQUEUE_H
