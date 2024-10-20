#include "Request.h"

// Default constructor
Request::Request() : ipIn("0.0.0.0"), ipOut("0.0.0.0"), time(0), jobType('P') {}

// Parameterized constructor
Request::Request(const std::string& ipIn_, const std::string& ipOut_, int time_, char jobType_)
    : ipIn(ipIn_), ipOut(ipOut_), time(time_), jobType(jobType_) {}
