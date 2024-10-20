#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @brief Represents a web server that processes requests.
 */
class WebServer {
private:
    bool busy;                  ///< Indicates if the server is currently processing a request.
    int remainingTime;         ///< Remaining time for the current request.
    Request currentRequest;     ///< The request currently being processed.

public:
    WebServer();               ///< Constructor for WebServer.
    void processRequest(const Request& request); ///< Processes the given request.
    void tick();               ///< Decreases remaining time for the current request.
    bool isBusy() const;       ///< Checks if the server is busy.
    Request getCurrentRequest() const; ///< Gets the current request being processed.
    int getRemainingTime();    ///< Gets remaining time left on current request, if any.
};

#endif // WEBSERVER_H
