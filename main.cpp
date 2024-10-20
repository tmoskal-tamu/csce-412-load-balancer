#include "LoadBalancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @file main.cpp
 * @brief Entry point for the load balancer simulation with dynamically generated requests.
 * 
 * This file simulates a load balancer that processes web requests using a set of web servers.
 * It dynamically creates requests and distributes them across the servers during the 
 * simulation. The load balancer automatically adjusts the number of servers based on the 
 * request load.
 */

/**
 * @brief Generates a random IP address in the form of 'xxx.xxx.xxx.xxx'.
 * 
 * @return A random IP address as a string.
 */
std::string generateRandomIP() {
    return std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256);
}

/**
 * @brief Randomly selects a job type for the request.
 * 
 * The job type will be either 'P' (Processing) or 'S' (Streaming).
 * 
 * @return A random job type ('P' or 'S').
 */
char randomJobType() {
    return rand() % 2 == 0 ? 'P' : 'S';
}

/**
 * @brief Main function that initializes the load balancer simulation.
 * 
 * The main function prompts the user to enter the initial number of web servers 
 * and the number of clock cycles to simulate. It then generates an initial queue 
 * of requests, runs the simulation, and uses the load balancer to manage and 
 * process the requests.
 * 
 * @return int Exit status of the program (0 for successful execution).
 */
int main() {
    srand(time(0)); // Seed for random number generator

    // Get user input for the number of servers and simulation run time
    int numServers, runTime;
    std::cout << "Enter the initial number of web servers: ";
    std::cin >> numServers;
    std::cout << "Enter the amount of clock cycles to simulate: ";
    std::cin >> runTime;

    // Initialize the load balancer with the specified number of servers
    LoadBalancer loadBalancer(numServers);

    // Create initial set of requests (servers * 100 requests)
    int initialRequests = numServers * 100;
    for (int i = 0; i < initialRequests; ++i) {
        std::string ipIn = generateRandomIP();
        std::string ipOut = generateRandomIP();
        int time = rand() % 100 + 1;  // Random time between 1 and 100 clock cycles
        char jobType = randomJobType();
        loadBalancer.addRequest(Request(ipIn, ipOut, time, jobType));
    }

    // Add these requests to the load balancer's default request queue
    loadBalancer.addDefaultRequests(initialRequests);

    // Run the simulation for the specified amount of clock cycles
    loadBalancer.simulate(runTime);

    return 0;
}
