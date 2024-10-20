#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include "RequestQueue.h"
#include <vector>

/**
 * @class LoadBalancer
 * @brief Manages the distribution of requests across multiple WebServer instances.
 * 
 * The LoadBalancer class generates requests, distributes them to web servers,
 * and dynamically adds or removes servers based on the request load. It also
 * tracks the total number of servers added/removed and the total number of requests
 * created/completed.
 */
class LoadBalancer {
private:
    std::vector<WebServer> servers; ///< Vector of WebServer objects
    RequestQueue requestQueue;      ///< Queue holding incoming requests
    int currentTime;                ///< Current clock cycle
    int totalServersAdded;          ///< Total number of servers added during simulation
    int totalServersRemoved;        ///< Total number of servers removed during simulation
    int totalRequestsCreated;       ///< Total number of requests created during simulation
    int totalRequestsCompleted;     ///< Total number of requests completed during simulation

public:
    /**
     * @brief Generates a random IP address in the form of 'xxx.xxx.xxx.xxx'.
     * 
     * @return A random IP address as a string.
     */
    std::string generateRandomIP();

    /**
     * @brief Constructs a LoadBalancer with a specified number of servers.
     * @param numServers Initial number of servers.
     */
    LoadBalancer(int numServers);

    /**
     * @brief Adds a request to the request queue.
     * @param request The request to add.
     */
    void addRequest(const Request& request);

    /**
     * @brief Simulates the LoadBalancer's operations over a specified runtime.
     * @param runTime The total number of clock cycles for the simulation.
     */
    void simulate(int runTime);

    /**
     * @brief Adjusts the number of servers based on the size of the request queue.
     * @param logFile The file for output to be directed to.
     */
    void adjustServers(std::ofstream& logFile);

    /**
     * @brief Generates a random request with random IP addresses, processing time, and job type.
     * @return A randomly generated request.
     */
    Request generateRandomRequest();

    /**
     * @brief Displays the total number of servers added and removed during the simulation, as well as the number of requests created and completed.
     * @param logFile The file for output to be directed to.
     */
    void displayServerChanges(std::ofstream& logFile) const;

    /**
     * @brief Adds a specified amount of initial requests to the total request count.
     */
    void addDefaultRequests(int requests);
};

#endif // LOADBALANCER_H
