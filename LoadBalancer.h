#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include "RequestQueue.h"
#include <vector>

class LoadBalancer {
private:
    std::vector<WebServer> servers;
    RequestQueue requestQueue;
    int currentTime;
    int totalServersAdded;   // Track how many servers are added
    int totalServersRemoved; // Track how many servers are removed

public:
    LoadBalancer(int numServers);
    void addRequest(const Request& request);
    void simulate(int runTime);
    void adjustServers();  // Adjust servers dynamically based on the queue size
    void displayServerChanges() const;  // New method to display server changes
    Request generateRandomRequest();
};

#endif // LOADBALANCER_H
