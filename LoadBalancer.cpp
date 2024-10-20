#include "LoadBalancer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Generates a random IP address in the form of 'xxx.xxx.xxx.xxx'.
 * 
 * @return A random IP address as a string.
 */
std::string LoadBalancer::generateRandomIP() {
    return std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
}

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
    std::string ipIn = generateRandomIP();
    std::string ipOut = generateRandomIP();
    int processingTime = (rand() % 30) + 1;
    char jobType = (rand() % 2 == 0) ? 'P' : 'S';

    return Request(ipIn, ipOut, processingTime, jobType);
}

/**
 * @brief Dynamically adjusts the number of servers based on the request queue size.
 * @param logFile The file for output to be directed to.
 */
void LoadBalancer::adjustServers(std::ofstream& logFile) {
    int numServers = servers.size();
    int numRequests = requestQueue.isEmpty() ? 0 : requestQueue.size();
    
    if (numRequests >= 100 * numServers) {
        servers.emplace_back();
        totalServersAdded++;
        logFile << "Clock cycle " << currentTime << ": Added a new server. Total servers: " << servers.size() << std::endl;
    }
    
    if (numRequests <= numServers / 3 && numServers > 3) {
        servers.pop_back();
        totalServersRemoved++;
        logFile << "Clock cycle " << currentTime << ": Removed a server. Total servers: " << servers.size() << std::endl;
    }
}

/**
 * @brief Simulates the LoadBalancer's operation over a specified number of clock cycles.
 */
void LoadBalancer::simulate(int runTime) {
    std::ofstream logFile("load_balancer_log.txt"); // Open log file
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return;
    }
    logFile << "Request processing times range from 1-30 clock cycles" << std::endl;
    logFile << "Beginning queue size: " << requestQueue.size() << std::endl;
    
    for (currentTime = 0; currentTime < runTime; ++currentTime) {
        if (currentTime % 60 == 0) {
            logFile << "\n---- Status at clock cycle: " << currentTime << " ----" << std::endl;
            logFile << "Total servers: " << servers.size() << std::endl;
            logFile << "Requests in queue: " << requestQueue.size() << std::endl;

            // Display status of each server
            for (size_t i = 0; i < servers.size(); ++i) {
                if (servers[i].isBusy()) {
                    logFile << "Server " << i + 1 << " is busy with " << servers[i].getRemainingTime() << " clock cycles remaining." << std::endl;
                } else {
                    logFile << "Server " << i + 1 << " is idle." << std::endl;
                }
            }

            logFile << "----------------------------------" << std::endl;
        }

        if (rand() % 2 == 0) {
            Request newRequest = generateRandomRequest();
            requestQueue.addRequest(newRequest);
            totalRequestsCreated++;
            logFile << "Clock cycle " << currentTime << ": New request added: " << newRequest.getIPIn() << " -> " << newRequest.getIPOut() << " (" << newRequest.getJobType() << ")" << std::endl;
        }

        adjustServers(logFile);

        for (auto& server : servers) {
            if (!server.isBusy() && !requestQueue.isEmpty()) {
                Request req = requestQueue.getNextRequest();
                server.processRequest(req);
                logFile << "Clock cycle " << currentTime << ": Server is processing request from " << req.getIPIn() << " to " << req.getIPOut() << " (" << req.getJobType() << ") for " << req.getTime() << " cycles." << std::endl;
            }
        }

        for (auto& server : servers) {
            if (server.isBusy()) {
                server.tick();
                if (!server.isBusy()) {
                    totalRequestsCompleted++;
                    logFile << "Clock cycle " << currentTime << ": Request completed by server from " << server.getCurrentRequest().getIPIn() << " to " << server.getCurrentRequest().getIPOut() << " (" << server.getCurrentRequest().getJobType() << ") in " << server.getCurrentRequest().getTime() << " cycles." << std::endl;
                }
            }
        }
    }

    displayServerChanges(logFile);
    logFile.close();
}

/**
 * @brief Displays the total number of servers added, removed, requests created, and requests completed after the simulation ends.
 * @param logFile The file for output to be directed to.
 */
void LoadBalancer::displayServerChanges(std::ofstream& logFile) const {
    logFile << std::endl << "Simulation complete." << std::endl;
    logFile << "Total servers added: " << totalServersAdded << std::endl;
    logFile << "Total servers removed: " << totalServersRemoved << std::endl;
    logFile << "Total requests created: " << totalRequestsCreated << std::endl;
    logFile << "Total requests completed: " << totalRequestsCompleted << std::endl;
    logFile << "Final queue size: " << requestQueue.size() << std::endl;
}

void LoadBalancer::addDefaultRequests(int requests) {
    totalRequestsCreated += requests;
}