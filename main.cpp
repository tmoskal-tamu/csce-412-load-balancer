#include "LoadBalancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Helper functions to generate random IP addresses and job types
std::string generateRandomIP() {
    return std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256);
}

char randomJobType() {
    return rand() % 2 == 0 ? 'P' : 'S';
}

int main() {
    srand(time(0)); // Seed for random generator

    int numServers, runTime;
    std::cout << "Enter the initial number of web servers: ";
    std::cin >> numServers;
    std::cout << "Enter the amount of clock cycles to simulate: ";
    std::cin >> runTime;

    LoadBalancer loadBalancer(numServers);

    // Create initial set of requests (servers * 100)
    int initialRequests = numServers * 100;
    for (int i = 0; i < initialRequests; ++i) {
        std::string ipIn = generateRandomIP();
        std::string ipOut = generateRandomIP();
        int time = rand() % 100 + 1;  // Random time between 1 and 100 clock cycles
        char jobType = randomJobType();
        loadBalancer.addRequest(Request(ipIn, ipOut, time, jobType));
    }

    // Simulate load balancing
    loadBalancer.simulate(runTime);

    return 0;
}
