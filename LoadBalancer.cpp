#include "LoadBalancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructs a LoadBalancer with a specified number of servers.
 */
LoadBalancer::LoadBalancer(int numServers) : currentTime(0), totalServersAdded(0), totalServersRemoved(0), totalRequestsCreated(0), totalRequestsCompleted(0) {
    int initialServers = std::max(3, numServers);
    servers.resize(initialServers);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

/**
 * @brief Adds a request to the request queue.
 * @param request The request to add.
 */
void LoadBalancer::addRequest(const Request& request) {
    requestQueue.addRequest(request);
}

/**
 * @brief Generates a random request.
 * @return A randomly generated request.
 */
Request LoadBalancer::generateRandomRequest() {
    std::string ipIn = "192.168.1." + std::to_string(rand() % 255);
    std::string ipOut = "10.0.0." + std::to_string(rand() % 255);
    int processingTime = (rand() % 10) + 1;
    char jobType = (rand() % 2 == 0) ? 'P' : 'S';

    return Request(ipIn, ipOut, processingTime, jobType);
}

/**
 * @brief Dynamically adjusts the number of servers based on the request queue size.
 */
void LoadBalancer::adjustServers() {
    int numServers = servers.size();
    int numRequests = requestQueue.isEmpty() ? 0 : requestQueue.size();
    
    if (numRequests >= 100 * numServers) {
        servers.emplace_back();
        totalServersAdded++;
        std::cout << "Clock cycle " << currentTime << ": Added a new server. Total servers: " << servers.size() << std::endl;
    }
    
    if (numRequests <= numServers / 3 && numServers > 3) {
        servers.pop_back();
        totalServersRemoved++;
        std::cout << "Clock cycle " << currentTime << ": Removed a server. Total servers: " << servers.size() << std::endl;
    }
}

/**
 * @brief Simulates the LoadBalancer's operation over a specified number of clock cycles.
 */
void LoadBalancer::simulate(int runTime) {
    for (currentTime = 0; currentTime < runTime; ++currentTime) {
        if (currentTime % 60 == 0) {
            std::cout << "----------------------------------" << std::endl;
            std::cout << "Clock cycle: " << currentTime << std::endl;
            std::cout << "Current server count: " << servers.size() << std::endl;
            std::cout << "Current size of request queue: " << requestQueue.size() << std::endl;
            std::cout << "----------------------------------" << std::endl;
        }

        if (rand() % 2 == 0) {
            Request newRequest = generateRandomRequest();
            requestQueue.addRequest(newRequest);
            totalRequestsCreated++;
            std::cout << "Clock cycle " << currentTime << ": New request added: " << newRequest.getIPIn() << " -> " 
                      << newRequest.getIPOut() << " (" << newRequest.getJobType() << ")" << std::endl;
        }

        adjustServers();

        for (auto& server : servers) {
            if (!server.isBusy() && !requestQueue.isEmpty()) {
                Request req = requestQueue.getNextRequest();
                server.processRequest(req);
                std::cout << "Clock cycle " << currentTime << ": Server is processing request from " 
                          << req.getIPIn() << " to " << req.getIPOut() << " (" << req.getJobType() << ") for " 
                          << req.getTime() << " cycles." << std::endl;
            }
        }

        for (auto& server : servers) {
            if (server.isBusy()) {
                server.tick();
                if (!server.isBusy()) {
                    totalRequestsCompleted++;
                    std::cout << "Clock cycle " << currentTime << ": Request completed by server. IP In: "
                              << server.getCurrentRequest().getIPIn() << ", IP Out: "
                              << server.getCurrentRequest().getIPOut() << ", Time taken: "
                              << server.getCurrentRequest().getTime() << " cycles." << std::endl;
                }
            }
        }
    }

    displayServerChanges();
}

/**
 * @brief Displays the total number of servers added, removed, requests created, and requests completed after the simulation ends.
 */
void LoadBalancer::displayServerChanges() const {
    std::cout << std::endl << "Simulation complete." << std::endl;
    std::cout << "Total servers added: " << totalServersAdded << std::endl;
    std::cout << "Total servers removed: " << totalServersRemoved << std::endl;
    std::cout << "Total requests created: " << totalRequestsCreated << std::endl;
    std::cout << "Total requests completed: " << totalRequestsCompleted << std::endl;
}

void LoadBalancer::addDefaultRequests(int requests) {
    totalRequestsCreated += requests;
}