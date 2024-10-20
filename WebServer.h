#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class WebServer {
private:
    bool busy;
    Request currentRequest;
    int remainingTime;

public:
    WebServer();
    void processRequest(const Request& request);
    void tick();
    bool isBusy() const;
};

#endif // WEBSERVER_H
