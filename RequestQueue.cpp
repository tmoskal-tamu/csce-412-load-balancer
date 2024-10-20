#include "RequestQueue.h"

void RequestQueue::addRequest(const Request& request) {
    queue.push(request);
}

Request RequestQueue::getNextRequest() {
    if (!queue.empty()) {
        Request req = queue.front();
        queue.pop();
        return req;
    }
    return Request(); // Return a default Request if the queue is empty
}

bool RequestQueue::isEmpty() const {
    return queue.empty();
}

// Implement the size method
int RequestQueue::size() const {
    return queue.size();
}
