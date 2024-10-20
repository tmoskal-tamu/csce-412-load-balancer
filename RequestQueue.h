#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "Request.h"
#include <queue>

/**
 * @class RequestQueue
 * @brief Manages a queue of requests to be processed by web servers.
 * 
 * The RequestQueue class allows for adding requests to the queue and retrieving 
 * requests in a first-in-first-out (FIFO) order. It also checks whether the 
 * queue is empty.
 */
class RequestQueue {
private:
    std::queue<Request> requestQueue; ///< Queue of Request objects

public:
    /**
     * @brief Adds a request to the queue.
     * @param request The request to add.
     */
    void addRequest(const Request& request);

    /**
     * @brief Retrieves and removes the next request from the queue.
     * @return The next request in the queue.
     */
    Request getNextRequest();

    /**
     * @brief Checks if the request queue is empty.
     * @return True if the queue is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Gets the current number of requests in the queue.
     * @return The number of requests in the queue.
     */
    int size() const;
};

#endif // REQUESTQUEUE_H
