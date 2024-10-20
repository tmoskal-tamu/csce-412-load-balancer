#include "WebServer.h"

/**
 * @brief Constructs a WebServer instance.
 */
WebServer::WebServer() : busy(false), remainingTime(0), currentRequest("0.0.0.0", "0.0.0.0", 0, 'P') {}

/**
 * @brief Processes a request by marking the server as busy and setting the remaining time.
 * @param request The request to process.
 */
void WebServer::processRequest(const Request& request) {
    currentRequest = request;         // Store the current request.
    busy = true;                      // Mark the server as busy.
    remainingTime = request.getTime(); // Set remaining time to the time of the request.
}

/**
 * @brief Decreases the remaining time for the current request.
 * If the remaining time reaches zero, marks the server as not busy.
 */
void WebServer::tick() {
    if (busy) {
        remainingTime--; // Decrement remaining time.

        if (remainingTime <= 0) {
            busy = false; // Mark the server as not busy if the request is complete.
        }
    }
}

/**
 * @brief Checks if the server is currently busy.
 * @return true if the server is busy, false otherwise.
 */
bool WebServer::isBusy() const {
    return busy;
}

/**
 * @brief Gets the current request being processed.
 * @return The current request.
 */
Request WebServer::getCurrentRequest() const {
    return currentRequest; // Return the current request.
}

int WebServer::getRemainingTime() {
    return remainingTime;
}