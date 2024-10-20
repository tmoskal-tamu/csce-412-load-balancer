#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>

// Struct to store request information
struct Request {
    std::string ipIn;
    std::string ipOut;
    int time;       // Time to process (in clock cycles)
    char jobType;   // 'P' for processing, 'S' for streaming

    // Default constructor
    Request() : ipIn("0.0.0.0"), ipOut("0.0.0.0"), time(0), jobType('P') {}

    // Parameterized constructor
    Request(const std::string& ipIn_, const std::string& ipOut_, int time_, char jobType_)
        : ipIn(ipIn_), ipOut(ipOut_), time(time_), jobType(jobType_) {}
};

// Class to represent a queue of requests
class RequestQueue {
private:
    std::queue<Request> queue;

public:
    void addRequest(const Request& request) {
        queue.push(request);
    }

    Request getNextRequest() {
        if (!queue.empty()) {
            Request req = queue.front();
            queue.pop();
            return req;
        }
        return Request(); // Return a default Request if the queue is empty
    }

    bool isEmpty() const {
        return queue.empty();
    }
};

// Class to represent a web server
class WebServer {
private:
    bool busy;          // Whether the server is busy processing a request
    Request currentRequest;
    int remainingTime;  // Time left to process the current request

public:
    WebServer() : busy(false), remainingTime(0) {}

    // Start processing a new request
    void processRequest(const Request& request) {
        currentRequest = request;
        remainingTime = request.time;
        busy = true;
        std::cout << "Started processing request: " << request.ipIn << " -> "
                  << request.ipOut << " Time: " << request.time
                  << " JobType: " << request.jobType << std::endl;
    }

    // Simulate the passage of one clock cycle
    void tick() {
        if (busy) {
            remainingTime--;
            if (remainingTime <= 0) {
                busy = false;
                std::cout << "Finished processing request: " << currentRequest.ipIn << " -> "
                          << currentRequest.ipOut << std::endl;
            }
        }
    }

    bool isBusy() const {
        return busy;
    }
};

// Class to represent a load balancer that manages web servers and requests
class LoadBalancer {
private:
    std::vector<WebServer> servers;
    RequestQueue requestQueue;
    int currentTime;

public:
    LoadBalancer(int numServers) : currentTime(0) {
        servers.resize(numServers);
    }

    void addRequest(const Request& request) {
        requestQueue.addRequest(request);
    }

    // Simulate the load balancer for a specified amount of time
    void simulate(int runTime) {
        for (currentTime = 0; currentTime < runTime; ++currentTime) {
            std::cout << "Clock cycle: " << currentTime << std::endl;

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
    }
};

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
    std::cout << "Enter number of web servers: ";
    std::cin >> numServers;
    std::cout << "Enter simulation runtime (in clock cycles): ";
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
