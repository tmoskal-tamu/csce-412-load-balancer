#include "RequestQueue.h"
#include <stdexcept>  // Required for std::runtime_error

/**
 * @brief Adds a request to the queue.
 * @param request The request to add.
 */
void RequestQueue::addRequest(const Request& request) {
    requestQueue.push(request);
}

/**
 * @brief Retrieves and removes the next request from the queue.
 * @return The next request in the queue.
 * @throws std::runtime_error if the queue is empty.
 */
Request RequestQueue::getNextRequest() {
    if (requestQueue.empty()) {
        throw std::runtime_error("Request queue is empty.");
    }
    Request nextRequest = requestQueue.front();
    requestQueue.pop();
    return nextRequest;
}

/**
 * @brief Checks if the request queue is empty.
 * @return True if the queue is empty, false otherwise.
 */
bool RequestQueue::isEmpty() const {
    return requestQueue.empty();
}

/**
 * @brief Gets the current number of requests in the queue.
 * @return The number of requests in the queue.
 */
int RequestQueue::size() const {
    return requestQueue.size();
}
