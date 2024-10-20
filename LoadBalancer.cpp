#include "LoadBalancer.h"
#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()

LoadBalancer::LoadBalancer(int numServers) : currentTime(0), totalServersAdded(0), totalServersRemoved(0) {
    // Ensure at least 3 servers when the load balancer is initialized
    int initialServers = std::max(3, numServers);
    servers.resize(initialServers);
    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void LoadBalancer::addRequest(const Request& request) {
    requestQueue.addRequest(request);
}

// Function to generate a random request
Request LoadBalancer::generateRandomRequest() {
    // Generate random IP addresses (for simplicity, we'll just use numbers converted to strings)
    std::string ipIn = "192.168.1." + std::to_string(rand() % 255);
    std::string ipOut = "10.0.0." + std::to_string(rand() % 255);
    int processingTime = (rand() % 30) + 1; // Random time between 1 and 10 clock cycles
    char jobType = (rand() % 2 == 0) ? 'P' : 'S'; // Randomly choose between 'P' (processing) and 'S' (streaming)

    return Request(ipIn, ipOut, processingTime, jobType);
}

// Function to dynamically adjust the number of servers based on queue size
void LoadBalancer::adjustServers() {
    int numServers = servers.size();
    int numRequests = requestQueue.isEmpty() ? 0 : requestQueue.size();
    
    // Add a new server if the number of requests is 100 times the number of servers
    if (numRequests >= 100 * numServers) {
        servers.emplace_back();  // Add a new server
        totalServersAdded++;      // Increment the server added count
        std::cout << "Added a new server. Total servers: " << servers.size() << std::endl;
    }
    
    // Remove a server if the number of requests is less than 1/3 of the number of servers,
    // but ensure that we always have at least 3 servers.
    if (numRequests <= numServers / 3 && numServers > 3) {
        servers.pop_back();       // Remove the last server
        totalServersRemoved++;    // Increment the server removed count
        std::cout << "Removed a server. Total servers: " << servers.size() << std::endl;
    }
}

// Simulate the load balancer's operations over a given runtime
void LoadBalancer::simulate(int runTime) {
    for (currentTime = 0; currentTime < runTime; ++currentTime) {
        

        if(currentTime % 50 == 0) {
            std::cout << "----------------------------------" << std::endl;
            std::cout << "Clock cycle: " << currentTime << std::endl;
            std::cout << "Current server count: " << servers.size() << std::endl;
            std::cout << "Current size of request queue: " << requestQueue.size() << std::endl;
            std::cout << "----------------------------------" << std::endl;
        }

        // Randomly generate a request with a 50% chance at each clock cycle
        if (rand() % 2 == 0) {
            Request newRequest = LoadBalancer::generateRandomRequest();
            requestQueue.addRequest(newRequest);
            std::cout << "New request added: " << newRequest.ipIn << " -> " 
                      << newRequest.ipOut << " (" << newRequest.jobType << ")" << std::endl;
        }

        // Adjust the number of servers based on the number of requests in the queue
        adjustServers();

        // Assign new requests to free servers
        for (auto& server : servers) {
            if (!server.isBusy() && !requestQueue.isEmpty()) {
                Request req = requestQueue.getNextRequest();
                server.processRequest(req);
            }
        }

        // Let each server process its request (tick the clock)
        for (auto& server : servers) {
            server.tick();
        }
    }

    // After the simulation, display the total number of servers added and removed
    displayServerChanges();
}

// Display the total number of servers added and removed
void LoadBalancer::displayServerChanges() const {
    std::cout << "\nSimulation complete." << std::endl;
    std::cout << "Total servers added: " << totalServersAdded << std::endl;
    std::cout << "Total servers removed: " << totalServersRemoved << std::endl;
}
