#include "WebServer.h"
#include <iostream>

WebServer::WebServer() : busy(false), remainingTime(0) {}

void WebServer::processRequest(const Request& request) {
    currentRequest = request;
    remainingTime = request.time;
    busy = true;
    std::cout << "Started processing request: " << request.ipIn << " -> "
              << request.ipOut << " Time: " << request.time
              << " JobType: " << request.jobType << std::endl;
}

void WebServer::tick() {
    if (busy) {
        remainingTime--;
        if (remainingTime <= 0) {
            busy = false;
            std::cout << "Finished processing request: " << currentRequest.ipIn << " -> "
                      << currentRequest.ipOut << std::endl;
        }
    }
}

bool WebServer::isBusy() const {
    return busy;
}
