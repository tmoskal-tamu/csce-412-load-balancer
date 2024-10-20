#ifndef REQUEST_H
#define REQUEST_H

#include <string>

struct Request {
    std::string ipIn;
    std::string ipOut;
    int time;       // Time to process (in clock cycles)
    char jobType;   // 'P' for processing, 'S' for streaming

    // Default constructor
    Request();

    // Parameterized constructor
    Request(const std::string& ipIn_, const std::string& ipOut_, int time_, char jobType_);
};

#endif // REQUEST_H
